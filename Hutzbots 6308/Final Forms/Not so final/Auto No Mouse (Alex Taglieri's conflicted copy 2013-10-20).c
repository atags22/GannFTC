//////////////////////////////////////////////////
//    Hutzbots autonomous mode code abode
//////////////////////////////////////////////////
// Drive till the colored box, follow the lines,
// drop in beaconed basket, turn to face the
// ramp, drive up it, ???????, profit. Win.
//////////////////////////////////////////////////
// Hutzbots is Josh, Ben, Alex, Laurie, Gabe,
// Lev, Isablel, and Hodaya.

//////////////////////////////////////////////////
//                 Driving
//////////////////////////////////////////////////
// red vs blue, left vs right, determined
// by beacon when the colored box is hit.
byte team = 0;
float desiredAngle = 0;
float desiredSpeed = 0;
float deisredDelay = 0;


//////////////////////////////////////////////////
//               Line Tracking
//////////////////////////////////////////////////
#define COLOR_RED 0
#define COLOR_BLUE 0
#define COLOR_GROUND 0
#define COLOR_RAMP 0
#define COLOR_RANGE 5
#define SENSOR_ONE 0
#define SENSOR_TWO 1
#define SENSOR_BOTH 2
//void determineColor(byte color, byte sensorToUse); // change this
void correctProxiesForColor(byte color);

//////////////////////////////////////////////////
//              Block Placing
//////////////////////////////////////////////////
#define PLACING_TICK_TIME 9001
#define PLACING_MOVE_SPEED 0
#define PLACING_MOVE_TIME 9001
void initPlaceBlock();

//////////////////////////////////////////////////
//                 IR Utils
//////////////////////////////////////////////////
#define INFRONT_IR 5

//////////////////////////////////////////////////
//                Ramp Utils
//////////////////////////////////////////////////
#define RAMP_TIME 9001
// The speed at which to travel up the ramp.
#define RAMP_SPEED 60
int rampDriveTimer = 0;

//////////////////////////////////////////////////
//          Stepping Utilities
//////////////////////////////////////////////////
#define S1_TIME 0
#define S2_TIME 1
#define S3_TIME 2
#define S4_TIME 3
#define S5_TIME 4

//////////////////////////////////////////////////
//               Navigation
//////////////////////////////////////////////////
// TBR

//////////////////////////////////////////////////
//                task main()
//////////////////////////////////////////////////
task main()
{

//////////////////////////////////////////////////
//               Initialization
//////////////////////////////////////////////////
// Set things up, possibly determine red/blue,
// and stuff. Set initial speed towards the
//////////////////////////////////////////////////

//////////////////////////////////////////////////
//                 Looping
//////////////////////////////////////////////////
	while (true)
	{
		switch (Stage)
		{
			case stages.
		}

	// apply wheels

	// ^loop
	}
}
