#pragma config(Sensor, S1,			gyro,								 sensorI2CHiTechnicGyro)
#pragma config(Sensor, S2,		 compass,								 sensorI2CHiTechnicCompass)

/* Uncomment to get filter info on the screen */
// #define HEADING_DISPLAY

/* Uncomment when one of the sensors is mounted upside down */
// #define MOUNTING -


#include "heading.c";

task main()
{
  while (true)
  {
    nxtDisplayTextLine(7,"Heading: %3.0f", heading);
    wait1Msec(20);
  }
}


