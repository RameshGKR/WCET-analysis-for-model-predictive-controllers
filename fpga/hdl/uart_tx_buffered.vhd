--------------------------------------------------------------------------------
--! @date 08/09/2023
--! @author Ward Goossens wardgoossens@gmail.com
--------------------------------------------------------------------------------
--! @brief UART Transmitter with buffer
--!
--! Implements a 12 MBaud UART transmitter with buffer. The data is first stored
--! in an asynchronous, asymmetric FIFO buffer in words of 64 bits. Data is then
--! pulled from the buffer in 8 bit words to be transmitted.
--!
--! 12 MBaud is the maximum baud rate supported by the onboard FT232HQ UART-USB
--! bridge. Communication at this baud rate requires the FTDI D2xx and 
--! VCP drivers.
--------------------------------------------------------------------------------

library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
use IEEE.NUMERIC_STD.ALL;

entity uart_tx_buffered is
    port ( 
        CLK_BASE : in std_logic;                -- Base clock (100 MHz)
        RST : in std_logic;                     -- Active-high reset
        UART_TX : out std_logic;                -- Outgoing UART line
        DIN : in std_logic_vector (63 downto 0);-- Buffer input data
        DVALID : in std_logic;                  -- Buffer input data is valid
        READY : out std_logic                   -- Output buffer ready to receive
    );
end uart_tx_buffered;

architecture behavioral of uart_tx_buffered is

--- FIFO signals ---
signal fifo_out : std_logic_vector(7 downto 0);
signal fifo_re : std_logic;
signal fifo_empty : std_logic;
signal fifo_full : std_logic;
signal fifo_valid : std_logic;

--- UART clock signals ---
signal clk_uart : std_logic;

--- UART state signals ---
type t_uart_state is (s_idle, s_start, s_data, s_stop);
signal uart_state : t_uart_state := s_idle;
signal bit_count : integer range 0 to 7 := 0;

begin

--- UART Clock generator (PLL) ---
uart_clock_wiz : entity work.uart_clock_wiz
port map (
    CLK_IN => CLK_BASE, -- 100 MHz
    CLK_OUT => clk_uart -- 12 MHz
);

--- FIFO ---
uart_buffer : entity work.fifo_generator
port map (
    WR_CLK => CLK_BASE,
    RD_CLK => clk_uart,
    RST => RST,
    DIN => DIN,
    WR_EN => DVALID,
    RD_EN => fifo_re,
    DOUT => fifo_out,
    FULL => fifo_full,
    EMPTY => fifo_empty,
    VALID => fifo_valid,
    WR_RST_BUSY => open, -- Only for UltraScale architectures
    RD_RST_BUSY => open  -- Only for UltraScale architectures
);

READY <= not fifo_full;

--- UART transmission ---
p_queue_uart_seq:
process(CLK_UART)
begin
    if rising_edge(CLK_UART) then
    if RST = '1' then
        uart_state <= s_idle;
        bit_count <= 0;
    else
        if uart_state = s_idle then
            if fifo_empty = '0' then
                uart_state <= s_start;
            else
                uart_state <= s_idle;
            end if;
        elsif uart_state = s_start then
            if fifo_valid = '1' then
                uart_state <= s_data;
                bit_count <= 0;
            else
                uart_state <= s_idle;
            end if;
        elsif uart_state = s_data then
            if bit_count < 7 then
                bit_count <= bit_count + 1;
                uart_state <= s_data;
            else
                uart_state <= s_stop;
            end if;
        elsif uart_state = s_stop then
            if fifo_empty = '0' then
                uart_state <= s_start;
            else
                uart_state <= s_idle;
            end if;
        end if;
    end if;
    end if;
end process p_queue_uart_seq;

p_queue_uart_com:
process(uart_state, fifo_out, bit_count, fifo_empty, fifo_valid)
begin
    case uart_state is
    when s_idle =>
        fifo_re <= not fifo_empty;
        UART_TX <= '1';
    when s_start =>
        fifo_re <= '0';
        UART_TX <= not fifo_valid;
    when s_data =>
        fifo_re <= '0';
        UART_TX <= fifo_out(bit_count);
    when others => -- s_stop | others
        fifo_re <= not fifo_empty;
        UART_TX <= '1';
    end case; 
end process p_queue_uart_com;

end behavioral;
