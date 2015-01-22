#pragma systemFile
#include "JoystickDriver.c"  //Include file to "handle" the Bluetooth messages.

////////////////////////////////////
//
//    Stuffed Griffins Functions
//
// This contains functions created
// by the 8489 Stuffed Griffins in
// the 2014-2015 season.
//
////////////////////////////////////

//These variables store the postitions for the goal gripper servo positions
//Please use these variables in programs use the goal gripper positions, instead of creating new variables
int goalGripperRelease = 125;
int goalGripperGrab = 165;

//these variables are for teleopMecanumDrive
bool driveToggle = false;
bool press = false;

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

//this function only moves backwards and forwards.
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

void teleopMecanumDrive()
{
	//update joystick settings and set joystick variables
	getJoystickSettings(joystick);
	int Y1 = -joystick.joy1_y1;
	int X1 = joystick.joy1_x1;
	int X2 = joystick.joy1_x2;
	int Y2 = -joystick.joy1_y2;

	int x = (X1+X2)/2;
	int y = (Y1+Y2)/2;

	//create toggle for slow drive.  use button 5 to toggle.
	if(joy1Btn(5) == 1 && press)
	{
		driveToggle=!driveToggle;
		press=false;
	}
	else if(joy1Btn(5) != 1)
	{
		press=true;
	}

	if(!driveToggle)
	{
		//normal drive with diagonal zones, first controller joysticks
		if( X1*Y1>=0 && X2*Y1>=0 && X1*Y2>=0 && X2*Y1>=0 && abs(x+y-10)/sqrt(2)-1.02*sqrt((x-10)*(x-10)+(y-10)*(y-10))-3>0 )
		{

			float average = scale((X1+Y1+X2+Y2)/4);
			motor[motor1] = average;
			motor[motor2] = 0;
			motor[motor3] = average;
			motor[motor4] = 0;

		}
		else if( -X1*Y1>=0 && -X2*Y1>=0 && -X1*Y2>=0 && -X2*Y1>=0 && abs(x+y-10)/sqrt(2)-1.02*sqrt((x-10)*(x-10)+(y-10)*(y-10))-3>0 )
		{
			float average = scale((-X1+Y1-X2+Y2)/4);
			motor[motor1] = 0;
			motor[motor2] = average;
			motor[motor3] = 0;
			motor[motor4] = average;
		}
		else
		{
			motor[motor1] = scale(Y2+X2);
			motor[motor4] = scale(Y2-X2);

			motor[motor2] = scale(Y1-X1);
			motor[motor3] = scale(Y1+X1);
		}
	}
	else //slow drive, no diagonal zones, first controller joysticks
	{
		motor[motor1] = scale(Y1+X1, 7, 5, 35);
		motor[motor4] = scale(Y1-X1, 7, 5, 35);

		motor[motor2] = scale(Y2-X2, 7, 5, 35);
		motor[motor3] = scale(Y2+X2, 7, 5, 35);
	}
}

void teleopSimpleRobotFunctions()
{
	getJoystickSettings(joystick);

	//intake control, second controller left y-axis
	motor[intake] = scale(joystick.joy2_y1, 5, 5, 100);

	//goal gripper control, second controller left bumper releases the goal, second controller left trigger engages the goal
	if(joy2Btn(5) == 1)
	{
		servo[goalGripper] = goalGripperRelease;
	}
	if(joy2Btn(7) == 1)
	{
		servo[goalGripper] = goalGripperGrab;
	}

}

//this task is designed for team 8489's arm, it should move it to different positions.
//the positions are defined by encoder distance form position 1.  There are four positions.
//There must be global variables currentPosition and newPosition, which stores the current
//and desired arm positions, respectivly.

//the variables pos1, pos2, pos3, and pos4 are the encoder ticks away from position 1(all the way down),
//to the desired position

int moveArm(int newPosition, int currentPosition)
{
  //the motor positions are encoder ticks from the bottom position
  //the servo positions are the locations of the servo in each different position
  int motorPos0 = 0, motorPos1 = -2000, motorPos2 = -4000;
  int servoPos0 = 5, servoPos1 = 110, servoPos2 = 220;

  //the positions are then put in arrays to make later computation easier
  int motorPositions[3] = {motorPos0, motorPos1, motorPos2};
  int servoPositions[3] = {servoPos0, servoPos1, servoPos2};

  //determine how many encoder ticks the motor needs to move

  int motorMovement = motorPositions[newPosition] - motorPositions[currentPosition];

  //start moving the servo to its position
  servo[armServo1] = servoPositions[newPosition];
  servo[armServo2] = 225-servoPositions[newPosition];

  //reset the encoder
  nMotorEncoder[armMotor1] = 0;
  nMotorEncoder[armMotor2] = 0;

  //determine which way the motor needs to run
  if(motorMovement > 0)
  {
  	nMotorEncoderTarget[armMotor1] = motorMovement;
  	nMotorEncoderTarget[armMotor2] = motorMovement;

    motor[armMotor1] = 15;
    motor[armMotor2] = 15;

    //waiting for the target to be reached
    while(nMotorRunState[armMotor1] != runStateIdle )
    {
      //carryout other commands
      //teleopMecanumDrive();
      //TODO: functions6 that carry out non drive and non arm commands
    }
  }
  else if(motorMovement < 0)
  {
    nMotorEncoderTarget[armMotor1] = motorMovement;
  	nMotorEncoderTarget[armMotor2] = motorMovement;

    motor[armMotor1] = -30;
    motor[armMotor2] = -30;

    //waiting for the target to be reached
    while(nMotorRunState[armMotor1] != runStateIdle)
    {
      //carryout other commands
      //teleopMecanumDrive();
      //teleopSimpleRobotFunctions();
    }
  }

  //stop the motor
  motor[armMotor1] = 0;
  motor[armMotor2] = 0;

  //return the new position for the arm
  return newPosition;
}
