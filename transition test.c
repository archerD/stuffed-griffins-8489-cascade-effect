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

void transition(int initVal, int finalVal, byte changeRate = 10)
{
	if(initVal < finalVal)
	{
		for(int i = initVal; i <= finalVal; i++)
		{
			motor[motor1] = i;
			motor[motor2] = i;
			motor[motor3] = i;
			motor[motor4] = i;
			wait1Msec(changeRate);
		}
	}
	else
	{
		for(int i = initVal; i >= finalVal; i--)
		{
			motor[motor1] = i;
			motor[motor2] = i;
			motor[motor3] = i;
			motor[motor4] = i;
			wait1Msec(changeRate);
		}
	}
}



task main()
{
	transition(10, 85);
	wait(1);

	transition(85, 0);
}
