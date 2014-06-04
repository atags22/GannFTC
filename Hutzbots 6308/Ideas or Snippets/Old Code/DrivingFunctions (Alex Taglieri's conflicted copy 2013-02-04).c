#pragma config(Hubs,  S1, HTMotor,  HTMotor,  HTServo,  none)
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
#pragma config(Servo,  srvo_S1_C3_1,    servo1,               tServoNone)
#pragma config(Servo,  srvo_S1_C3_2,    servo2,               tServoNone)
#pragma config(Servo,  srvo_S1_C3_3,    servo3,               tServoNone)
#pragma config(Servo,  srvo_S1_C3_4,    servo4,               tServoNone)
#pragma config(Servo,  srvo_S1_C3_5,    servo5,               tServoNone)
#pragma config(Servo,  srvo_S1_C3_6,    servo6,               tServoNone)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

// Used in setting driving, compass angles.
int DesiredAngle = 0;

// The motors.
int FL = 0, FR = 0, BL = 0, BR = 0;

#define VARIANCE_NOISE 4 // used in making sure the robot is aligned

// Gets the difference between two angles
int getVariance(int record, int newAngle)
{
	if (abs(record - newAngle) > 180)
		return 360 - abs(record - newAngle);

	return record - newAngle;
}

// write to screen
void Debug()
{
	nxtDisplayCenteredTextLine(0, "Compass = %d", SensorValue[compass]);
	nxtDisplayCenteredTextLine(1, "Desired = %d", DesiredAngle);
	nxtDisplayCenteredTextLine(2, "Variance = %d", getVariance(SensorValue[compass], DesiredAngle));
	nxtDisplayCenteredTextLine(4, "FL: %d FR: %d", motorPowerSigned[omniFL], motorPowerSigned[omniFR]);
	nxtDisplayCenteredTextLine(6, "BL: %d BR: %d", motorPowerSigned[omniBL], motorPowerSigned[omniBR]);
}

// set up stuff
void InitializeRobot ( )
{
	nMotorPIDSpeedCtrl[omniBL] = mtrSpeedReg;
	nMotorPIDSpeedCtrl[omniBR] = mtrSpeedReg;
	nMotorPIDSpeedCtrl[omniFL] = mtrSpeedReg;
	nMotorPIDSpeedCtrl[omniFR] = mtrSpeedReg;
	wait10Msec(10); // let el compassio work man
	//CompassBase = SensorValue[compass];
	//nxtDisplayCenteredTextLine(0, "Initial compass: %d", CompassBase);
	//Debug();
}

void SetMoveDirection (int X, int Y)
{
		motor[omniFR] = X - Y;
		motor[omniBR] = -X - Y;
		motor[omniFL] = X + Y;
		motor[omniBL] = -X + Y;
}

void SetMoveMath ( int turn, int power)
{
	float newPower = power * 0.71 * 0.8;

	DesiredAngle = SensorValue[compass] + turn; // weeeeeeeeeeeeeeeeeee

	int mathy = degreesToRadians(turn);

	int x = sin(mathy);
	int y = cos(mathy);


	FR = newPower * (x - y);
	BR = newPower * (-x - y);
	FL = newPower * (x + y);
	BL = newPower * (-x + y);
}

void SetTurn ( int degrees )
{
	motor[omniFL] = degrees;
	motor[omniFR] = degrees;
	motor[omniBL] = degrees;
	motor[omniBR] = degrees;
}

void SetMotors ( int num = 0 )
{
	motor[omniBL] = num;
	motor[omniFL] = num;
	motor[omniFR] = num;
	motor[omniBR] = num;
}

void UpdateMotors ( )
{
	motor[omniBL] = BL;
	motor[omniBR] = BR;
	motor[omniFL] = FL;
	motor[omniFR] = FR;
}

void waitAndKillReady(int delay)
{
	for (int i = 0; i < delay*0.91; i++)
	{
		if (SensorValue[S2] == 1)
			StopAllTasks();
		wait1Msec(1);
	}
}

void holdOn ( int pause )
{
	SetMotors();
	waitAndKillReady(pause);
}

void SetLift ( byte height )
{
	// height = 1, 2, 3, 11, 21, 31
	// test

}

void AdjustToCompass ( )
{
	int vary = getVariance(DesiredAngle, SensorValue[compass]);

	if (abs(vary) > VARIANCE_NOISE)
	{
		vary *= 0.2; // we'll just half it to convert it to motor power values

		FL -= vary;
		FR -= vary;
		BL -= vary;
		BR -= vary;
	}
}

void WaitAndAdjust(int Tmil)
{
	for (int i = 0; i < Tmil; i++)
	{
		wait10Msec(2);
		AdjustToCompass();
		UpdateMotors();
		Debug();
	}
}

task main ( )
{
	InitializeRobot();

	SetMoveMath(0, 20);
	WaitAndAdjust(1500);
	//holdOn(10);

	//SetMoveMath(90, 40);
	//WaitAndAdjust(100);
}
