library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
use IEEE.NUMERIC_STD.ALL;

entity tb_full_adder_4bit is
end tb_full_adder_4bit;

architecture Behavioral of tb_full_adder_4bit is
    component full_adder_4bit
        Port (
            A     : in  STD_LOGIC_VECTOR(3 downto 0);
            B     : in  STD_LOGIC_VECTOR(3 downto 0);
            Cin   : in  STD_LOGIC;
            Sum   : out STD_LOGIC_VECTOR(3 downto 0);
            Cout  : out STD_LOGIC
        );
    end component;

    signal A, B, Sum : STD_LOGIC_VECTOR(3 downto 0);
    signal Cin, Cout : STD_LOGIC;
begin
    uut: full_adder_4bit
        port map (A => A, B => B, Cin => Cin, Sum => Sum, Cout => Cout);

    stim: process
    begin
        A <= "0000"; B <= "0000"; Cin <= '0'; wait for 10 ns;  -- 0 + 0 + 0 = 0000, C=0
        A <= "0001"; B <= "0001"; Cin <= '0'; wait for 10 ns;  -- 1 + 1 = 0010, C=0
        A <= "0101"; B <= "0011"; Cin <= '1'; wait for 10 ns;  -- 5 + 3 + 1 = 1001, C=0
        A <= "1111"; B <= "0001"; Cin <= '0'; wait for 10 ns;  -- 15+1=16 -> 0000, C=1
        A <= "1111"; B <= "1111"; Cin <= '1'; wait for 10 ns;  -- 15+15+1=31 -> 1111, C=1
        wait;
    end process;
end Behavioral;
