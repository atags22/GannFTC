#pragma config(Hubs,  S1, HTServo,  HTMotor,  HTMotor,  none)
#pragma config(Hubs,  S2, HTMotor,  none,     none,     none)
#pragma config(Sensor, S1,     ,               sensorI2CMuxController)
#pragma config(Sensor, S2,     ,               sensorI2CMuxController)
#pragma config(Motor,  motorA,          motor1,        tmotorNXT, PIDControl, encoder)
#pragma config(Motor,  motorB,          motor2,        tmotorNXT, PIDControl, encoder)
#pragma config(Motor,  motorC,          motor3,        tmotorNXT, PIDControl, encoder)
#pragma config(Motor,  mtr_S1_C2_1,     Turbine,       tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C2_2,     Flag,          tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C3_1,     LeftLift,      tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C3_2,     RightLift,     tmotorTetrix, openLoop, reversed)
#pragma config(Motor,  mtr_S2_C1_1,     LeftDrive,     tmotorTetrix, PIDControl, reversed, encoder)
#pragma config(Motor,  mtr_S2_C1_2,     RightDrive,    tmotorTetrix, PIDControl, encoder)
#pragma config(Servo,  srvo_S1_C1_1,    DispenseL,            tServoContinuousRotation)
#pragma config(Servo,  srvo_S1_C1_2,    DispenseR,            tServoContinuousRotation)
#pragma config(Servo,  srvo_S1_C1_3,    AutonomousDispenser,  tServoStandard)
#pragma config(Servo,  srvo_S1_C1_4,    servo4,               tServoNone)
#pragma config(Servo,  srvo_S1_C1_5,    servo5,               tServoNone)
#pragma config(Servo,  srvo_S1_C1_6,    servo6,               tServoNone)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

#include "JoystickDriver.c"
#define THRESH 25 // variable to create a deadzone in the controller's y values
#define SLOW 25  // variable for the minimum speed of drive motors in which robot moves
#define SCALE .78125 // variable that scales numbers between -128 and 128 to -100 and 100

task main()
{
	while(true)
	{
		getJoystickSettings(joystick);
		servo[AutonomousDispenser] = 256;

		// code for driving the robot slowly with face buttons
		if (joy1Btn(4)) // moves the robot foward at minimum speed
		{
			motor[LeftDrive] = -SLOW;
			motor[RightDrive] = SLOW;
		}
		else if (joy1Btn(2)) // moves the robot backwards at minimum speed
		{
			motor[LeftDrive] = SLOW;
			motor[RightDrive] = -SLOW;
		}
		else if (joy1Btn(1)) // rotates the robot in place clockwise
		{
			motor[LeftDrive] = SLOW;
			motor[RightDrive] = SLOW;
		}
		else if (joy1Btn(3)) // rotates the robot in place counterclockwise
		{
			motor [LeftDrive] = -SLOW;
			motor [RightDrive] = -SLOW;
		}

		// code for driving the robot with joysticks
		//else
		{
			if ((joystick.joy1_y1) > THRESH || (joystick.joy1_y1) < -THRESH) // runs the left side tread
			{
				motor[LeftDrive]= ((joystick.joy1_y1)* SCALE);
			}
			else {
				motor[LeftDrive]= 0;
			}

			if ((joystick.joy1_y2) > THRESH || (joystick.joy1_y2) < -THRESH) // runs the right side tread
			{
				motor[RightDrive]= ((joystick.joy1_y2)* SCALE);
				nxtDisplayCenteredTextLine(2, "Pressed");
			}
			else {
				motor[RightDrive]= 0;
			}
		}

		// code for running the lift
		if (joy2Btn(5)) // runs the lift up
		{
			motor [LeftLift] = -100;
			motor [RightLift] = 100;
		}
		else if (joy2Btn(7)) // runs the lift down
		{
			motor [LeftLift] = 100;
			motor [RightLift] = -100;
		}
		else
		{
			motor [LeftLift] = 0;
			motor [RightLift] = 0;
		}

		// code for setting the chamber servos to preset positions
		if (joy1Btn(3))
		{
			servo[DispenseL] = 100;
			servo[DispenseR] = 100;
		}

		if (joy1Btn(1))
		{
			servo[DispenseL] = 200;
			servo[DispenseR] = 200;
		}

		// code for manuel dispensing with chamber servos
		if (joy1Btn(2))
		{
			servo[DispenseL] = (ServoValue[DispenseL] + 10); // rotates the chamber towards dispense in increments of 10 degrees
			servo[DispenseR] = (ServoValue[DispenseR] + 10);
		}
		if (joy1Btn(4))
		{
		servo[DispenseL] = (ServoValue[DispenseL] - 10); // rotates the chamber away from dispnse in increments of 10 degrees
		servo[DispenseR] = (ServoValue[DispenseR] - 10);
		}

		// code for the flag raiser
		if (joy2Btn(9)) // turns the crank at full speed
		{
			motor[Flag] = -100;
		}
		else if (joy2Btn(10)) // turns the crank at half speed for positioning
		{
			motor[Flag] = -25;
		}
		else
		{
			motor[Flag] = 0;
		}

		// code for the block grabber
		if (joy1Btn(6)) // runs the grabber inwards
		{
			motor[Turbine] = 100;
		}
		else if (joy1Btn(8)) // runs the grabber outwards
		{
			motor[Turbine] = -100;
		}
		else
		{
			motor[Turbine] =0;
		}
	}
}
// for (i = 0;(i < 50);i++)



		//// old code for the dispensing servos
		//if (joy2Btn(2)) // rotates the chamber backwards
		//{
		//	servo [DispenseL] = 137;
		//	servo [DispenseR] = 117;
		//}
		//else if (joy2Btn(4))
		//{
		//	servo [DispenseL] = 117;
		//	servo [DispenseR] = 137;
		//}
		//else  // keeps the chamber in place
		//{
		//	servo [DispenseL] = 140;
		//	servo [DispenseR] = 140;
		//}
