#pragma config(Hubs,  S1, HTMotor,  HTMotor,  HTMotor,  HTServo)
#pragma config(Hubs,  S4, HTMotor,  none,     none,     none)
#pragma config(Sensor, S2,     Gyro,           sensorI2CHiTechnicGyro)
#pragma config(Sensor, S3,     IR,             sensorHiTechnicIRSeeker1200)
#pragma config(Motor,  mtr_S1_C1_1,     BR,            tmotorTetrix, PIDControl, encoder)
#pragma config(Motor,  mtr_S1_C1_2,     FR,            tmotorTetrix, PIDControl, encoder)
#pragma config(Motor,  mtr_S1_C2_1,     BlockMoteL,    tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C2_2,     Pullup,        tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C3_1,     BL,            tmotorTetrix, PIDControl, reversed, encoder)
#pragma config(Motor,  mtr_S1_C3_2,     FL,            tmotorTetrix, PIDControl, reversed, encoder)
#pragma config(Motor,  mtr_S4_C1_1,     BlockMoteR,    tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S4_C1_2,     Flag,          tmotorTetrix, openLoop)
#pragma config(Servo,  srvo_S1_C4_1,    Latch,                tServoContinuousRotation)
#pragma config(Servo,  srvo_S1_C4_2,    BlockDrop,            tServoStandard)
#pragma config(Servo,  srvo_S1_C4_3,    BlockServeL,          tServoContinuousRotation)
#pragma config(Servo,  srvo_S1_C4_4,    BlockServeR,          tServoContinuousRotation)
#pragma config(Servo,  srvo_S1_C4_5,    servo5,               tServoNone)
#pragma config(Servo,  srvo_S1_C4_6,    servo6,               tServoNone)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//


////////////////////////////////////////////////////////////////////////////////////////////////////
//                            Hutzbots autonomous mode code abode
////////////////////////////////////////////////////////////////////////////////////////////////////
// 1. Drive forward (?, ? | hit colored line)     // Ready for face a tape
// 2. Rotate left/right (?, ?)                    // Turn to face the tape
// 3. Drive forward (?, ? | IR sensor located)    // Patrol along the tape
// 4. Drive forward (?, ?)                        // Until ready to rotate
// 5. Rotate around (?, ?)                        // Turn to face the ramp
// 6. Drive forward (?, ? | hit the ramp)         // Prepare to go over it
// 7. ? Drive over ramp (?, ? | touch sensor)     // Using sensors for sec
// 8. Drive up ramp (?, ?)                        // Aaaaaaand we're done!
////////////////////////////////////////////////////////////////////////////////////////////////////
// Hutzbots is Josh, Ben, Alex, Laurie, Gabe, Lev, Isabel, and Hodaya.
////////////////////////////////////////////////////////////////////////////////////////////////////

#include "Youtilities.c"
#include "JoystickDriver.c"

//////////////////////////////////////////////////
//                 Driving
//////////////////////////////////////////////////
//float quarterPI = PI / 4;
// This is the radius of the robot radius over the wheel radius.
#define ROBOT_RADIUS_RATIO 5.625
#define WHEEL_RADIUS 11
float forward = degreesToRadians(90);
// dist from edge: 47
//

// first turn
#define TURN_45  980
// 90 turn #define TURN_90  2120

#define STAGE_1  7930 // approach
// 2: rotate 45 side
#define STAGE_3  6900 // total distance
// 3: place block
// 4: sub from stopped block
#define STAGE_6  4700 // sideways
#define STAGE_7  3000 // back (up the ramp?)
// 8: stop

// The distance to go for the block part
long blockDistance = 0;


bool letswait = false; //Delay at start of match?

//////////////////////////////////////////////////
//              Block Placing
//////////////////////////////////////////////////
void stoppingPlaceBlock()
{
	wait10Msec(20);
	Stop();
	wait10Msec(80);
	servoChangeRate[BlockDrop] -= 2;
	servo[BlockDrop] -= 87;
	wait10Msec(90);
	servo[BlockDrop] += 87;
	servoChangeRate[BlockDrop] += 2;
}

