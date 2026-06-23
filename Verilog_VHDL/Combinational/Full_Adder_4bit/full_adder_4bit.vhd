library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
use IEEE.NUMERIC_STD.ALL;

entity full_adder_4bit is
    Port (
        A     : in  STD_LOGIC_VECTOR(3 downto 0);
        B     : in  STD_LOGIC_VECTOR(3 downto 0);
        Cin   : in  STD_LOGIC;
        Sum   : out STD_LOGIC_VECTOR(3 downto 0);
        Cout  : out STD_LOGIC
    );
end full_adder_4bit;

architecture Behavioral of full_adder_4bit is
begin
    process (A, B, Cin)
        variable temp : unsigned(4 downto 0);
    begin
        -- widen A and B to 5 bits and add
        temp := resize(unsigned(A), 5) + resize(unsigned(B), 5);

        -- add carry-in as +1 if Cin = '1'
        if Cin = '1' then
            temp := temp + 1;
        end if;

        -- drive outputs
        Sum  <= std_logic_vector(temp(3 downto 0));
        Cout <= temp(4);
    end process;
end Behavioral;
