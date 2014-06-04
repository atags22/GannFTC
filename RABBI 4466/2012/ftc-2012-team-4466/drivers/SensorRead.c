
/**********************************************************************\
*                                                                                                                                                                                                                                                                           *
* PROGRAM: Sensor Reading Programm For Get Over It 2010-2011                *
* VERSION: 1.0                                                                                                                                                                                                              *
* PURPOSE: Controllable task to read certain sensors. This task in    *
*          necessary because there is no thread protection within     *
*          RobotC, which causes procedures to be read twice at once   *
* AUTHOR: Benjamin Chaney                                             *
* DATE:          April 2011                                                                                                                                                                               *
*       In Partnership with Xander Soldat                                                                                                                                                                                                                                                                         *
* LICENSE: GNU GPL V3 2011                                            *
\**********************************************************************/

#ifndef SENSORREAD
#define SENSORREAD
#endif

bool readKalman = true;     /* <!Set true to read Compass and gyro sensors> */
bool gyrocal = false;
bool joyreq = false;
bool readmag = false;

/*
* These are the outputs from the sensor task.
*/

/*
*
*/

bool KalmanRead;
bool joydone;
bool magnetdone;

int CompassReading();
int GyroReading();
int MagnetReading();

int _CompassReading;
int _GyroReading;
int _MagnetReading;


task sensorRead() {
  while(true) {
    if (readKalman) {
      _CompassReading =  HTMCreadHeading(COMPASSPOS);
      _GyroReading =  HTGYROreadRot(GYROPOS);
      KalmanRead = true;
    }

    if (gyrocal){
      HTGYROstartCal(GYROPOS);
      gyrocal = false;
    }
    if (joyreq == true){
      getJoystickSettings(joystick);
      joydone = true;
      joyreq = false;
    }
    if (readmag){
      _MagnetReading = HTMAGreadVal(MAGPOS);
      magnetdone = true;
      readmag = false;
    }
    EndTimeSlice();
  }
}


int CompassReading() {
  KalmanRead = false;
  readKalman = true;
  while (!KalmanRead) {
    readKalman = true;
    EndTimeSlice();
  }
  readKalman = false;
  return _CompassReading;
}

int GyroReading() {
  KalmanRead = false;
  readKalman = true;
  while (!KalmanRead) {
    readKalman = true;
    EndTimeSlice();
  }
  readKalman = false;
  return _GyroReading;
}

int MagnetReading(){
  magnetdone = false;
  readmag = true;
  while(!magnetdone){
    readmag = true;
    EndTimeSlice();
  }
  return _MagnetReading;
}

void getjoystickts() {
  joydone =false;
  joyreq = true;
  while (!joydone){
    joyreq = true;
    EndTimeSlice();
  }
}


/*********************** END IR distance sensors mgmt ****************************/


void calibrategyro() {
  gyrocal = true;
  while (gyrocal){
    EndTimeSlice();
  }
}
