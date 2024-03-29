#pragma config(Hubs,  S1, HTMotor,  HTMotor,  HTMotor,  HTServo)
#pragma config(Sensor, S2,     Comp,           sensorI2CHiTechnicCompass)
#pragma config(Sensor, S3,     IR,             sensorHiTechnicIRSeeker1200)
#pragma config(Motor,  mtr_S1_C1_1,     BR,            tmotorTetrix, PIDControl, encoder)
#pragma config(Motor,  mtr_S1_C1_2,     FR,            tmotorTetrix, PIDControl, encoder)
#pragma config(Motor,  mtr_S1_C2_1,     Amry,          tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C2_2,     Flaggy,        tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C3_1,     BL,            tmotorTetrix, PIDControl, reversed, encoder)
#pragma config(Motor,  mtr_S1_C3_2,     FL,            tmotorTetrix, PIDControl, reversed, encoder)
#pragma config(Servo,  srvo_S1_C4_1,    Latch,                tServoContinuousRotation)
#pragma config(Servo,  srvo_S1_C4_2,    BlockDrop,            tServoStandard)
#pragma config(Servo,  srvo_S1_C4_3,    servo3,               tServoNone)
#pragma config(Servo,  srvo_S1_C4_4,    servo4,               tServoNone)
#pragma config(Servo,  srvo_S1_C4_5,    servo5,               tServoNone)
#pragma config(Servo,  srvo_S1_C4_6,    servo6,               tServoNone)
//*!!Code automatically generated by 'ROBOTC' configuration wizard
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//
////////////////////////////////////////////////////////////////////////////////////////////////////
//                                   Utilities for Hutzbots Code
////////////////////////////////////////////////////////////////////////////////////////////////////
// Containing driving, compass, internal workings, and utility functions for the Hutzbots robot.
////////////////////////////////////////////////////////////////////////////////////////////////////


//so that it is easy to change which button is used for line following.
//////////////////////////////////////////////////
//                 Compass
//////////////////////////////////////////////////
int userAngle = 0;
int robotAngle;
float quarterPI = PI / 4;
void setProxiesToAngle(int angle, int speed)
{
	// Angle and theta in given triangles

}

void Stop()
{
	motor[FL] = motor[FR] = motor[BL] = motor[BR] = 0;
}

//////////////////////////////////////////////////
//                 Driving
//////////////////////////////////////////////////
void driveRobot(float speed, float theta, float factor = 0, int rotate = 0)
{
	motor[FL] = motor[BR] = round(speed * sin(theta - quarterPI) * factor + (rotate * factor));
	motor[FR] = motor[BL] = round(speed * cos(theta - quarterPI) * factor + (rotate * factor));
}

void driveMeccanum(float speed, float theta, float factor = 0, int rotate = 0)
{
	motor[FL] = round(speed * +sin(theta + quarterPI) * factor - (rotate * factor));
	motor[BR] = round(speed * +sin(theta + quarterPI) * factor + (rotate * factor));
	motor[FR] = round(speed * -cos(theta + quarterPI) * factor + (rotate * factor));
	motor[BL] = round(speed * -cos(theta + quarterPI) * factor - (rotate * factor));
}

//////////////////////////////////////////////////
//               Internal Workings
//////////////////////////////////////////////////
void raiseLift();
void spinConveyorBelt();

// while true
// case 1
// setValues(angle, speed, time)
// case 2
// setVakuyes(ang, sp, ti)
// if (sensor)
//

//////////////////////////////////////////////////
//                   Others
//////////////////////////////////////////////////

void getRobotAngle()
{
	robotAngle = SensorValue(Comp);
	wait1Msec(50);
}



int sqr (int input)
{ return input * input; }


float angleOffset(float angle1, float angle2)
{
	if (abs(angle1 - angle2) > 180)
		return 360 - abs(angle1 - angle2);

	return angle1 - angle2;
}
float addAngles(float angle1, float angle2)
{
	float sum = angle1 + angle2;

	if (sum > 360)
		return 360 - sum;

	if (sum < 0)
		return 360 + sum;

	return sum;
}

