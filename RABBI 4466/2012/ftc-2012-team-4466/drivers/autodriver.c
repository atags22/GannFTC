#ifndef _AUTO_DRIVER
#define _AUTO_DRIVER
#endif


// This code allows the robot to move in a straight line by using the kalman filter to correct it to avoid turning.

void rotate (int x){
  motor[fr] = x;
  motor[fl] = x;
  motor[br] = -x;
  motor[bl] = -x;
}

void faceforward(){
  int spin;
  while(abs(heading) > 3){
    spin = heading % 360;
    if (spin > 180) {
      spin -= 360; // put value between -179 and +180
    }
    if (spin < -180){
      spin += 360;
    }
    motor[fr] = spin;
    motor[fl] = spin;
    motor[br] = -spin;
    motor[bl] = -spin;
  }
  motor[fr] = 0;
  motor[fl] = 0;
  motor[br] = 0;
  motor[bl] = 0;
}


void moveDAS(int Direction, long Motorenc, int speed, bool frontface){
  nMotorEncoder[fr] = 0; // reset motor encoder
  int target = heading;  // set target angle to face
  int spin;
  int angle = Direction - 45;
  int motorx;
  int motory;
  float rotationmatrix[2][2];
  rotationmatrix[0][0] = cosDegrees(angle);
  rotationmatrix[0][1] = sinDegrees(angle);
  rotationmatrix[1][0] = 0 - rotationmatrix[0][1];
  rotationmatrix[1][1] = rotationmatrix[0][0];
  while (abs (nMotorEncoder[fr]) < Motorenc) { // end program when traveled sufficiently
    spin = (target - heading) % 360;  // calculate how far to spin back towards facing direction.
    if (spin > 180) {
      spin -= 360; // put value between -179 and +180
    }
    if (spin < -180){
      spin += 360;
    }
    motorx = 0 * rotationmatrix[0][0] + speed * rotationmatrix[1][0];
    motory = 0 * rotationmatrix[0][1] + speed * rotationmatrix[1][1];
#ifdef KALMOVEDEBUG
    nxtDisplayTextLine(1,"target: "+target);
    nxtDisplayTextLine(2,"heading: "+heading);
    nxtDisplayTextLine(3,"spin: "+ spin);
#endif
    motor[fr] = motorx - spin;
    motor[fl] = 0- motory - spin;
    motor[bl] = motorx + spin;
    motor[br] = 0- motory + spin;
  }
  if (frontface){
    undisturb = true;
    EndTimeSlice();
    wait1Msec(300);
    faceforward();
  }
}

void offramp(){
  moveDAS (0, OFFRAMPDIST, 45, true);
}
