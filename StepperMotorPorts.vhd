library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
use IEEE.STD_LOGIC_ARITH.ALL;
use IEEE.STD_LOGIC_UNSIGNED.ALL;



entity StepperMotorPorts is
    Port (	
	 			StepDrive_A : out std_logic;
				StepDrive_B : out std_logic;
				StepDrive_C : out std_logic;
				StepDrive_D : out std_logic;
		 		clock : in std_logic;
		 		Direction : in std_logic;
		 		StepEnable : in std_logic;
            Reset : in std_logic --;
		);
end StepperMotorPorts;

architecture StepDrive of StepperMotorPorts is

	signal StepDrive : std_logic_vector(3 downto 0);
	signal state : std_logic_vector(1 downto 0) := "00";
	signal StepCounter : std_logic_vector(31 downto 0) := (others => '0');
	constant StepLockOut : std_logic_vector(31 downto 0) := "00000000000000110000110101000000";	--"00000000000000000000110101000000";

	
	
begin

	process(clock)
	begin

		if ( (clock'Event) and (clock = '1') ) then


			if (Reset = '1') then

				 state <= "00";
				 StepCounter <= "00000000000000000000000000000000"; --(others => '0');
				 StepDrive <= "0000";
				 StepDrive_A <= '0';--StepDrive(3);
				 StepDrive_B <= '0';--StepDrive(2);
				 StepDrive_C <= '0';--StepDrive(1);
				 StepDrive_D <= '0';--StepDrive(0);

				 
			else

				StepCounter <= StepCounter + "0000000000000000000000000000001";

				if (StepCounter >= StepLockOut) then

					StepCounter <= "00000000000000000000000000000000";

					StepDrive <= "0000";
					
					if (StepEnable = '1') then
					
						if (Direction = '1') then state <= state + "01"; end if;
						if (Direction = '0') then state <= state - "01"; end if;

						case state is 

							when "00" =>

								StepDrive <= "1010";
								StepDrive_A <= '1';--StepDrive(3);
								StepDrive_B <= '0';--StepDrive(2);
								StepDrive_C <= '1';--StepDrive(1);
								StepDrive_D <= '0';--StepDrive(0);
								
							when "01" =>
			
								StepDrive <= "1001";
								StepDrive_A <= '1';--StepDrive(3);
								StepDrive_B <= '0';--StepDrive(2);
								StepDrive_C <= '0';--StepDrive(1);
								StepDrive_D <= '1';--StepDrive(0);
								
							when "10" =>
			
								StepDrive <= "0101";	
								StepDrive_A <= '0';--StepDrive(3);
								StepDrive_B <= '1';--StepDrive(2);
								StepDrive_C <= '0';--StepDrive(1);
								StepDrive_D <= '1';--StepDrive(0);		
								
							when "11" =>
			
								StepDrive <= "0110";
								StepDrive_A <= '0';--StepDrive(3);
								StepDrive_B <= '1';--StepDrive(2);
								StepDrive_C <= '1';--StepDrive(1);
								StepDrive_D <= '0';--StepDrive(0);
								
							when others =>

						end case;
		
					end if;
					
				end if;
	
			end if;

		end if;

	end process;

end StepDrive;