#pragma config(Hubs,  S1, HTMotor,  HTMotor,  none,     none)
#pragma config(Sensor, S2,     irSensor,       sensorHiTechnicIRSeeker1200)
#pragma config(Sensor, S3,     Compass,        sensorI2CHiTechnicCompass)
#pragma config(Motor,  mtr_S1_C1_1,     RightMotor,    tmotorTetrix, PIDControl, encoder)
#pragma config(Motor,  mtr_S1_C1_2,     LeftMotor,     tmotorTetrix, PIDControl, encoder)
#pragma config(Motor,  mtr_S1_C2_1,     AutonomousBlockDispenser, tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C2_2,     motorG,        tmotorTetrix, openLoop)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

#define WHEEL_CIRCUMFERENCE 999.9 // placeholder for actual circumference of wheel with tread around it
#define FIELD_WIDTH 144
#define FIELD_LENGTH 144
#define DIRECTION_MARGIN_OF_ERROR 5

int FieldObstaclesXCoord[] = { 23, 24 }; // X coordinates for grid obstacles on field (dummy values for now)
int FieldObstaclesYCoord[] = { 23, 24 }; // Y coordinates for grid obstacles on field (dummy values for now)
int CurrentYCoord = 0;
int CurrentXCoord = 0;
int InitialDirection = -1;
int DistanceTraveled = 0;

bool IsObstacleOnCoordinates(int X, int Y)
{
	int i;

	// loop through the field's obstacle coordinates and compare them to the X and Y values passed to this subroutine.
	for (i = 0;(i < sizeof(FieldObstaclesXCoord));i++)
	{
		if ((FieldObstaclesXCoord[i] == X) && (FieldObstaclesYCoord[i] == Y))
		{
			return true;
		}
	}
	return false;
}

// before the robot moves to any coordinate, call this to see if it can actually go there
bool CanIMoveToCoordinate(int X, int Y)
{
	// is this coordinate outside the field itself?
	if ((X >= FIELD_WIDTH) || (Y >= FIELD_LENGTH))
	{
		return false;  // can't move there, outside the field.
	}
	else if (IsObstacleOnCoordinates(X, Y)) // Is there an obstacle on the field at this coordinate?
	{
		return false;  // can't move there, something is sitting on that coordinate.
	}
	else
	{
		return true; // otherwise, I can move to that coordinate location.
	}
}

// this subroutine takes a compass sensor reading and sees if it's within the margin of error that's equivalent to the desired heading
bool Near(int Direction, int LastKnownDirection)
{
	// easy case, they are equal so direction hasn't changed, still on same course
	if (Direction == LastKnownDirection)
	{
		return true;
	}

	// uses a counter to check if the robot is within the margin of error before or after the current heading
	for (int i = 1;(i <= DIRECTION_MARGIN_OF_ERROR);i++)
	{
		// check for values below the margin of error
		if ((Direction - i) < 0)
		{
			if ((360 - (Direction - i)) == LastKnownDirection)
			{
				return true;
			}
		}
		else if ((Direction - i) == LastKnownDirection)
		{
			return true;
		}

		// check for values above the margin of error
		if ((Direction + i) > 359)
		{
			if (360 - (Direction + i) == LastKnownDirection)
			{
				return true;
			}
		}
		else if (Direction + i) == LastKnownDirection)
		{
			return true;
		}
	}

	// no matches, just return false
	return false;
}

// calculate robot's heading from compass and how far it has moved since the last time this was called, update current grid location
// by calculating how many grid positions it have moved (and in what direction).
// this can and should be called frequently from the main task loop.
void CurrentPosition()
{
	int CurrentDistanceTraveled;
	int CurrentDirection;
	CurrentDistanceTraveled = (SensorValue[LeftMotor] / 720) * WHEEL_CIRCUMFERENCE;
	CurrentDirection = SensorValue[Compass];
	// reset rotation tick counter since we've already read its value.
	SensorValue[LeftMotor] = 0;
	// now, use distance travelled and heading to calculate where we are on the field.
	if (CurrentDistanceTraveled >= 1)
	{
		if (Near(CurrentDirection, InitialDirection))
		{
			CurrentYCoord += CurrentDistanceTraveled;
		}
		else if (Near(CurrentDirection, ((InitialDirection + 90) % 360)))
		{
			CurrentXCoord += CurrentDistanceTraveled;
		}
		else if (Near(CurrentDirection, ((InitialDirection + 180) % 360)))
		{
			CurrentYCoord -= CurrentDistanceTraveled;
		}
		else if (Near(CurrentDirection, ((InitialDirection + 270) % 360)))
		{
			CurrentYCoord -= CurrentDistanceTraveled;
		}
	}
}

bool isBeaconInRange(tSensors irSensor)	// subroutine that determines whether IR beacon is in range
{
	wait1Msec(1);
	int ir = SensorValue[irSensor];	// defines integer that returns current sensor value
	wait1Msec(1);
	if (ir == 0)	// no beacon detected
	{
		return false;
	}
	else	// beacon detected
	{
		return true;
	}
}

void MoveRobot(int LeftPower, int RightPower)	// subroutine for moving the robot
{
	motor[LeftMotor] = LeftPower;	// assign variable power level to left motor
	motor[RightMotor] = RightPower;	// assign variable power level to right motor
}

void DispenseBlock()	// subroutine to dispense block into bin with IR beacon, will be called when robot reaches box with beacon
{
	motor(AutonomousBlockDispenser) = 100;	// run motor to dispense block
	wait1Msec(3000);	// replace 3000 with amount of time it takes to dispense
	motor(AutonomousBlockDispenser) = 0;	// stop motor after dispensing
}

task main()
{
	InitialDirection = SensorValue[Compass];
	SensorValue[LeftMotor] = 0;
	time1[T1] = 0;
	while(true)
	{
		if (isBeaconInRange(irSensor) == true)
		{
			while (SensorValue[irSensor] != 3 && isBeaconInRange(irSensor) == true)	// while beacon is not in sector 3 and not out of range
			{
				MoveRobot(75, 75);	// move robot forward
			}
			if (SensorValue[irSensor] == 3)	// robot has reached the desired sector
			{
				int TimeDriven = time1[T1];

				MoveRobot(0, 0);	// robot comes to a halt
				DispenseBlock();	// puts block in bin

				if ((TimeDriven > 5) && (TimeDriven < 10))	// moves the robot to the end of the row of baskets
				{
					MoveRobot (75, 75);
					wait1Msec (1000);
					MoveRobot (0,0);
				}

				else if ((TimeDriven > 10) && (TimeDriven < 15)) // moves the robot for less time if it took longer to find the beacon
				{
					MoveRobot (75, 75);
					wait1Msec (800);
					MoveRobot (0,0);
				}

				else if ((TimeDriven > 15) && (TimeDriven < 20))
				{
					MoveRobot (75, 75);
					wait1Msec (600);
					MoveRobot (0,0);
				}

				else if ((TimeDriven > 20) && (TimeDriven < 25))
				{
					MoveRobot (75, 75);
					wait1Msec (400);
					MoveRobot (0,0);
				}

				MoveRobot (75, 75);	// put the code for going up the ramp here
				MoveRobot (0,0);	// stops the robot on the ramp
			}
			else	// robot is out of range
			{
				MoveRobot(-50, -50);
				wait1Msec(100);
				MoveRobot(0, 0);
			}
		}
	}
}
