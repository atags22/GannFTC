#pragma config(Hubs,  S1, HTServo,  HTMotor,  HTMotor,  HTMotor)
#pragma config(Sensor, S1,     ,               sensorI2CMuxController)
#pragma config(Sensor, S2,     comp,           sensorI2CHiTechnicCompass)
#pragma config(Sensor, S3,     ir,             sensorHiTechnicIRSeeker1200)
#pragma config(Sensor, S4,     color,          sensorCOLORFULL)
#pragma config(Motor,  motorA,           ,             tmotorNXT, openLoop)
#pragma config(Motor,  motorB,           ,             tmotorNXT, openLoop)
#pragma config(Motor,  motorC,           ,             tmotorNXT, openLoop)
#pragma config(Motor,  mtr_S1_C2_1,     omniBL,        tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C2_2,     omniBR,        tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C3_1,     omniFL,        tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C3_2,     omniFR,        tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C4_1,     liftL,         tmotorTetrix, PIDControl, encoder)
#pragma config(Motor,  mtr_S1_C4_2,     liftR,         tmotorTetrix, PIDControl, encoder)
#pragma config(Servo,  srvo_S1_C1_1,    rotFL,                tServoStandard)
#pragma config(Servo,  srvo_S1_C1_2,    rotFR,                tServoStandard)
#pragma config(Servo,  srvo_S1_C1_3,    rotBR,                tServoStandard)
#pragma config(Servo,  srvo_S1_C1_4,    rotBL,                tServoStandard)
#pragma config(Servo,  srvo_S1_C1_5,    armBase,              tServoStandard)
#pragma config(Servo,  srvo_S1_C1_6,    armClaw,              tServoStandard)
task main()
{
	motor[omniFL] = 30;
	wait10Msec(100);
	motor[omniFL] = 0;
	motor[omniFR] = 30;
	wait10Msec(100);
	motor[omniFR] = 0;
	motor[omniBL] = 30;
	wait10Msec(100);
	motor[omniBL] = 0;
	motor[omniBR] = 30;
	wait10Msec(100);
}
