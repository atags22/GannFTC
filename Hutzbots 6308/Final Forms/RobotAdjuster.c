#pragma config(Hubs,  S1, HTMotor,  HTMotor,  HTMotor,  HTServo)
#pragma config(Hubs,  S4, HTMotor,  none,     none,     none)
#pragma config(Sensor, S2,     Compass,        sensorI2CHiTechnicGyro)
#pragma config(Sensor, S3,     IR,             sensorHiTechnicIRSeeker1200)
#pragma config(Motor,  mtr_S1_C1_1,     BR,            tmotorTetrix, PIDControl, encoder)
#pragma config(Motor,  mtr_S1_C1_2,     FR,            tmotorTetrix, PIDControl, encoder)
#pragma config(Motor,  mtr_S1_C2_1,     BlockatorTL,   tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C2_2,     PullBase,      tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C3_1,     BL,            tmotorTetrix, PIDControl, reversed, encoder)
#pragma config(Motor,  mtr_S1_C3_2,     FL,            tmotorTetrix, PIDControl, reversed, encoder)
#pragma config(Motor,  mtr_S4_C1_1,     BlockatorTR,   tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S4_C1_2,     Flag,          tmotorTetrix, openLoop)
#pragma config(Servo,  srvo_S1_C4_1,    PullTop,              tServoContinuousRotation)
#pragma config(Servo,  srvo_S1_C4_2,    AutoBlock,            tServoStandard)
#pragma config(Servo,  srvo_S1_C4_3,    BlockatorBL,          tServoContinuousRotation)
#pragma config(Servo,  srvo_S1_C4_4,    BlockatorBR,          tServoContinuousRotation)
#pragma config(Servo,  srvo_S1_C4_5,    servo5,               tServoNone)
#pragma config(Servo,  srvo_S1_C4_6,    servo6,               tServoNone)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

#include "JoystickDriver.c"

int selectedBase;

void line(int line, char* text)
{
	nxtDisplayCenteredTextLine(line, text);
}
char* selectify(string text, bool selected)
{
	if (selected) return (char*)strcat(strcat(" ", text), " ");
	else          return  StringFormat("<%s>", text); //(char*)"<" + text + ">";
}
char* getSelection(int line, int selection)
{
	bool sel = line == selection;
	switch (line)
	{
		case 1: return selectify("Lift top", sel);
		case 2: return selectify("Lift bottom", sel);
		case 3: return selectify("Blockator top", sel);
		case 4: return selectify("Blockator botm", sel);
		default: return "";
	}
}
void chooserDisplay(int selection)
{
	line(0, "{Select} Adjust ");

	line(1, getSelection(1, selection));
	line(3, getSelection(2, selection));
	line(5, getSelection(3, selection));
	line(7, getSelection(4, selection));
}
void motorDisplay(int side)
{
	line(0, " Select {Adjust}");
	line(2, getSelection(selectedBase, -1));
	switch (side)
	{
		case -1: line(4, "Press LR to turn");
		case 0: line(4, "<<");
		case 1: line(4, ">>");
	}
}
int getMotorSpeed(int dir)
{
	if (dir == -1) return 0;
	else if (dir == 0) return 80;
	else return -80;
}
int getServoSpeed(int dir)
{
	if (dir == -1) return 127;
	else if (dir == 0) return 255;
	else return 0;
}
void setMotoring(int choice)
{
	switch(selectedBase)
	{
		case 1: // lift top
			servo[PullTop] = getServoSpeed(choice);
			break;
		case 2: //lift bottom
			motor[PullBase] = getMotorSpeed(choice);
			break;
		case 3: // blockator top
			motor[BlockatorTL] = motor[BlockatorTR] = getMotorSpeed(choice);
			break;
		case 4:
			if (choice == -1) return;
			else if (choice == 0) { servo[BlockatorBL] += 5; servo[BlockatorBR] += 5; }
			else { servo[BlockatorBL] -= 5; servo[BlockatorBR] -= 5; }
			break;
	}
}

task main()
{
	selectedBase = 1;
	bDisplayDiagnostics = false;
	nNxtExitClicks = 1;
	eraseDisplay();
	while (true)
	{
		chooserDisplay(selectedBase);

		while (nNxtButtonPressed != kButtonCenter)
		{
			if (nNxtButtonPressed == kRightButton)
			{
				if (selectedBase == 4) selectedBase = 1;
				else selectedBase++;
				chooserDisplay(selectedBase);
			}
			else if (nNxtButtonPressed == kLeftButton)
			{
				if (selectedBase == 1) selectedBase = 4;
				else selectedBase--;
				chooserDisplay(selectedBase);
			}
		} // while enter
		while (nNxtButtonPressed == kButtonCenter) { } // wait till release

		motorDisplay(-1); int lastDisplayed = -1;

		while (nNxtButtonPressed != kButtonCenter)
		{
			if (nNxtButtonPressed == kLeftButton)
			{
				if (lastDisplayed != 0)
				{
					lastDisplayed = 0;
					motorDisplay(0);
				}
				setMotoring(0);
			}
			else if (nNxtButtonPressed == kRightButton)
			{
				if (lastDisplayed != 1)
				{
					lastDisplayed = 1;
					motorDisplay(1);
				}
				setMotoring(1);
			}
			else if (nNxtButtonPressed == -1) // none
			{
				if (lastDisplayed != -1)
				{
					lastDisplayed = -1; motorDisplay(-1);
				}
				setMotoring(-1);
			}
		} // end != center #2
		while (nNxtButtonPressed == kEnterButton) { }

	} // 1st while
}
