#pragma config(Hubs,  S1, HTMotor,  HTMotor,  none,     none)
#pragma config(Hubs,  S2, HTServo,  HTMotor,  none,     none)
#pragma config(Sensor, S1,     ,               sensorI2CMuxController)
#pragma config(Sensor, S2,     ,               sensorI2CMuxController)
#pragma config(Motor,  motorA,           ,             tmotorNXT, openLoop)
#pragma config(Motor,  motorB,           ,             tmotorNXT, openLoop)
#pragma config(Motor,  motorC,           ,             tmotorNXT, openLoop)
#pragma config(Motor,  mtr_S1_C1_1,     motor1,        tmotorTetrix, openLoop, reversed)
#pragma config(Motor,  mtr_S1_C1_2,     motor4,        tmotorTetrix, openLoop, reversed)
#pragma config(Motor,  mtr_S1_C2_1,     motor2,        tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C2_2,     motor3,        tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S2_C2_1,     intake,        tmotorTetrix, openLoop, reversed)
#pragma config(Motor,  mtr_S2_C2_2,     arm,           tmotorTetrix, openLoop)
#pragma config(Servo,  srvo_S2_C1_1,    goalGripper,          tServoNone)
#pragma config(Servo,  srvo_S2_C1_2,    servo2,               tServoNone)
#pragma config(Servo,  srvo_S2_C1_3,    servo3,               tServoNone)
#pragma config(Servo,  srvo_S2_C1_4,    servo4,               tServoNone)
#pragma config(Servo,  srvo_S2_C1_5,    servo5,               tServoNone)
#pragma config(Servo,  srvo_S2_C1_6,    servo6,               tServoNone)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//
/////////////////////////////////////////////////////////////////////////////////////////////////////
//
//                           Autonomous Mode Code Template
//
// This file contains a template for simplified creation of an autonomous program for an TETRIX robot
// competition.
//
// You need to customize two functions with code unique to your specific robot.
//
/////////////////////////////////////////////////////////////////////////////////////////////////////

#include "JoystickDriver.c"  //Include file to "handle" the Bluetooth messages.
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

bool ramp;
bool rollingGoal = false;
bool centerGoal = false;
bool kickstand = false;
TFileHandle readFrom;
TFileIOResult result;

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

	byte read = lastRead();
	if(read == 1)
	{
		ramp = true;
	}
	else if(read == 2)
	{
		ramp = false;
	}

	read = lastRead();

	if(read == 1)
	{
		rollingGoal = true;
	}

	read = lastRead();

	if(read == 1)
	{
		centerGoal = true;
	}

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

	waitForStart();

	servo[goalGripper] = 50;

	if(ramp)
	{
		transition(0, -50);
		autoDrive(1.85, 0, -50, 12);
		wait1Msec(500);
		if(rollingGoal)
		{
			servo[goalGripper] = 5;

			autoDrive(1.15, 0, -25, 8);

			wait1Msec(500);

			transition(-25, -12, 30);

			servo[goalGripper] = 100;

			transition(-12, 0, 30);

			wait1Msec(500);

			//code to put a ball in
			//the tube will go here

			autoDrive(2.5, -50, 0, -20);

			autoDrive(4.6, 0, 25, -5);

			//autoDrive(3.75, 0, 50, -9);

			//autoDrive(2, 0, 0, 50);

			//autoDrive(2, 85, 0, 0);

			//autoDrive(7, 0, 85, 0);

			//autoDrive(1, 0, 0, 85);

			//autoDrive(0.5, 0, -85, 0);

		}
	}

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
