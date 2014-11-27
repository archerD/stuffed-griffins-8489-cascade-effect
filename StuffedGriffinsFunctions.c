//////////////////////////////////
//
//



//this function is designed to take joystick input, create a deadzone, and scale the input for output to motors.
int scale(int joyValue)
{
	//create deadzone
	if(joyValue < 5)
	{
		return 0;
	}
	else //scale input value
	{
		long step1 = joyValue * joyValue;
		long step2 = step1 * joyValue;
		long step3 = step2 * (85);
		float step4 = step3 / 14884;
		long step5 = step4 / abs(joyValue);
		int step6 = 10 * joyValue;
		int step7 = step6 / abs(joyValue);
		int final = step5 + step7;
		return final;
	}
}

//this function is an expansion of the above function.  it offers more control over the scaling.
//the parameter are: joyValue, the input from the joystick, minMotorPower, the lowest possible power for the direction,
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
