#pragma systemFile

////////////////////////////////////
//
//    Stuffed Griffins Functions
//
// This contains functions created
// by the 8489 Stuffed Griffins in
// the 2014-2015 season.
//
////////////////////////////////////



//this function is designed to take joystick input, create a deadzone, and scale the input for output to motors.
int scale(int joyValue)
{
	//create deadzone
	if(abs(joyValue) < 10)
	{
		return 0;
	}
	else //scale input value
	{
		long step1prepA = 10 * joyValue;
		long step1prepB = step1prepA / abs(joyValue);
		long step1prepC = joyValue - step1prepB;
		long step1 = step1prepC * step1prepC;
		long step2 = step1 * joyValue;
		long step3 = step2 * (90);
		float step4 = step3 / 13689;
		long step5 = step4 / abs(joyValue);
		int step6 = 10 * joyValue;
		int step7 = step6 / abs(joyValue);
		int final = step5 + step7;
		return final;
	}
}

//this function is an expansion of the above function.  it offers more control over the scaling.
//the parameter are: joyValue, the input to be scaled, minMotorPower, the lowest possible power for the direction,
//threshold, for the size of the deadzone, and maxMotorPower, the maximum power possible for the diriection.
int scale(int joyValue, short minMotorPower, short threshold, short maxMotorPower)
{
	//create deadzone
	if(abs(joyValue) < threshold)
	{
		return 0;
	}
	else //scale input value
	{
		long step1prepA = threshold * joyValue;
		long step1prepB = step1prepA / abs(joyValue);
		long step1prepC = joyValue - step1prepB;
		long step1 = step1prepC * step1prepC;
		long step2 = step1 * joyValue;
		long step3 = step2 * (maxMotorPower-minMotorPower);
		long step4prep = (127-threshold) * (127-threshold);
		float step4 = step3 / step4prep;
		long step5 = step4 / abs(joyValue);
		int step6 = minMotorPower * joyValue;
		int step7 = step6 / abs(joyValue);
		int final = step5 + step7;
		return final;
	}
}

//Drive forward function
//time_seconds = How many seconds you want it to drive
//X = X speed
//Y = Y speed
//R = Rotation speed
void autoDrive (float time_seconds, int X, int Y, int R, tMotor frontLeft = motor1, tMotor frontRight = motor2, tMotor backRight = motor3, tMotor backLeft = motor4)
{
	X = -X;
	//Drive
	motor[frontRight] = -Y + R - X;
	motor[backRight] =  -Y + R + X;
	motor[frontLeft] = -Y - R + X;
	motor[backLeft] =  -Y - R - X;

	//wait for _ seconds
	wait1Msec(1000*time_seconds);

	//Reset motors
	motor[frontLeft] = 0;
	motor[backLeft] = 0;
	motor[frontRight] = 0;
	motor[backRight] = 0;

	return;
}

//this program only moves backwards and forwards.
//it transitions between the two speeds entered.
void transitionYAxis(int initVal, int finalVal, byte changeRate = 10)
{
	initVal = -initVal;
	finalVal = -finalVal;

	//if speeding up while going forwards, or slowing down while in reverse
	if(initVal < finalVal)
	{
		//increment motor speed every changRate milliseconds
		for(int i = initVal; i <= finalVal; i++)
		{
			motor[motor1] = i;
			motor[motor2] = i;
			motor[motor3] = i;
			motor[motor4] = i;
			wait1Msec(changeRate);
		}
	}
	//if slowing down while going forwards, or speeding up while in reverse
	else
	{
		//decrement motor speed every changeRate milliseconds
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
