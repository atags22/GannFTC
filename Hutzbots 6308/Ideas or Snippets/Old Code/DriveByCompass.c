
#pragma config(Hubs,  S1, HTMotor,  HTMotor,  HTServo,  none)
#pragma config(Sensor, S4,     NorthSeeker,    sensorI2CHiTechnicCompass)
#pragma config(Motor,  motorA,           ,             tmotorNXT, openLoop)
#pragma config(Motor,  motorB,           ,             tmotorNXT, openLoop)
#pragma config(Motor,  motorC,           ,             tmotorNXT, openLoop)
#pragma config(Motor,  mtr_S1_C1_1,     omniBR,        tmotorTetrix, openLoop, reversed, encoder)
#pragma config(Motor,  mtr_S1_C1_2,     omniFR,        tmotorTetrix, openLoop, reversed, encoder)
#pragma config(Motor,  mtr_S1_C2_1,     omniBL,        tmotorTetrix, openLoop, reversed, encoder)
#pragma config(Motor,  mtr_S1_C2_2,     omniFL,        tmotorTetrix, openLoop, reversed, encoder)
#pragma config(Servo,  srvo_S1_C3_1,    servo1,               tServoNone)
#pragma config(Servo,  srvo_S1_C3_2,    servo2,               tServoNone)
#pragma config(Servo,  srvo_S1_C3_3,    servo3,               tServoNone)
#pragma config(Servo,  srvo_S1_C3_4,    servo4,               tServoNone)
#pragma config(Servo,  srvo_S1_C3_5,    servo5,               tServoNone)
#pragma config(Servo,  srvo_S1_C3_6,    servo6,               tServoNone)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

#include "JoystickDriver.c"
float TELE_OP_SCALE = 0.85;	// 0.85 = regular, 0.3 = accuramode
#define JOY_SCALE 0.78	//scales down the values from the algorithm for getting motor values from the joystick because otherwise they are too large - is equal to 100 / 128 because 128 is the highest value the joystick has
#define JOY_THRESHOLD 30		//threshold for when joystick value is considered zero, because there is a good amount of noise in the joysticks
#define SQR(val) (val) * (val) // square function


task main()
{
	while (true)
	{
		float Direction;
		Direction = SensorValue[NorthSeeker];
		// Set up joystick
		getJoystickSettings(joystick);

		// Drive teleop
		float moveX, moveY; int rotate;


		if (abs(joystick.joy1_x2) < JOY_THRESHOLD) // noise
		{
			rotate = 0;
		}
		else rotate = joystick.joy1_x2 * TELE_OP_SCALE * JOY_SCALE;

		float correction;

		correction = (Direction - SensorValue[NorthSeeker]) + 180 - rotate;

		// Check for noise
		if ((sqrt(SQR(joystick.joy1_x1) + SQR(joystick.joy1_y1)) < JOY_THRESHOLD))
		{
			moveX = 0;
			moveY = 0;
		}
		else // actual control
		{
			moveX = joystick.joy1_x1;
			moveY = joystick.joy1_y1;
		}
		// Set the motors
		motor[omniFR] = TELE_OP_SCALE * JOY_SCALE * (moveX - moveY) + correction;
		motor[omniBR] = TELE_OP_SCALE * JOY_SCALE * (-moveX - moveY) + correction;
		motor[omniFL] = TELE_OP_SCALE * JOY_SCALE * (moveX + moveY) + correction;
		motor[omniBL] = TELE_OP_SCALE * JOY_SCALE * (-moveX + moveY) + correction;
	}
}