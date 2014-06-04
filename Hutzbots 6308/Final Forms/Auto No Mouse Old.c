#pragma config(Hubs,  S1, HTMotor,  HTMotor,  HTMotor,  HTServo)
#pragma config(Hubs,  S4, HTMotor,  none,     none,     none)
#pragma config(Sensor, S1,     ,               sensorI2CMuxController)
#pragma config(Sensor, S3,     IR,             sensorHiTechnicIRSeeker1200)
#pragma config(Sensor, S4,     ,               sensorI2CMuxController)
#pragma config(Motor,  mtr_S1_C1_1,     BR,            tmotorTetrix, PIDControl, encoder)
#pragma config(Motor,  mtr_S1_C1_2,     FR,            tmotorTetrix, PIDControl, encoder)
#pragma config(Motor,  mtr_S1_C2_1,     BlockatorTL,   tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C2_2,     PullBottom,    tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C3_1,     BL,            tmotorTetrix, PIDControl, reversed, encoder)
#pragma config(Motor,  mtr_S1_C3_2,     FL,            tmotorTetrix, PIDControl, reversed, encoder)
#pragma config(Motor,  mtr_S4_C1_1,     BlockatorTR,   tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S4_C1_2,     Flag,          tmotorTetrix, openLoop)
#pragma config(Servo,  srvo_S1_C4_1,    PullTop,              tServoContinuousRotation)
#pragma config(Servo,  srvo_S1_C4_2,    BlockDrop,            tServoStandard)
#pragma config(Servo,  srvo_S1_C4_3,    BlockatorBL,          tServoContinuousRotation)
#pragma config(Servo,  srvo_S1_C4_4,    BlockatorBR,          tServoContinuousRotation)
#pragma config(Servo,  srvo_S1_C4_5,    FlagRotater,          tServoStandard)
#pragma config(Servo,  srvo_S1_C4_6,    servo6,               tServoNone)

#include "Youtilities.c"
#include "JoystickDriver.c"

#define INFRONT_IR 5

void stoppingPlaceBlock()
{
	wait10Msec(40);
	Stop();
	wait10Msec(80);
	servoChangeRate[BlockDrop] -= 2;
	servo[BlockDrop] -= 87;
	wait10Msec(150);
	servo[BlockDrop] += 87;
	servoChangeRate[BlockDrop] += 2;
}

#define TURN_45 800
#define STAGE_1  990 // approach from 1130
// 2: rotate 45 side
#define STAGE_3  6850 // total distance from 6560
// 3: place block
// 4: sub from stopped block
#define STAGE_6  5000 // sideways from 5200
#define STAGE_7  3500 // back from 3000

// The distance to go for the block part
long blockDistance = 0;

//////////////////////////////////////////////////
//               Function Utils
//////////////////////////////////////////////////
// What stage in the program the robot is at
ubyte Stage = 1;
// The speed we're going to drive at per tick
int desiredSpeed = 0;
// The distance we need to travel for the next stage
long desiredDistance = 0;
// What kinda drive it is
byte driveType = 0;
// Driving angle
float driveAngle = 0;

void stageRotate(long encoder, int speed, bool nleft)
{
	driveType = 0; if (nleft) speed *= -1;
	desiredDistance = encoder; desiredSpeed = speed;
}

void stageSide(long distance, float angle, int speed)
{
	driveType = 1; driveAngle = angle;
	desiredSpeed = speed; desiredDistance = distance;
}
void stageDrive(long distance, int speed)
{
	//driveType = 1;
	//desiredSpeed = speed; desiredDistance = distance;
	stageSide(distance, PI/ 2.0, speed);
}

task main()
{
	waitForStart();
	wait10Msec(1000); // 10 sec
	while (true)
	{
		/////////////////////////
		//     Switch case
		/////////////////////////
		switch (Stage)
		{
			// Approach the center
			/////////////////////////
			case 1:
				// Should go forward till the turning point
				stageDrive(STAGE_1, 70);
				break;

			// Rotate left or right
			///////////////////////
			case 2:
				stageRotate(TURN_45, 70, true);
				break;

			// Ready bracket length
			//////////////////////
			case 3:
				stageDrive(STAGE_3, 70);
				if (SensorValue[IR] == INFRONT_IR)
				{
					blockDistance = desiredDistance - abs(nMotorEncoder[FL]);
					motor[FL] = motor[FR] = motor[BL] = motor[BR] = 0;wait10Msec(10);
					nMotorEncoder[FL] = 0;
					Stage++;
				}
				break; // In case we're in IR

			// Drop the block inside
			/////////////////////////
			case 4:
				stoppingPlaceBlock();
				Stage++;
				continue; // patrol to the end

			// Patrol to the end
			////////////////////
			case 5:
				// get the distance based on stoppedBlock.
				// I wouldn't mind a switch here but I don't care.
				// stoppedblock => patrolDistance
				stageDrive(blockDistance, 80);
				break;

			// Go sideways (right)
			//////////////////////
			case 6:
				stageSide(STAGE_6, 0, 70);
				break;

			// Go backwards
			///////////////
			case 7:
				stageSide(STAGE_7, 3.0*PI/2.0, 70);
				break;

			// Park on ramp
			///////////////
			case 8:
				Stop();
				return;
		}

		//////////////////////////////////////////////////
		// Apply driving to the wheels for this stage
		//////////////////////////////////////////////////

		if (driveType == 0)
		{
			if (abs(nMotorEncoder[FL]) < desiredDistance)
			{
				// Set the motors to rotate to the speed.
				motor[FR] = motor[BR] = desiredSpeed;
				motor[BL] = motor[FL] = -desiredSpeed;
			}
			else // we have rotated succesfully
			{
				Stop(); wait10Msec(10);
				nMotorEncoder[FL] = 0;
				Stage++;
			}
		}
		else if (driveType == 1) // Regular driving stage
		{
			if (abs(nMotorEncoder[FL]) < desiredDistance) // && nMotorEncoder[FR] < desiredDistance)
			{
				// Set the mecanum wheels to drive at the speed/angle.
				driveMeccanum(desiredSpeed, driveAngle, 1, 0);
			}
			else // we have reached the required distance
			{
				motor[FL] = motor[FR] = motor[BL] = motor[BR] = 0;wait10Msec(10);
				nMotorEncoder[FL] = 0;
				Stage++;
			}
		}

	} // end while
} // end main
