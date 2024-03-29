#pragma config(Hubs,  S3, HTMotor,  HTMotor,  HTMotor,  none)
#pragma config(Sensor, S3,     ,               sensorI2CMuxController)
#pragma config(Motor,  motorA,           ,             tmotorNXT, openLoop)
#pragma config(Motor,  motorB,           ,             tmotorNXT, openLoop)
#pragma config(Motor,  motorC,           ,             tmotorNXT, openLoop)
#pragma config(Motor,  mtr_S3_C1_1,      ,             tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S3_C1_2,      ,             tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S3_C2_1,      ,             tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S3_C2_2,      ,             tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S3_C3_1,      ,             tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S3_C3_2,      ,             tmotorTetrix, openLoop)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

#include "JoystickDriver.c"
float TELE_OP_SCALE = 0.85;	// 0.85 = regular, 0.3 = accuramode
#define JOY_SCALE 0.78	//scales down the values from the algorithm for getting motor values from the joystick because otherwise they are too large - is equal to 100 / 128 because 128 is the highest value the joystick has
#define JOY_THRESHOLD 30		//threshold for when joystick value is considered zero, because there is a good amount of noise in the joysticks
#define SQR(val) (val) * (val) // square function`
bool lifted = false; // whether to set the motors
// servo positions
#define CLAW_OPEN 180
#define CLAW_CLOSED 135
#define LIFT_SPEED 80 // lifting motors' speed
#define COUNTER_MAX 60 // for not looping the button commands
#define SERVO_INCREMENT 10 // for tilting the tilter
// button counters - they're incremented when buttons are pressed until they hit COUNTER_MAX
int counterClaw = 0;
int counterTiltForward = 0;
int counterTiltBackward = 0;
int counterSmoothen = 0;

task main()
{
	while (true)
	{
		//reset lifted
		lifted = false;

		// Set up joystick
		getJoystickSettings(joystick);

		// Drive teleop
		float moveX, moveY;
		int rotate;
		if (abs(joystick.joy1_x2) < JOY_THRESHOLD)
		{
			rotate = 0;
		}
		else rotate = joystick.joy1_x2 * TELE_OP_SCALE * JOY_SCALE;
		// Check for noise
		if ((sqrt(SQR(joystick.joy1_x1) + SQR(joystick.joy1_y1)) < JOY_THRESHOLD))
		{
			moveX = 0;
			moveY = 0;
		}
		else
		{
			moveX = joystick.joy1_x1;
			moveY = joystick.joy1_y1;
		}
		// Set the motors
		motor[omniFR] = TELE_OP_SCALE * JOY_SCALE * (moveX - moveY) + rotate;
		motor[omniBR] = TELE_OP_SCALE * JOY_SCALE * (-moveX - moveY) + rotate;
		motor[omniFL] = TELE_OP_SCALE * JOY_SCALE * (moveX + moveY) + rotate;
		motor[omniBL] = TELE_OP_SCALE * JOY_SCALE * (-moveX + moveY) + rotate;

		// set the claw
		if (joy2Btn(2))
		{
			// check the counter
			if (counterClaw < COUNTER_MAX)
			{
				counterClaw++;
			}
			else
			{
				if (ServoValue[servClaw] == CLAW_OPEN)
				{
					servo[servClaw] = CLAW_CLOSED;
				}
				else
				{
					servo[servClaw] = CLAW_OPEN;
				}
				counterClaw = 0;
			}
		}
		else counterClaw = 0;

		// tilt forward
		if (joystick.joy2_y2 > 100)
		{
			if (counterTiltForward < COUNTER_MAX + 20)
			{
				counterTiltForward++;
			}
			else
			{
				if (ServoValue[servL] < 255 - SERVO_INCREMENT)
				{
					servo[servL] += SERVO_INCREMENT;
					servo[servR] -= SERVO_INCREMENT;
				}
				counterTiltForward = 0;
			}
		}
		else if (joystick.joy2_y2 < -100)
		{
			if (counterTiltBackward < COUNTER_MAX)
			{
				counterTiltBackward++;
			}
			else
			{
				if (ServoValue[servL] > SERVO_INCREMENT)
				{
					servo[servL] -= SERVO_INCREMENT;
					servo[servR] += SERVO_INCREMENT;
				}
				counterTiltBackward = 0;
			}
		}
		else
		{
			counterTiltBackward = 0;
			counterTiltForward = 0;
		}

		// the speed toggler for smooth handling
		if (joy1Btn(2))
		{
			if (counterSmoothen < COUNTER_MAX)
			{
				counterSmoothen++;
			}
			else if (counterSmoothen == 0)
			{
				if (TELE_OP_SCALE == 0.85)
				{
					TELE_OP_SCALE = 0.3;
				}
				else TELE_OP_SCALE = 0.85;

				counterSmoothen = -120;
			}
		}
		else counterSmoothen++;

		// the lift buttons are automatic (motors)
		if (joy2Btn(8))
		{
			motor[liftR] = -LIFT_SPEED;
			lifted = true;
		}
		if (joy2Btn(7))
		{
			motor[liftL]= -LIFT_SPEED;
			lifted = true;
		}
		if (joy2Btn(6))
		{
			motor[liftR] = LIFT_SPEED;
			lifted = true;
		}
		if (joy2Btn(5))
		{
			motor[liftL] = LIFT_SPEED;
			lifted = true;
		}
		if (!lifted) // this is to make sure the motors stop
		{
			motor[liftL] = 0;
			motor[liftR] = 0;
		}
	}
}


/////////////////////////////
// Generic Button Counters //
/////////////////////////////
// Buttons can be held down
// to do actions repeatedly
// after a delay
/////////////////////////////

#define BUTTON_DELAY 200
int buttonCount = 0;

if (joy1Btn(5))
{
	if (buttonCount > 0)
		buttonCount--;

	else
	{
		buttonFunction();
		buttonCount = BUTTON_DELAY;
	}
}
else buttonCount = 0;


/////////////////////////////
//   Single-press buttons  //
/////////////////////////////
// Buttons will only toggle
// again once they have been
// released.
/////////////////////////////

bool buttonOne = false;

if (joy1Btn(1))
{
	if (!buttonOne)
	{
		buttonFunction();
		buttonOne = true;
	}
	else {}
}
else buttonOne = false;
