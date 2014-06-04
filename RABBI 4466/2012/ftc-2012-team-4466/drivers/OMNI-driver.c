#pragma systemFile

#ifndef OMNIDRIVER
#define OMNIDRIVER
#endif

int Jdrivefr = 0;
int Jdrivefl = 0;
int Jdrivebl = 0;
int Jdrivebr = 0;

task Jdrive {
  int joyx;
  int joyy;
  int theda;
  int robotx;
  int roboty;
  int spin[4];
  float rotationmatrix[2][2];
  while (true){
    getjoystickts();
    if((joystick.joy1_x1/1.8) > 12 || (joystick.joy1_x1/1.8) < -12) {
      spin[0] = -1 * joystick.joy1_x1/3;
      spin[1] = -1 * joystick.joy1_x1/3;
      spin[2] = joystick.joy1_x1/3;
      spin[3] = joystick.joy1_x1/3; }
    else {
      spin[0] = 0;
      spin[1] = 0;
      spin[2] = 0;
      spin[3] = 0;
    }

    //end of readings for "omin-spin" and they are stored in the array Spin, which each spot corresponding to a motor
    //Start of joystick readings for driving
    getjoystickts();

    joyx = joystick.joy1_x2/1.27;
    joyy = -1 * joystick.joy1_y2/1.27;


    int theda = 0- heading - 45; // calculate offset of angle
    theda %= 360;

    rotationmatrix[0][0] = cosDegrees(theda);
  rotationmatrix[0][1] = sinDegrees(theda);
  rotationmatrix[1][0] = 0 - rotationmatrix[0][1];
  rotationmatrix[1][1] = rotationmatrix[0][0];
    //initialize rotation matrix

    robotx = joyx * rotationmatrix[0][0] + joyy * rotationmatrix[1][0];
    roboty = joyx * rotationmatrix[0][1] + joyy * rotationmatrix[1][1];
    //matrix multiplication of rotation matrix versus vector matrix

    Jdrivefr = 0 - robotx + spin[0];
    Jdrivefl = roboty + spin[1];
    Jdrivebl = 0 - robotx + spin[2];
    Jdrivebr = roboty + spin[3];
    //put information in global variables to be accesed by drive procudure when called by main.
    wait1Msec(20);
  }
}
