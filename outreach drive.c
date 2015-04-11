#pragma config(Hubs,  S1, HTMotor,  HTMotor,  none,     none)
#pragma config(Motor,  motorA,           ,             tmotorNXT, openLoop)
#pragma config(Motor,  motorB,           ,             tmotorNXT, openLoop)
#pragma config(Motor,  motorC,           ,             tmotorNXT, openLoop)
#pragma config(Motor,  mtr_S1_C1_1,     motor2,        tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C1_2,     motor1,        tmotorTetrix, openLoop, reversed)
#pragma config(Motor,  mtr_S1_C2_1,     motor4,        tmotorTetrix, openLoop, reversed)
#pragma config(Motor,  mtr_S1_C2_2,     motor3,        tmotorTetrix, openLoop)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

#include "joystickDriver.c";

task main()
{
	waitForStart();   // wait for start of tele-op phase

	//Create "deadzone" variables. Adjust threshold value to increase/decrease deadzone
	int X2 = 0, Y1 = 0, X1 = 0, threshold = 5;

	int driveDirection = 0;

	while (true)
	{
		//get joystick settings
		getJoystickSettings(joystick);

		//Create "deadzone" for Y1/Ch3
		if(abs(joystick.joy1_y1) > threshold)
			Y1 = joystick.joy1_y1;
		else
			Y1 = 0;
		//Create "deadzone" for X1/Ch4
		if(abs(joystick.joy1_x1) > threshold)
			X1 = joystick.joy1_x1;
		else
			X1 = 0;
		//Create "deadzone" for X2/Ch1
		if(abs(joystick.joy1_x2) > threshold)
			X2 = joystick.joy1_x2;
		else
			X2 = 0;


		if(joystick.joy1_TopHat != -1)
			driveDirection = joystick.joy1_TopHat;

		switch (driveDirection)
		{
		case 4:
		Y1 = -Y1;
		X1 = -X1;
		X2 = -X2;
		break;

		default:
		break;
		}

		//Remote Control Commands
		motor[motor2] = Y1 - X2 + X1;
		motor[motor3] =  Y1 - X2 - X1;
		motor[motor1] = Y1 + X2 - X1;
		motor[motor4] =  Y1 + X2 + X1;
	}
}