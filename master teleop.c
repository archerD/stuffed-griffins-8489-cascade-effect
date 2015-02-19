#pragma config(Hubs,  S1, HTMotor,  HTMotor,  none,     none)
#pragma config(Hubs,  S2, HTServo,  none,     none,     none)
#pragma config(Hubs,  S3, HTMotor,  HTMotor,  none,     none)
#pragma config(Sensor, S1,     ,               sensorI2CMuxController)
#pragma config(Sensor, S2,     ,               sensorI2CMuxController)
#pragma config(Sensor, S3,     ,               sensorI2CMuxController)
#pragma config(Motor,  motorA,           ,             tmotorNXT, openLoop)
#pragma config(Motor,  motorB,           ,             tmotorNXT, openLoop)
#pragma config(Motor,  motorC,           ,             tmotorNXT, openLoop)
#pragma config(Motor,  mtr_S1_C1_1,     motor2,        tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C1_2,     motor1,        tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C2_1,     motor4,        tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C2_2,     motor3,        tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S3_C1_1,     conveyor,      tmotorTetrix, openLoop, reversed)
#pragma config(Motor,  mtr_S3_C1_2,     intake,        tmotorTetrix, openLoop, reversed)
#pragma config(Motor,  mtr_S3_C2_1,     armMotor1,     tmotorTetrix, PIDControl, reversed, encoder)
#pragma config(Motor,  mtr_S3_C2_2,     armMotor2,     tmotorTetrix, PIDControl, encoder)
#pragma config(Servo,  srvo_S2_C1_1,    goalGripper,          tServoStandard)
#pragma config(Servo,  srvo_S2_C1_2,    ballGuard,            tServoStandard)
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

#include "StuffedGriffinsFunctions.c" //include file with the Stuffed Griffins' functions

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
	servo[ballGuard] = ballGuardOFF;
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
	int armPosition = 0;
	initializeRobot();

	waitForStart();   // wait for start of tele-op phase

	while (true)
	{
		//update joystick settings
		getJoystickSettings(joystick);

		teleopMecanumDrive();

		teleopSimpleRobotFunctions();

		//check if button has been pressed
		if(joy2Btn(2) == 1)
		{
			armPosition = moveArm(0, armPosition);
		}
		else if(joy2Btn(3) == 1)
		{
			armPosition = moveArm(1, armPosition);
		}
		else if(joy2Btn(4) == 1)
		{
			armPosition = moveArm(2, armPosition);
		}

		if(joy2Btn(6) == 1)
		{
			motor[armMotor1] = 15;
			motor[armMotor2] = 15;
		}
		else if(joy2Btn(8) == 1)
		{
			motor[armMotor1] = -15;
			motor[armMotor2] = -15;
		}
		else
		{
			motor[armMotor1] = 0;
			motor[armMotor2] = 0;
		}

	}
}
