library IEEE;
use IEEE.STD_LOGIC_1164.ALL;

entity tb_sync_counter_3bit is
end tb_sync_counter_3bit;

architecture Behavioral of tb_sync_counter_3bit is
    -- Component declaration
    component sync_counter_3bit
        Port (
            clk   : in  STD_LOGIC;
            reset : in  STD_LOGIC;
            q     : out STD_LOGIC_VECTOR(2 downto 0)
        );
    end component;

    -- Signals for simulation
    signal clk   : STD_LOGIC := '0';
    signal reset : STD_LOGIC := '0';
    signal q     : STD_LOGIC_VECTOR(2 downto 0);

begin
    -- Instantiate the counter
    uut: sync_counter_3bit
        port map (
            clk   => clk,
            reset => reset,
            q     => q
        );

    -- Clock generation: 10 ns period (100 MHz)
    clk_process: process
    begin
        clk <= '0';
        wait for 5 ns;
        clk <= '1';
        wait for 5 ns;
    end process;

    -- Stimulus process
    stim_proc: process
    begin
        -- Apply reset for first 2 clock cycles
        reset <= '1';
        wait for 20 ns;
        reset <= '0';

        -- Let counter run for several cycles
        wait for 160 ns;

        -- Apply another reset mid-way
        reset <= '1';
        wait for 10 ns;
        reset <= '0';

        -- Continue counting
        wait for 100 ns;

        wait; -- End simulation
    end process;
end Behavioral;
