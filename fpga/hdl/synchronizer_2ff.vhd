--------------------------------------------------------------------------------
--! @date 08/09/2023
--! @author Ward Goossens wardgoossens@gmail.com
--------------------------------------------------------------------------------
--! @brief Dual flip-flop synchronizer
--------------------------------------------------------------------------------

library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
use IEEE.NUMERIC_STD.ALL;

entity synchronizer_2ff is
    port( 
        CLK : in std_logic; -- Clock
        RST : in std_logic; -- Synchronous active-low reset
        INPUT : in std_logic; -- Input value
        OUTPUT : out std_logic); -- Output value
end synchronizer_2ff;

architecture behavioral of synchronizer_2ff is

signal a : std_logic := '0';

begin

p_synchronize:
process(CLK) is
begin
if rising_edge(CLK) then
    if RST = '1' then -- Synchronous reset
        a <= '0';
        OUTPUT <= '0';
    else
        a <= INPUT;
        OUTPUT <= a;
    end if;
end if;
end process p_synchronize;

end behavioral;
