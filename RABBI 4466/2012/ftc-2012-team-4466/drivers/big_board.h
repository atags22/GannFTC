/*#pragma config(Hubs,  S1, HTMotor,  HTMotor,  HTMotor,  HTServo)
#pragma config(Sensor, S2,     HTPB,                sensorI2CCustom9V)
#pragma config(Sensor, S3,     SMUX_1,              sensorI2CCustom)
#pragma config(Sensor, S4,     SMUX_2,              sensorI2CCustom)
#pragma config(Motor,  mtr_S1_C1_1,     e,             tmotorNormal, openLoop)
#pragma config(Motor,  mtr_S1_C1_2,     a,             tmotorNormal, PIDControl, reversed, encoder)
#pragma config(Motor,  mtr_S1_C2_1,     b,             tmotorNormal, PIDControl, reversed, encoder)
#pragma config(Motor,  mtr_S1_C2_2,     c,             tmotorNormal, PIDControl, encoder)
#pragma config(Motor,  mtr_S1_C3_1,     f,             tmotorNormal, PIDControl, encoder)
#pragma config(Motor,  mtr_S1_C3_2,     d,             tmotorNormal, PIDControl, encoder)
#pragma config(Servo,  srvo_S1_C4_1,    frontarm,             tServoStandard)
#pragma config(Servo,  srvo_S1_C4_2,    backarm,              tServoStandard)
#pragma config(Servo,  srvo_S1_C4_3,    dispencer,            tServoStandard)
#pragma config(Servo,  srvo_S1_C4_4,    Irpullup,             tServoStandard)
#pragma config(Servo,  srvo_S1_C4_5,    Irfront,              tServoStandard)
#pragma config(Servo,  srvo_S1_C4_6,    Irback,               tServoStandard)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*/

 /**********************************************************************\
*                                                                                                                                                                                                                                                                                *
* PROGRAM: Big Board                                                                                                                                      *
* VERSION: 1.2                                                                                                                                                                                                              *
* AUTHOR: Team R.A.B.B.I                                              *
* DATE:          April 2011                                                                                                                                                                               *
*                                                                                                                                                                                                                                                                                 *
* LICENSE: GNU GPL V3 2011                                            *
\**********************************************************************/

#define MAGTHREASHOLD 4
#define MAGDELAY 0

#define XLIFTLOW 0
#define XLIFTHIGH 0x7fff

#ifndef BIG_BOARD
#define BIG_BOARD
#endif

//Definitions for the different sensor ports
#define MAGPOS msensor_S4_3
#define COMPASSPOS S3
#define GYROPOS S2

#define RIGHTSD true
#define LEFTSD false

#define REDCL true
#define BLUECL false

#define OFFRAMPDIST 3800
#define LRADJUST 2000
#define SIDESTEP 1000
#define FORWARDTOCRATES 2100 //measure
#define PREPTOHIT 750 // measure
#define HITTIN 3000 //measure
#define PARKFRONT 6000 //measure
#define BBSETUP 1000
#define BBCROSS 8500 //measure

#define FIRSTHIT 1500 //measure
#define SECONDHIT 2000//measure
#define THIRDHIT 1500//measure
#define WOGFINISH 3000
