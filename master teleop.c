#pragma config(Hubs,  S1, HTMotor,  none,     none,     none)
#pragma config(Hubs,  S2, HTMotor,  none,     none,     none)
#pragma config(Hubs,  S3, HTMotor,  none,     none,     none)
#pragma config(Hubs,  S4, HTServo,  none,     none,     none)
#pragma config(Sensor, S1,     ,               sensorI2CMuxController)
#pragma config(Sensor, S2,     ,               sensorI2CMuxController)
#pragma config(Sensor, S3,     ,               sensorI2CMuxController)
#pragma config(Sensor, S4,     ,               sensorI2CMuxController)
#pragma config(Motor,  motorA,           ,             tmotorNXT, openLoop)
#pragma config(Motor,  motorB,           ,             tmotorNXT, openLoop)
#pragma config(Motor,  motorC,           ,             tmotorNXT, openLoop)
#pragma config(Motor,  mtr_S1_C1_1,     motor2,        tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C1_2,     motor3,        tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S2_C1_1,     motor1,        tmotorTetrix, openLoop, reversed)
#pragma config(Motor,  mtr_S2_C1_2,     motor4,        tmotorTetrix, openLoop, reversed)
#pragma config(Motor,  mtr_S3_C1_1,     intake,        tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S3_C1_2,     motorI,        tmotorTetrix, openLoop)
#pragma config(Servo,  srvo_S4_C1_1,    goalGripper,          tServoStandard)
#pragma config(Servo,  srvo_S4_C1_2,    servo2,               tServoNone)
#pragma config(Servo,  srvo_S4_C1_3,    servo3,               tServoNone)
#pragma config(Servo,  srvo_S4_C1_4,    servo4,               tServoNone)
#pragma config(Servo,  srvo_S4_C1_5,    servo5,               tServoNone)
#pragma config(Servo,  srvo_S4_C1_6,    servo6,               tServoNone)
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
	servo[goalGripper] = 50;
	wait1Msec(1000);

	return;
}

int scale(int joyValue, int threshold, int minMotorPower)
{
	if(abs(joyValue) <= threshold)
	{
		return 0;
	}
	else
	{
		long step1 = joyValue * joyValue;
		long step2 = step1 * joyValue;
		long step3 = step2 * (100-minMotorPower);
		float step4 = step3 / 16129;
		long step5 = step4 / abs(joyValue);
		int step6 = minMotorPower * joyValue;
		int step7 = step6 / abs(joyValue);
		int final = step5 + step7;
		return final;
	}
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

	int X2 = 0, Y1 = 0, X1 = 0, Y2 = 0, threshold = 10;
	int var = 30;

	int down = 15;
	int up = 50;

	while (true)
	{
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
		//Create "deadzone" for Y1/Ch3
		if(abs(joystick.joy1_y2) > threshold)
			Y2 = joystick.joy1_y2;
		else
			Y2 = 0;

		if( abs(Y1+Y2+X1+X2)>=10  && X1*Y1>=0 && X2*Y1>=0 && X1*Y2>=0 && X2*Y1>=0 && abs(X1-Y1)<var && abs(X2-Y2)<var )
		{

			float average = scale((X1+Y1+X2+Y2)/4, 10, 15);
			motor[motor1] = average;
			motor[motor2] = 0;
			motor[motor3] = average;
			motor[motor4] = 0;

		}
		else if( abs(Y1+Y2-X1-X2)>=10 && -X1*Y1>=0 && -X2*Y1>=0 && -X1*Y2>=0 && -X2*Y1>=0 && abs(X1+Y1)< var && abs(X2+Y2)< var )
		{
			float average = scale((-X1+Y1-X2+Y2)/4, 10, 15);
			motor[motor1] = 0;
			motor[motor2] = average;
			motor[motor3] = 0;
			motor[motor4] = average;
		}
		else
		{
			motor[motor1] = scale(Y1+X1, 10, 15);
			motor[motor4] = scale(Y1-X1, 10, 15);

			motor[motor2] = scale(Y2-X2, 10, 15);
			motor[motor3] = scale(Y2+X2, 10, 15);
		}

		if(abs(joystick.joy2_y1)>10){
			motor[intake] = -scale(joystick.joy2_y1, 5, 5);
		}
		else
		{
			motor[intake] = 0;
		}


		if(joy1Btn(5) == 1)
		{
			servoTarget[goalGripper] = up;
		}
		if(joy1Btn(7) == 1)
		{
			servoTarget[goalGripper] = down;
		}

	}
}
