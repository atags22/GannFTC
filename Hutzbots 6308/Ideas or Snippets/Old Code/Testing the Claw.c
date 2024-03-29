#pragma config(Hubs,  S1, HTMotor,  HTMotor,  none,     none)
#pragma config(Sensor, S2,     touch,          sensorTouch)
#pragma config(Sensor, S3,     ir,             sensorHiTechnicIRSeeker1200)
#pragma config(Sensor, S4,     compass,        sensorI2CHiTechnicCompass)
#pragma config(Motor,  motorA,           ,             tmotorNXT, openLoop)
#pragma config(Motor,  motorB,           ,             tmotorNXT, openLoop)
#pragma config(Motor,  motorC,           ,             tmotorNXT, openLoop)
#pragma config(Motor,  mtr_S1_C1_1,     omniBR,        tmotorTetrix, PIDControl, encoder)
#pragma config(Motor,  mtr_S1_C1_2,     omniFR,        tmotorTetrix, PIDControl, encoder)
#pragma config(Motor,  mtr_S1_C2_1,     omniBL,        tmotorTetrix, PIDControl, encoder)
#pragma config(Motor,  mtr_S1_C2_2,     omniFL,        tmotorTetrix, PIDControl, encoder)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

//#include "DrivingFunctions.c"

int compassCenter;

void StopMotors ( )
{
	motor[omniBL] = 0; motor[omniBR] = 0;
	motor[omniFL] = 0; motor[omniFR] = 0;
}

void SetMoveMath ( int turn, int power)
{
	//float newPower = power * 0.71 * 0.8;
	int newPower = -power;

	int mathy = degreesToRadians(turn);

	int x = sin(mathy);
	int y = cos(mathy);


	motor[omniFR] = newPower * (x - y);
	motor[omniBR] = newPower * (-x - y);
	motor[omniFL] = newPower * (x + y);
	motor[omniBL] = newPower * (-x + y);
}

void AdjustToCompass ( int turn )
{
	int variance = SensorValue[compass] - compassCenter + turn;
	// -4 ->
	if (variance != 0) // now a very sensitive variance
	{
		motor[omniFL] -= variance;
		motor[omniFR] += variance;

		motor[omniBL] -= variance;
		motor[omniBR] -= variance;
	}
}

// Moves at a direction and speed for a time, and adjusts using the compass. Kill button.
void MoveWithCompassKill ( int turn, int speed, int msec10)
{
	for (int i = 0; i < msec10 / 2; i++)
	{
		if (SensorValue[touch] == 1)
			StopAllTasks();
		SetMoveMath(turn, speed);
		AdjustToCompass(turn);
		wait10Msec(2);
	}
}

task main()
{
	wait10Msec(5);
	compassCenter = SensorValue[compass];
	MoveWithCompassKill(0, 50, 150);
	StopMotors();
	wait10Msec(50);
	MoveWithCompassKill(180, 50, 150);
}
