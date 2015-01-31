#pragma config(Hubs,  S1, HTMotor,  HTMotor,  none,     none)
#pragma config(Hubs,  S2, HTServo,  none,     none,     none)
#pragma config(Hubs,  S3, HTMotor,  HTMotor,  none,     none)
#pragma config(Sensor, S1,     ,               sensorI2CMuxController)
#pragma config(Sensor, S2,     ,               sensorI2CMuxController)
#pragma config(Sensor, S3,     ,               sensorI2CMuxController)
#pragma config(Motor,  motorA,           ,             tmotorNXT, openLoop)
#pragma config(Motor,  motorB,           ,             tmotorNXT, openLoop)
#pragma config(Motor,  motorC,           ,             tmotorNXT, openLoop)
#pragma config(Motor,  mtr_S1_C1_1,     motor1,        tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C1_2,     motor2,        tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C2_1,     motor3,        tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C2_2,     motor4,        tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S3_C1_1,     intake,        tmotorTetrix, openLoop, reversed)
#pragma config(Motor,  mtr_S3_C1_2,     conveyor,      tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S3_C2_1,     armMotor1,     tmotorTetrix, PIDControl, reversed, encoder)
#pragma config(Motor,  mtr_S3_C2_2,     armMotor2,     tmotorTetrix, PIDControl, encoder)
#pragma config(Servo,  srvo_S2_C1_1,    goalGripper,          tServoStandard)
#pragma config(Servo,  srvo_S2_C1_2,    armServo1,            tServoStandard)
#pragma config(Servo,  srvo_S2_C1_3,    armServo2,            tServoStandard)
#pragma config(Servo,  srvo_S2_C1_4,    ballGuard,            tServoStandard)
#pragma config(Servo,  srvo_S2_C1_5,    servo5,               tServoNone)
#pragma config(Servo,  srvo_S2_C1_6,    servo6,               tServoNone)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

/////////////////////////////////////////////////////////////////////////////////////////////////////
//
//                              Autonomous Testing Code
//
// This file is designed so autonomous testing can be done without the FCS.  It would be a good
// idea to test in this file before editing master auto.
//
// Please update when changes are made to master auto.
//
/////////////////////////////////////////////////////////////////////////////////////////////////////

#include "StuffedGriffinsFunctions.c" //Stuffed Griffins functions

/////////////////////////////////////////////////////////////////////////////////////////////////////
//
//                                    initializeRobot
//
// Prior to the start of autonomous mode, you may want to perform some initialization on your robot.
// Things that might be performed during initialization include:
//   1. Move motors and servos to a preset position.
//   2. Some sensor types take a short while to reach stable values during which time it is best that
//      robot is not moving. For example, gyro sensor needs a few seconds to obtain the background
//      "bias" value.
//
// In many cases, you may not have to add any code to this function and it will remain "empty".
//
/////////////////////////////////////////////////////////////////////////////////////////////////////

// Declaring global variables, which will be set in the init routine.
bool ramp;
bool rollingGoal = false;
bool centerGoal = false;
bool kickstand = false;
TFileHandle readFrom;
TFileIOResult result;

// to read the data from autoWriter
byte lastRead()
{
	byte N;
	TFileIOResult result;
	ReadByte(readFrom, result, N);
	return N;
}

void initializeRobot()
{
	// setting auto program variables

	word currentSize;
	OpenRead(readFrom, result, "auto.txt", currentSize);

	//read the byte with the ramp data and set the variable ramp
	byte read = lastRead();
	if(read == 1)
	{
		ramp = true;
	}
	else if(read == 2)
	{
		ramp = false;
	}

	//read the byte with the rolling goal data and set the variable rollingGoal
	read = lastRead();
	if(read == 1)
	{
		rollingGoal = true;
	}

	//read the byte with the center goal data and set the variable centerGoal
	read = lastRead();
	if(read == 1)
	{
		centerGoal = true;
	}

	//read the byte with the kickstand data and set the variable kickstand
	read = lastRead();
	if(read == 1)
	{
		kickstand = true;
	}

	Close(readFrom, result);

	return;
}


/////////////////////////////////////////////////////////////////////////////////////////////////////
//
//                                         Main Task
//
// The following is the main code for the autonomous robot operation. Customize as appropriate for
// your specific robot.
//
// The types of things you might do during the autonomous phase (for the 2008-9 FTC competition)
// are:
//
//   1. Have the robot follow a line on the game field until it reaches one of the puck storage
//      areas.
//   2. Load pucks into the robot from the storage bin.
//   3. Stop the robot and wait for autonomous phase to end.
//
// This simple template does nothing except play a periodic tone every few seconds.
//
// At the end of the autonomous period, the FMS will autonmatically abort (stop) execution of the program.
//
/////////////////////////////////////////////////////////////////////////////////////////////////////

task main()
{
	initializeRobot();

	ramp = true;
	rollingGoal = true;
	waitForStart();

	//if starting from the ramp
	if(ramp)
	{
		transitionYAxis(0, -50);
		autoDrive(1.85, 0, -50, 12);
		wait1Msec(500);
		//if collecting the rolling goal
		if(rollingGoal)
		{
			//open servo
			servo[goalGripper] = goalGripperRelease;

			//move to goal
			autoDrive(1.15, 0, -25, 10);

			wait1Msec(500);

			grabGoal();

			wait1Msec(500);

			//code to put a ball in
			//the tube will go here

			//move sideways to go beside ramp
			autoDrive(2.5, 50, 0, -20);

			//move to back wall
			autoDrive(4.1, 0, 25, -5);

			//turn so goal is in parking zone
			autoDrive(1.1, 0, 0, 50);

			//back up to make sure goal is in parking zone
			autoDrive(1, 0, -25, 0);

		}
	}

	//if starting from the parking zone
	if(!ramp)
	{
		//if(rollingGoal)
		//{
		//	autoDrive(0.5, -85, 0, 0);
		//	autoDrive(8, 0, -85, 0);
		//	servo[goalGripper] = 15;
		//	autoDrive(8, 0, 85, 0);
		//	autoDrive(1, 0, 0, 85);
		//	autoDrive(0.5, 0, -85, 0);
		//}
		if(kickstand)
		{
			autoDrive(2, 0, -50, 9);
			autoDrive(0.75, 0, -75, -100);
		}
	}

	while (true)
	{}
}
