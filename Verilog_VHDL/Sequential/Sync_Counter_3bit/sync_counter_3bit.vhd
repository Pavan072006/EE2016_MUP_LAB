library IEEE;
use IEEE.STD_LOGIC_1164.ALL;

-- Entity declaration
entity sync_counter_3bit is
    Port (
        clk   : in  STD_LOGIC;  -- Clock signal
        reset : in  STD_LOGIC;  -- Active-high synchronous reset
        q     : out STD_LOGIC_VECTOR(2 downto 0)  -- 3-bit counter output
    );
end sync_counter_3bit;

-- Architecture: Structural using D flip-flops
architecture Behavioral of sync_counter_3bit is
    signal d, q_int : STD_LOGIC_VECTOR(2 downto 0);
begin
    ----------------------------------------------------------------
    -- Combinational logic for D inputs (binary up-counter)
    ----------------------------------------------------------------
    d(0) <= not q_int(0);  -- Toggle every clock
    d(1) <= q_int(1) xor q_int(0);  -- Toggle when q0 = 1
    d(2) <= q_int(2) xor (q_int(1) and q_int(0));  -- Toggle when q1 & q0 = 1

    ----------------------------------------------------------------
    -- Sequential logic: 3 D flip-flops (synchronous reset)
    ----------------------------------------------------------------
    process(clk)
    begin
        if rising_edge(clk) then
            if reset = '1' then
                q_int <= (others => '0');
            else
                q_int <= d;
            end if;
        end if;
    end process;

    -- Connect internal signals to output
    q <= q_int;

end Behavioral;
