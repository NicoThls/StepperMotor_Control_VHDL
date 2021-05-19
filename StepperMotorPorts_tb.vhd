library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
use IEEE.STD_LOGIC_ARITH.ALL;
use IEEE.STD_LOGIC_UNSIGNED.ALL;



entity StepperMotorPorts_tb is
end StepperMotorPorts_tb;

architecture tb of StepperMotorPorts_tb is
	 signal StepDrive_A : std_logic;
	 signal StepDrive_B : std_logic;
	 signal StepDrive_C : std_logic;
	 signal StepDrive_D : std_logic;
    signal clock : std_logic;
    signal Direction : std_logic;
    signal StepEnable : std_logic;
    signal Reset : std_logic;
	 constant T : time := 20 ns; 


	 
begin

    UUT : entity work.StepperMotorPorts port map (StepDrive_A => StepDrive_A, StepDrive_B => StepDrive_B, StepDrive_C => StepDrive_C, StepDrive_D => StepDrive_D,clock => clock, Direction => Direction, StepEnable => StepEnable, Reset => Reset);

    Reset <= '1', '0' after 100 ns, '1' after 30e6 ns, '0' after 40e6 ns;
    StepEnable <= '1', '0' after 5e6 ns, '1' after 10e6 ns, '0' after 50e6 ns;
    Direction <=  '1', '0' after 1e6 ns, '1' after 2e6 ns, '0' after 3e6 ns, '1' after 4e6 ns, '0' after 15e6 ns;

	 
	 -- clock
    process
    begin
        clock <= '0';
        wait for T/2;
        clock <= '1';
        wait for T/2;
    end process;
	 
end tb;