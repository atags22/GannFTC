/**********************************************************************\
*                                                                                                                                                                                                                                                                           *
* PROGRAM: Common file for Get Over It 2010-2011                                                  *
* VERSION: 2.0                                                                                                                                                                                                              *
* PURPOSE: Common file holding all common procedures                  *
* AUTHOR: Team R.A.B.B.I.                                             *
* DATE:          April 2011                                                                                                                                                                               *
*                                                                                                                                                                                                                                                                                 *
* LICENSE: GNU GPL V3 2011                                            *
\**********************************************************************/


/*
* Movements for Omni-bot according to above diagram
* @pragma speed: speed for the robot to travel from 0-100
* @void drive: @pragma percent: percent speed for all movements. From 0-100
*/

#pragma systemFile
#ifndef __RABBI_COMMON__
#define __RABBI_COMMON__
#endif

bool _isBetween(int x, int threshold, int plusMinus) {
  if (clip(x, threshold - plusMinus, threshold + plusMinus) == x) {
    return true;
  }
  return false;
}


void stopmot() {
  motor[fr]=0;
  motor[fl]=0;
  motor[br]=0;
  motor[bl]=0;
  wait10Msec(10);
}
void left(int speed){
  motor[bl]=speed;
  motor[fl]=speed;
  motor[fr]=speed ;
  motor[br]=speed;
}
void right(int speed){
  motor[bl]= -speed;
  motor[fl]= -speed;
  motor[fr]= -speed;
  motor[br]= -speed;
}
void forward(int speed){
  motor[bl]=speed;
  motor[fl]=-speed;
  motor[fr]=speed;
  motor[br]=-speed;}
void backward (int speed){
  motor[bl]=-speed;
  motor[fl]=speed;
  motor[fr]=-speed;
  motor[br]=speed;
}
void clk(int speed) {
  motor[bl] = speed;
  motor[fl] = speed;
  motor[fr] = -speed;
  motor[br] = -speed;
}

void cntClk(int speed) {
  motor[bl] = -speed;
  motor[fl] = -speed;
  motor[fr] = speed;
  motor[br] = speed;
}

void drive(int percent) {
  motor[bl] = ((float)Jdrivebl)* (((float)percent)/100);
  motor[fl] = ((float)Jdrivefl)* (((float)percent)/100);
  motor[fr] = ((float)Jdrivefr)* (((float)percent)/100);
  motor[br] = ((float)Jdrivebr)* (((float)percent)/100);
}
task magnetdetect{
  wait1Msec(MAGDELAY);
      // servo move
}
