#pragma config(Hubs,  S1, HTServo,  HTMotor,  HTMotor,  none)
#pragma config(Hubs,  S2, HTMotor,  none,     none,     none)
#pragma config(Sensor, S3,     irSensor,       sensorHiTechnicIRSeeker1200)
#pragma config(Sensor, S4,     Gyro,           sensorI2CHiTechnicGyro)
#pragma config(Motor,  mtr_S1_C2_1,     motorF,        tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C2_2,     motorG,        tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C3_1,     motorH,        tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C3_2,     motorI,        tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S2_C1_1,     LeftDrive,     tmotorTetrix, openLoop, reversed, encoder)
#pragma config(Motor,  mtr_S2_C1_2,     RightDrive,    tmotorTetrix, openLoop, encoder)
#pragma config(Servo,  srvo_S1_C1_1,    servo1,               tServoNone)
#pragma config(Servo,  srvo_S1_C1_2,    servo2,               tServoNone)
#pragma config(Servo,  srvo_S1_C1_3,    AutonomousDispenser,  tServoStandard)
#pragma config(Servo,  srvo_S1_C1_4,    servo4,               tServoNone)
#pragma config(Servo,  srvo_S1_C1_5,    servo5,               tServoNone)
#pragma config(Servo,  srvo_S1_C1_6,    servo6,               tServoNone)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

void moveRobot(int LeftPower, int RightPower)   // subroutine for moving the robot
{
    motor[LeftDrive] = LeftPower;   // assign variable power level to left motor
    motor[RightDrive] = RightPower; // assign variable power level to right motor
}

void turnLeft()
{
	int degreesToTurn = 90;
	float degreesSoFar = 0;
	int initialTurnReading = SensorValue[Gyro];

	moveRobot(-75, 75);

	while (abs(degreesSoFar) < abs(degreesToTurn))
	{
		wait1Msec(10);
		int currentGyroReading = SensorValue[Gyro] - initialTurnReading;
		degreesSoFar = (degreesSoFar + (currentGyroReading * .01));
	}

	moveRobot(0, 0);
}

void turnRight()
{
	int degreesToTurn = -90;
	float degreesSoFar = 0;
	int initialTurnReading = SensorValue[Gyro];

	moveRobot(75, -75);

	while (abs(degreesSoFar) < abs(degreesToTurn))
	{
		wait1Msec(10);
		int currentGyroReading = SensorValue[Gyro] - initialTurnReading;
		degreesSoFar = (degreesSoFar + (currentGyroReading * .01));
	}

	moveRobot(0, 0);
}

task main()
{
	turnRight();
	//nxtDisplayCenteredBigTextLine(2, SensorValue[Gyro]);
	}