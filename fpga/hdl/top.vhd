--------------------------------------------------------------------------------
--! @date 08/09/2023
--! @author Ward Goossens wardgoossens@gmail.com
--------------------------------------------------------------------------------
--! @brief Timestamp logger for use with RapiTime
--!
--! Logs the ID and timestamp for embedded runtime execution analysis.
--! Timestamps are buffered and transmitted to a PC using 12 MBaud UART. When
--! the done signal is asserted, the first two bits of the record are set high
--! to end the logging on the PC.
--!
--! A timestamp record consists of 8 bytes:
--! 0b00 + ID[14] + TIMESTAMP[32] + CRC[8] + SEQ[8]
--! 
--! If done was asserted, the record has the following structure:
--! 0b1100 + 0x000 + 0x00000000 + CRC[8] + SEQ[8]
--! 
--------------------------------------------------------------------------------

library IEEE;
use IEEE.std_logic_1164.ALL;
use IEEE.numeric_std.ALL;
use IEEE.std_logic_misc.xor_reduce;

entity top is
    port ( 
        CLK : in std_logic;                             -- Board clock (100 MHz)
        RST_N : in std_logic;                           -- Active-low reset

        UART_RX : in std_logic;                         -- Incoming UART through FT232H UART-USB bridge
        UART_TX : out std_logic;                        -- Outgoing UART through FT232H UART-USB bridge

        INSTR_EN : in std_logic;                        -- CK_IO[26]    - enable for ID bus, RST and DONE
        INSTR_ACK : out std_logic;                      -- CK_IO[29]    - acknowledge of enable
        INSTR_RST : in std_logic;                       -- CK_IO[27]    - reset for timestamp counter 
	    INSTR_DONE: in std_logic;                       -- CK_IO[28]    - indicate end of logging
        INSTR_ID : in std_logic_vector(13 downto 0);    -- CK_IO[0-13]  - 14-bit asynchronous ID bus
        INSTR_ID_PARITY : in std_logic;                 -- CK_IO[30]    - odd parity bit for the ID bus
	    INSTR_EN_LED : out std_logic;                   -- LED6         - indicate enable
        
        FORWARD_UART : in std_logic;                    -- SW0          - Enable UART forwarding
        FORWARD_UART_ENABLED : out std_logic;           -- LED5         - UART forwarding enabled
        UART_TX_F : out std_logic;                      -- CK_IO[40]    - Outgoing UART through CK_IO
        UART_RX_F : in std_logic;                       -- CK_IO[41]    - Incoming UART through CK_IO
        
        NOT_READY_LED : out std_logic                   -- LED4         - UART TX was not ready to receive data, data loss occurred
    );
end top;

architecture behavorial of top is
--- Signals ---
signal rst : std_logic;

