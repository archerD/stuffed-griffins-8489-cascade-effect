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
#pragma config(Servo,  srvo_S2_C1_1,    goalGripper,          tServoStandard)
#pragma config(Servo,  srvo_S2_C1_2,    servo2,               tServoNone)
#pragma config(Servo,  srvo_S2_C1_3,    servo3,               tServoNone)
#pragma config(Servo,  srvo_S2_C1_4,    servo4,               tServoNone)
#pragma config(Servo,  srvo_S2_C1_5,    servo5,               tServoNone)
#pragma config(Servo,  srvo_S2_C1_6,    servo6,               tServoNone)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//


/////////////////////////////////////////////////////////////////////////////////////////////////////
//
//                           Tele-Operation Mode Code Template
//
// This file contains a template for simplified creation of an tele-op program for an FTC
// competition.
//
// You need to customize two functions with code unique to your specific robot.
//
/////////////////////////////////////////////////////////////////////////////////////////////////////

#include "JoystickDriver.c"  //Include file to "handle" the Bluetooth messages.
#include "StuffedGriffinsFunctions.c"

/////////////////////////////////////////////////////////////////////////////////////////////////////
//
//                                    initializeRobot
//
// Prior to the start of tele-op mode, you may want to perform some initialization on your robot
// and the variables within your program.
//
// In most cases, you may not have to add any code to this function and it will remain "empty".
//
/////////////////////////////////////////////////////////////////////////////////////////////////////

void initializeRobot()
{
	// Place code here to sinitialize servos to starting positions.
	// Sensors are automatically configured and setup by ROBOTC. They may need a brief time to stabilize.

	return;
}

//this task is designed for team 8489's arm, it should move it to different positions.
//the positions are defined by encoder distance form position 1.  There are four positions.
//as input it needs the position wanted to be reached, and it needs access to variable currentPosition,
//which must have the number of the current position.

int currentPosition = 1; //arm position
int newPosition;
TSemaphore armLock;
task moveTo()
{
	//declare variables
	long distance;
	long target;
	long position;
	long pos1 = 0;
	long pos2 = 50;
	long pos3 = 100;
	long pos4 = 150;
	long encoderValues[4] = {pos1, pos2, pos3, pos4};
	nMotorEncoder[arm] = 0;

	//define undefined variables
	target = encoderValues[newPosition-1];
	position = encoderValues[currentPosition-1];
	distance = target - position;

	//start moving arm
	motor[arm] = 50*distance/abs(distance);
	//wait to reach target position
	while(nMotorEncoder[arm] < abs(distance))
	{
		EndTimeSlice();
	}
	//stop motor and update current position
	motor[arm] = 0;
	currentPosition = newPosition;
	return;
}



/////////////////////////////////////////////////////////////////////////////////////////////////////
//
//                                         Main Task
//
// The following is the main code for the tele-op robot operation. Customize as appropriate for
// your specific robot.
//
// Game controller / joystick information is sent periodically (about every 50 milliseconds) from
// the FMS (Field Management System) to the robot. Most tele-op programs will follow the following
// logic:
//   1. Loop forever repeating the following actions:
//   2. Get the latest game controller / joystick settings that have been received from the PC.
//   3. Perform appropriate actions based on the joystick + buttons settings. This is usually a
//      simple action:
//      *  Joystick values are usually directly translated into power levels for a motor or
//         position of a servo.
//      *  Buttons are usually used to start/stop a motor or cause a servo to move to a specific
//         position.
//   4. Repeat the loop.
//
// Your program needs to continuously loop because you need to continuously respond to changes in
// the game controller settings.
//
// At the end of the tele-op period, the FMS will autonmatically abort (stop) execution of the program.
//
/////////////////////////////////////////////////////////////////////////////////////////////////////


task main()
{
	initializeRobot();

	waitForStart();   // wait for start of tele-op phase
	int down = 100;
	int up = 5;
	bool servoToggle = false;
	bool press = false;
	semaphoreInitialize(armLock);

	while (true)
	{
		getJoystickSettings(joystick);

		//drive intake
		motor[intake] = scale(joystick.joy1_y1);

		//goal gripper
		if(joystick.joy1_TopHat == 0)
		{
			servoTarget[goalGripper] = up;
		}
		if(joystick.joy1_TopHat == 4)
		{
			servoTarget[goalGripper] = down;
		}

		//thomas' goal gripper one button toggle
		if(joy1Btn(2) == 1 && press)
		{
			servoToggle=!servoToggle;
			press=false;
		}
		else if(joy1Btn(2) != 1)
		{
			press=true;
		}

		if(servoToggle == false)
		{
			servo[goalGripper] = down;
		}
		else if(servoToggle == true)
		{
			servo[goalGripper] = up;
		}

		//need to test.
		//arm motor
		if(joy1Btn(1) == 1)
		{
			semaphoreLock(armLock);
			if(bDoesTaskOwnSemaphore(armLock))
			{
				newPosition = 1;
				startTask(moveTo);
			}
			if(bDoesTaskOwnSemaphore(armLock))
				semaphoreUnlock(armLock);
		}
		else if(joy1Btn(2) == 1)
		{
			if(bDoesTaskOwnSemaphore(armLock))
			{
				semaphoreLock(armLock);
				newPosition = 2;
				startTask(moveTo);
			}
			if(bDoesTaskOwnSemaphore(armLock))
				semaphoreUnlock(armLock);
		}
		else if(joy1Btn(3) == 1)
		{
			if(bDoesTaskOwnSemaphore(armLock))
			{
				semaphoreLock(armLock);
				newPosition = 3;
				startTask(moveTo);
			}
			if(bDoesTaskOwnSemaphore(armLock))
				semaphoreUnlock(armLock);
		}
		else if(joy1Btn(4) == 1)
		{
			if(bDoesTaskOwnSemaphore(armLock))
			{
				semaphoreLock(armLock);
				newPosition = 4;
				startTask(moveTo);
			}
			if(bDoesTaskOwnSemaphore(armLock))
				semaphoreUnlock(armLock);
		}

	}

}
