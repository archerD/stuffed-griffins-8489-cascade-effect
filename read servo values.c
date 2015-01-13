#pragma config(Hubs,  S2, HTServo,  none,     none,     none)
#pragma config(Sensor, S2,     ,               sensorI2CMuxController)
#pragma config(Servo,  srvo_S2_C1_1,    goalGripper,          tServoStandard)
#pragma config(Servo,  srvo_S2_C1_2,    armServo,             tServoStandard)
#pragma config(Servo,  srvo_S2_C1_3,    armServo2,            tServoStandard)
#pragma config(Servo,  srvo_S2_C1_4,    servo4,               tServoNone)
#pragma config(Servo,  srvo_S2_C1_5,    servo5,               tServoNone)
#pragma config(Servo,  srvo_S2_C1_6,    servo6,               tServoNone)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

task main()
{
	int a = servo[goalGripper];
	servo[armServo] = a;
	while(true)
	{
		getJoystickSettings(joystick);
		if (joystick.joy1_TopHat == 0)
		{
			a += 5;
			servo[armServo] = a;
		}
		else if(joystick.joy1_TopHat == 4)
		{
			a -= 5;
			servo[armServo] = a;
		}
		eraseDisplay();
		nxtDisplayCenteredTextLine(3, "servo position:");
		nxtDisplayCenteredTextLine(4, "%d", ServoValue[armServo]);
		wait1Msec(100);
	}
}