///////////////////////////////////////////////////
//
//                Music
//
//
///////////////////////////////////////////////////
task LaCucaRacha()
{
	PlayTone(  523,   14); wait1Msec( 150);  // Note(C, Duration(16th))
	PlayTone(  523,   14); wait1Msec( 150);  // Note(C, Duration(16th))
	PlayTone(  523,   14); wait1Msec( 150);  // Note(C, Duration(16th))
	PlayTone(  698,   14); wait1Msec( 200);  // Note(F, Duration(16th))
	PlayTone(  880,   14); wait1Msec( 150);  // Note(A, Duration(16th))
	PlayTone(  523,   14); wait1Msec( 150);  // Note(C, Duration(16th))
	PlayTone(  523,   14); wait1Msec( 150);  // Note(C, Duration(16th))
	PlayTone(  523,   14); wait1Msec( 150);  // Note(C, Duration(16th))
	PlayTone(  698,   14); wait1Msec( 200);  // Note(F, Duration(16th))
	PlayTone(  880,   14); wait1Msec( 250);  // Note(A, Duration(16th))
	PlayTone(  698,   14); wait1Msec( 150);  // Note(F, Duration(16th))
	PlayTone(  698,   14); wait1Msec( 150);  // Note(F, Duration(16th))
	PlayTone(  659,   14); wait1Msec( 150);  // Note(E, Duration(16th))
	PlayTone(  659,   14); wait1Msec( 150);  // Note(E, Duration(16th))
	PlayTone(  587,   14); wait1Msec( 150);  // Note(D, Duration(16th))
	PlayTone(  587,   14); wait1Msec( 150);  // Note(D, Duration(16th))
	PlayTone(  523,   14); // wait1Msec( 150);  // Note(C, Duration(16th))
}
task HappyBirthday()
{
	PlayTone(  523,   14); wait1Msec(150);  // Note(C, Duration(16th))
	PlayTone(  523,   14); wait1Msec(150);  // Note(C, Duration(16th))
	PlayTone(  587,   14); wait1Msec(150);  // Note(D, Duration(16th))
	PlayTone(  523,   14); wait1Msec(150);  // Note(C, Duration(16th))
	PlayTone(  698,   14); wait1Msec(150);  // Note(F, Duration(16th))
	PlayTone(  659,   14); wait1Msec(150);  // Note(E, Duration(16th))

	PlayTone(  523,   14); wait1Msec(150);  // Note(C, Duration(16th))
	PlayTone(  523,   14); wait1Msec(150);  // Note(C, Duration(16th))
	PlayTone(  587,   14); wait1Msec(150);  // Note(D, Duration(16th))
	PlayTone(  523,   14); wait1Msec(150);  // Note(C, Duration(16th))
	PlayTone(  783,   14); wait1Msec(150);  // Note(G, Duration(16th))
	PlayTone(  698,   14); wait1Msec(150);  // Note(F, Duration(16th))

	PlayTone(  523,   14); wait1Msec(150);  // Note(C, Duration(16th))
	PlayTone(  523,   14); wait1Msec(150);  // Note(C, Duration(16th))
	PlayTone(  1046,  14); wait1Msec(150);  // Note(C, Duration(16th))
	PlayTone(  880,   14); wait1Msec(150);  // Note(A, Duration(16th))
	PlayTone(  698,   14); wait1Msec(150);  // Note(F, Duration(16th))
	PlayTone(  659,   14); wait1Msec(150);  // Note(E, Duration(16th))
	PlayTone(  587,   14); wait1Msec(150);  // Note(D, Duration(16th))

	PlayTone(  932,   14); wait1Msec(150);  // Note(A#, Duration(16th))
	PlayTone(  932,   14); wait1Msec(150);  // Note(A#, Duration(16th))
	PlayTone(  880,   14); wait1Msec(150);  // Note(A, Duration(16th))
	PlayTone(  698,   14); wait1Msec(150);  // Note(F, Duration(16th))
	PlayTone(  783,   14); wait1Msec(150);  // Note(G, Duration(16th))
	PlayTone(  698,   14);// wait1Msec(150);  // Note(F, Duration(16th))
}