signal instr_en_stable : std_logic;
signal instr_en_sync : std_logic;
signal instr_id_sync : std_logic_vector(INSTR_ID'range);
signal instr_id_parity_sync : std_logic;
signal instr_id_sync_valid : std_logic;
signal instr_done_sync : std_logic;
signal instr_rst_sync : std_logic;

type t_action is (s_idle, s_wait, s_log, s_rst, s_ack);
signal action, next_action : t_action;

subtype t_counter is natural; -- 32 bit by default
signal counter : t_counter;

signal seq_counter : natural range 0 to 2**8-1;
signal message : std_logic_vector(47 downto 0);
signal uart_in : std_logic_vector(63 downto 0);
signal uart_valid : std_logic;
signal uart_ready : std_logic;

signal uart_tx_i : std_logic;

--- LUTs ---
-- CRC-8-ATM linear implementation for (56, 48) code
type t_crc8 is array (0 to 7) of std_logic_vector(47 downto 0);
constant lut_crc8 : t_crc8 := (
    "100101001100011001101000010101101010100011100000",
    "110010100110001100110100001010110101010001110000",
    "111001010011000110011010000101011010101000111000",
    "011100101001100011001101000010101101010100011100",
    "101110010100110001100110100001010110101010001110",
    "110111001010011000110011010000101011010101000111",
    "011110101001010101110001111101111111001001000011",
    "001010011000110011010000101011010101000111000001"
);

function crc8(value : std_logic_vector(47 downto 0)) return std_logic_vector is
    variable v_crc : std_logic_vector(0 to 7) := X"00";
begin
    for i in lut_crc8'range loop
        v_crc(i) := xor_reduce(value and lut_crc8(i));
    end loop;
    return v_crc;
end function;

begin
--- Active high reset signal ---
rst <= not RST_N;

--- IO connections ---
INSTR_EN_LED <= INSTR_EN;

--- Stabilize input enable signal ---
sync_2ff_instr_en: entity work.synchronizer_2ff
port map(
    CLK => CLK,
    RST => rst,
    INPUT => INSTR_EN,
    OUTPUT => instr_en_stable
);

--- Sample ID, RST, DONE with stabilized enable ---
p_sample:
process(CLK)
begin
    if rising_edge(CLK) then
    if rst = '1' then
        instr_en_sync <= '0';
        instr_id_sync <= (others => '0');
        instr_rst_sync <= '0';
        instr_done_sync <= '0';
    elsif instr_en_stable = '1' then
        instr_id_sync <= INSTR_ID;
        instr_id_parity_sync <= INSTR_ID_PARITY;
        instr_rst_sync <= INSTR_RST;
        instr_done_sync <= INSTR_DONE;
    end if;
    instr_en_sync <= instr_en_stable;
    end if;
end process p_sample;

--- Action state machine ---
p_action:
process(CLK)
begin
    if rising_edge(CLK) then
    if rst = '1' then
        action <= s_idle;
    else
        action <= next_action;
    end if;
    end if;
end process p_action;

instr_id_sync_valid <= not xor_reduce(instr_id_sync & instr_id_parity_sync);

p_next_action:
process(action, instr_en_sync, instr_done_sync, instr_rst_sync, instr_id_sync_valid, uart_ready)
begin
    case action is
        when s_log | s_ack | s_rst =>
            if instr_en_sync = '1' then
                next_action <= s_ack;
            else
                next_action <= s_idle;
            end if;
        when s_wait =>
            if uart_ready = '1' and (instr_id_sync_valid = '1' or instr_done_sync = '1') then
                next_action <= s_log;
            else
                next_action <= s_wait;
            end if;
        when others => -- s_idle
            if instr_en_sync = '1' then
                if instr_rst_sync = '1' then
                    next_action <= s_rst;
                elsif uart_ready = '1' and (instr_id_sync_valid = '1' or instr_done_sync = '1') then
                    next_action <= s_log;
                else
                    next_action <= s_wait;
                end if;
            else
                next_action <= s_idle;
            end if;
    end case;
end process p_next_action;

INSTR_ACK <= '1' when (action = s_log or action = s_rst or action = s_ack) else '0';

--- Counter ---
p_counter:
process(CLK)
begin
    if rising_edge(CLK) then
        if rst = '1' or action = s_rst then
            counter <= 0;
        elsif instr_en_sync = '0' then -- If instr_en_sync is high, the CPU is not doing anything
            if counter = t_counter'high then
                counter <= 0;
            else
                counter <= counter + 1;
            end if;
        end if;
    end if;
end process p_counter;

--- Write message to UART buffer ---
p_seq:
process(CLK)
begin
    if rising_edge(CLK) then
    if rst = '1' then
        seq_counter <= 0;
    elsif uart_valid = '1' then
        seq_counter <= seq_counter + 1;
    end if;
    end if;
end process p_seq;
with instr_done_sync select message <=
    "11" & std_logic_vector(to_unsigned(0, 14)) & std_logic_vector(to_unsigned(0, 32)) when '1',
    "00" & instr_id_sync & std_logic_vector(to_unsigned(counter, 32)) when others;

uart_in <= message & crc8(message) & std_logic_vector(to_unsigned(seq_counter, 8));
uart_valid <= '1' when action = s_log else '0';

--- Buffered UART transmitter ---
uart_tx_buffered : entity work.uart_tx_buffered
port map (
    CLK_BASE => CLK,
    RST => rst,
    UART_TX => uart_tx_i,
    DIN => uart_in,
    DVALID => uart_valid,
    READY => uart_ready
);

--- Show that the buffer is not ready to accept data with an LED ---
NOT_READY_LED <= not uart_ready;

--- Use FPGA board as USB-UART bridge when SW0 is active ---
p_forward_uart:
process(uart_tx_i, UART_RX_F, UART_RX, FORWARD_UART)
begin
    if FORWARD_UART = '1' then
        UART_TX <= UART_RX_F;
        UART_TX_F <= UART_RX;
	    FORWARD_UART_ENABLED <= '1';
    else
        UART_TX <= uart_tx_i;
        UART_TX_F <= '1';
	    FORWARD_UART_ENABLED <= '0';
    end if;
end process p_forward_uart;
    
end behavorial;