//////////////////////////////////////////////////
//                 IR Utils
//////////////////////////////////////////////////
// This is the desired IR value
#define INFRONT_IR 4 // 5 if forward

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


////////////////////////////////////////////////////////////////////////////////////////////////////
//                                      Autonomous Methodology
////////////////////////////////////////////////////////////////////////////////////////////////////
// These methods set the desiredAngle and desiredSpeed values. They're just faster to call.

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
	stageSide(distance, 3.0 * PI / 2.0, speed);
}

void Initialize()
{
	servo[BlockDrop] = 200;



/*	nxtDisplayClearTextLine(4);
	//bNxtLCDStatusDisplay = false;
	eraseDisplay();


//nxtDisplayCenteredBigTextLine(3, "%s", "Press right for reversed.");
//nxtDisplayCenteredBigTextLine(5, "%s", "Press middle for delay.");
	nxtDisplayCenteredTextLine(4, "%s", "Select flipped T or F.");
/*for (int i = 0; i < 3000; i++)
while (true)
{
	if (nNxtButtonPressed == 2)
{
		flipit = false;
		nxtDisplayCenteredTextLine(4, "%s", "FlipIt is disabled."); break;
	}
	else if (nNxtButtonPressed == 1)
	{
		flipit = true;
		nxtDisplayCenteredTextLine(4, "%s", "FlipIt is engaged!"); break;
	}
	else
	{
		nxtDisplayCenteredTextLine(4, "%s", "Select flipped T or F.");
	}
}

wait10Msec(50);
nxtDisplayCenteredTextLine(4, "%s", "Select delay T or F.");

/*for (int i =0 ; i < 3000; i++)while (true)
{
	if (nNxtButtonPressed == 2)
	{
		letswait = false;
		nxtDisplayCenteredTextLine(4, "%s", "Waiting disabled."); break;
	}
	else if (nNxtButtonPressed == 1)
	{
		letswait = true;
		nxtDisplayCenteredTextLine(4, "%s", "Waiting enabled!"); break;
	}
	else nxtDisplayCenteredTextLine(4, "%s", "Select flipped T or F.");
}
wait10Msec(50);
nxtDisplayClearTextLine(4);

*/
}

////////////////////////////////////////////////////////////////////////////////////////////////////
//                                        task main()
////////////////////////////////////////////////////////////////////////////////////////////////////
task main()
{
	Initialize();
	waitForStart();

//if (letswait)
//{
	//wait10Msec(1100); //10 seconds to make the aleph bots happy.
//}

  nMotorEncoder[FL] = nMotorEncoder[FR] = nMotorEncoder[BL] = nMotorEncoder[BR] = 0;

	//return

//////////////////////////////////////////////////
//               Initialization
//////////////////////////////////////////////////
// Set things up, possibly determine red/blue,
// and stuff. Set initial speed towards the thing
//////////////////////////////////////////////////

// Set up red/blue/team settings
// Set initial speed and stuff

//////////////////////////////////////////////////
//                  Looping
//////////////////////////////////////////////////
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
				stageSide(STAGE_1,4.40482 - PI, 60); //InverseTangent(42.5/13.5). Plus Pi. Bad angle drive algorithm.
				break;

			// Rotate left or right
			///////////////////////
			case 2:
			{
				stageRotate(TURN_45, 60, true);
			}
				break;

			// Ready bracket length
			//////////////////////
			case 3:
				stageSide(STAGE_3, PI/2, 75);
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
				// stoppedblock => patrolDistance
				stageSide(blockDistance,PI/2, 75);
				break;

			// Go sideways (right)
			//////////////////////
			case 6:
				stageSide(STAGE_6, PI, 65);
				break;

			// Go backwards
			///////////////
			case 7:
				stageSide(STAGE_7, 3.0 * PI/2.0, 80);
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
				motor[FL] = motor[FR] = motor[BL] = motor[BR] = 0;wait10Msec(10);
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
