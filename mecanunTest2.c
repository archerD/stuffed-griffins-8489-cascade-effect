#pragma config(Hubs,  S1, HTMotor,  none,     none,     none)
#pragma config(Hubs,  S2, HTMotor,  none,     none,     none)
#pragma config(Sensor, S1,     ,               sensorI2CMuxController)
#pragma config(Sensor, S2,     ,               sensorI2CMuxController)
#pragma config(Motor,  motorA,          homeTest,      tmotorNXT, openLoop)
#pragma config(Motor,  motorB,           ,             tmotorNXT, openLoop)
#pragma config(Motor,  motorC,           ,             tmotorNXT, openLoop)
#pragma config(Motor,  mtr_S1_C1_1,     motor1,        tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C1_2,     motor2,        tmotorTetrix, openLoop, reversed)
#pragma config(Motor,  mtr_S2_C1_1,     motor3,        tmotorTetrix, openLoop, reversed)
#pragma config(Motor,  mtr_S2_C1_2,     motor4,        tmotorTetrix, openLoop)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

#include "JoystickDriver.c"

task main()
{
	waitForStart ();   // wait for start of tele-op phase


	//Create "deadzone" variables. Adjust threshold value to increase/decrease deadzone
	int X2 = 0, Y1 = 0, X1 = 0, Y2 = 0, threshold = 15;

	//Loop Forever
	while(1 == 1)
	{
		//
		// Read the current values of the joystick controllers.
		//
		hogCPU (); // Prevent the messaging task from writing to it while it is being read.
		getJoystickSettings (joystick); // Added to template for kick-off presentation
		releaseCPU ();


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
		//Create "deadzone" for Y1/Ch3
		if(abs(joystick.joy1_y1) > threshold)
			Y1 = joystick.joy1_y1;
		else
			Y1 = 0;

		motor[motor1] = -Y1-X1;
		motor[motor2] = -Y2-X2;
		motor[motor3] = -Y2-X2;
		motor[motor4] = -Y1-X1;

		setMotor(homeTest, joystick.joy1_y1);

		//
		// This wait is important for several reasons.  It provides the message
		// a chance to perform its processing.
		//
		wait1Msec (10);

	}
}