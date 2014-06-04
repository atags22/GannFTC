#pragma config(Hubs,  S1, HTMotor,  HTMotor,  HTMotor,  HTServo)
#pragma config(Sensor, S2,     touchy,         sensorTouch)
#pragma config(Sensor, S3,     ir,             sensorHiTechnicIRSeeker1200)
#pragma config(Sensor, S4,     compass,        sensorI2CHiTechnicCompass)
#pragma config(Motor,  motorA,           ,             tmotorNXT, openLoop)
#pragma config(Motor,  motorB,           ,             tmotorNXT, openLoop)
#pragma config(Motor,  motorC,           ,             tmotorNXT, openLoop)
#pragma config(Motor,  mtr_S1_C1_1,     omniBR,        tmotorTetrix, PIDControl, encoder)
#pragma config(Motor,  mtr_S1_C1_2,     omniFR,        tmotorTetrix, PIDControl, encoder)
#pragma config(Motor,  mtr_S1_C2_1,     omniBL,        tmotorTetrix, PIDControl, encoder)
#pragma config(Motor,  mtr_S1_C2_2,     omniFL,        tmotorTetrix, PIDControl, encoder)
#pragma config(Motor,  mtr_S1_C3_1,     motorH,        tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C3_2,     motorI,        tmotorTetrix, openLoop)
#pragma config(Servo,  srvo_S1_C4_1,    servo1,               tServoNone)
#pragma config(Servo,  srvo_S1_C4_2,    servo2,               tServoNone)
#pragma config(Servo,  srvo_S1_C4_3,    servo3,               tServoNone)
#pragma config(Servo,  srvo_S1_C4_4,    servo4,               tServoNone)
#pragma config(Servo,  srvo_S1_C4_5,    servo5,               tServoNone)
#pragma config(Servo,  srvo_S1_C4_6,    servo6,               tServoNone)

#define JOY_SCALE -0.78 // * 0.85
#define JOY_THRESHOLD 15
#define SQR(x) ((x) * (x))

#include "JoystickDriver.c"

task main()
{
	bNxtLCDStatusDisplay = false;
	bDisplayDiagnostics = false;
	for (int i = 0; i < 7; i++)
		nxtDisplayClearTextLine(i);
	nxtDisplayCenteredTextLine(0, "Debugger");
	while (true)
	{
		// Set up joystick
		getJoystickSettings(joystick);

		// Drive teleop
		float moveX, moveY; int rotate;

		if (abs(joystick.joy1_x2) < JOY_THRESHOLD) // noise
		{
			rotate = 0;
		}
		else rotate = joystick.joy1_x2 * /* TELE_OP_SCALE */ JOY_SCALE;

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
		motor[omniFR] = /*TELE_OP_SCALE */ JOY_SCALE * (moveX - moveY) + rotate;
		motor[omniBR] = /*TELE_OP_SCALE */ JOY_SCALE * (-moveX - moveY) + rotate;
		motor[omniFL] = /*TELE_OP_SCALE */ JOY_SCALE * (moveX + moveY) + rotate;
		motor[omniBL] = /*TELE_OP_SCALE */ JOY_SCALE * (-moveX + moveY) + rotate;

		nxtDisplayCenteredTextLine(2, "FL: %d | FR: %d", motorPowerSigned[omniFL], motorPowerSigned[omniFR]);
		nxtDisplayCenteredTextLine(3, "BL: %d | BR: %d", motorPowerSigned[omniBL], motorPowerSigned[omniBR]);

		nxtDisplayCenteredTextLine(5, "X: %d ||| Y: %d", joy1_x1, joy1_y1);
		wait10Msec(3);
	}
}
