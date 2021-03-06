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
#pragma config(Motor,  mtr_S3_C1_1,     conveyor,      tmotorTetrix, openLoop)
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

#include "StuffedGriffinsFunctions.c"


task main()
{
	servo[goalGripper] = goalGripperGrab;

	moveArm(2, 0);
	wait10Msec(100);
	motor[conveyor] = 10;
	wait1Msec(2250);
	moveArm(0, 2);
	motor[conveyor] = -20;
	wait(1);
	motor[conveyor] = 0;
}
