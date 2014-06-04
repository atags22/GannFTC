#pragma config(Hubs,  S4, HTMotor,  HTMotor,  none,     none)
#pragma config(Sensor, S1,     IR,             sensorHiTechnicIRSeeker1200)
#pragma config(Sensor, S2,     Compass,        sensorI2CHiTechnicCompass)
#pragma config(Sensor, S4,     ,               sensorI2CMuxController)
#pragma config(Motor,  motorA,           ,             tmotorNXT, openLoop)
#pragma config(Motor,  motorB,           ,             tmotorNXT, openLoop)
#pragma config(Motor,  motorC,           ,             tmotorNXT, openLoop)
#pragma config(Motor,  mtr_S4_C1_1,     omniFR,        tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S4_C1_2,     omniFL,        tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S4_C2_1,     omniBL,        tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S4_C2_2,     omniBR,        tmotorTetrix, openLoop)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

#include "JoystickDriver.c"
#define SQR(x) ((x) * (x))
task main()
{
	int speed;
	float direction;
while(true)
{
/*		servo[rotFL] = 127;
		servo[rotFR] = 127;
		servo[rotBL] = 127;
		servo[rotBR] = 127;
*/
	getJoystickSettings(joystick);
	speed = sqrt(SQR(joystick.joy1_x1) + SQR(joystick.joy1_y1));
	if (joystick.joy1_x1 == 0)
	{
		direction = (PI/2) * (abs(joystick.joy1_y1)/(joystick.joy1_y1));
	}
	else
	{
	direction = atan((joystick.joy1_y1/128)/(joystick.joy1_x1/128)) * (abs(joystick.joy1_y1)/(joystick.joy1_y1));
	}

	motor[omniBR] = (speed * cos(direction - (PI/4)));
	motor[omniFR] = (speed * sin(direction - (PI/4)));
	motor[omniBL] = (speed * sin(direction - (PI/4)));
	motor[omniFL] = (speed * cos(direction - (PI/4)));
}
}
