# StepperMotor_Control_VHDL
The aim of this project is to control a stepper motor from a C code. The file includes the definition of the entity in VHDL as well as a test bench to test it but also the driver to make it work on a FPGA board and finally, the control code in C. In this repository you can also find a pdf explaining in more details all the steps of this project. We gave 2 C files to control the Stepper Motor. The first one will only make it turn in one direction or the other. The second code will make the motor turn for a specific angle in one or other direction. Here is the table of content:

1) Objective
2) Constraints
3) Presentation of the different parts
4) VHDL
5) Test Bench
6) Platform designer, GHRD & Pin Planner
7) C code
8) Passage to the electronic board
9) Explanation of how it works
10) Conclusion


# Link to the video presentation
https://youtu.be/2Dp3qKqm1wg


# Authors
Nicolas Thils: nicothils@hotmail.com
Robin Vandebrouck: robin.vandebrouck@orange.fr

This work was carried out within the framework of the Hardware/Software course of the Polytechnic Faculty of the University of Mons (Belgium) during the academic year 2020-2021.
https://web.umons.ac.be/fr/


# Disclamer
The code of the StepperMotorPorts.vhdl is inspired by another github (https://github.com/23b125/VHDLstepperDriver/blob/master/StepperMotorDrive.vhd) and has been adapted to fit the objetives of this project.
