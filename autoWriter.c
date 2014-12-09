//////////////////////////////////////////////////////////////////////////////////////////
//            Writes a file containing the directions for auto period
//
// first byte is for whether the robot will start from the ramp, 1 for yes and 2 for no
// second byte is for whether the robot should collect ball tube, 1 for yes and 2 for no
// third byte is for whether the robot should score in the center goal, 1 for for yes and 2 for no
// fourth byte is for whether the robot should knock down the kickstane, 1 for yes and 2 for no
//
//////////////////////////////////////////////////////////////////////////////////////////

void errorCheck(TFileIOResult check)
{
	if(check != 0)
	{
		nxtDisplayCenteredTextLine(4, "error");
		wait(2);
	}
}

TFileHandle writeTo;

void write(byte N)
{
	TFileIOResult result;
	WriteByte(writeTo, result, N);
	errorCheck(result);
}

task main()
{
	nNxtExitClicks = 2;

	TFileIOResult result;
	short currentSize = 4;
	bool ramp;

	Delete("auto.txt", result);
	OpenWrite(writeTo, result, "auto.txt", currentSize);
	errorCheck(result);

	while(true)
	{
		eraseDisplay();

		nxtDisplayCenteredTextLine(1, "Starting from");
		nxtDisplayCenteredTextLine(3, "ramp left button");
		nxtDisplayCenteredTextLine(4, "or parking zone");
		nxtDisplayCenteredTextLine(5, "right button");

		while(nNxtButtonPressed == -1)
		{
		}
		if(nNxtButtonPressed == 2)
		{
			eraseDisplay();
			write(1);
			ramp = true;
			nxtDisplayCenteredTextLine(4, "ramp selected");
			wait1Msec(2000);
			break;
		}
		else if(nNxtButtonPressed == 1)
		{
			eraseDisplay();
			write(2);
			ramp = false;
			nxtDisplayCenteredTextLine(4, "parking zone");
			nxtDisplayCenteredTextLine(5, "selected");
			wait1Msec(2000);
			break;
		}
	}

	eraseDisplay();


	while(true)
	{
		eraseDisplay();
		nxtDisplayCenteredTextLine(1, "Should the robot");
		nxtDisplayCenteredTextLine(2, "get the ball tube");
		nxtDisplayCenteredTextLine(3, "right for yes");
		nxtDisplayCenteredTextLine(4, "left for no");

		while(nNxtButtonPressed == -1)
		{
		}
		if(nNxtButtonPressed == 1)
		{
			eraseDisplay();
			write(1);
			nxtDisplayCenteredTextLine(4, "robot will get");
			nxtDisplayCenteredTextLine(5, "ball tube");
			wait1Msec(2000);
			break;
		}
		else if(nNxtButtonPressed == 2)
		{
			eraseDisplay();
			write(2);
			nxtDisplayCenteredTextLine(4, "robot will not");
			nxtDisplayCenteredTextLine(5, "get ball tube");
			wait1Msec(2000);
			break;
		}
	}

	eraseDisplay();

	while(true)
	{
		eraseDisplay();
		nxtDisplayCenteredTextLine(1, "Should the robot");
		nxtDisplayCenteredTextLine(2, "score in the");
		nxtDisplayCenteredTextLine(3, "center goal");
		nxtDisplayCenteredTextLine(4, "right for yes");
		nxtDisplayCenteredTextLine(5, "left for no");

		while(nNxtButtonPressed == -1)
		{
		}
		if(nNxtButtonPressed == 1)
		{
			eraseDisplay();
			write(1);
			nxtDisplayCenteredTextLine(4, "robot will score");
			nxtDisplayCenteredTextLine(5, "in center goal");
			wait1Msec(2000);
			break;
		}
		else if(nNxtButtonPressed == 2)
		{
			eraseDisplay();
			write(2);
			nxtDisplayCenteredTextLine(3, "robot will not");
			nxtDisplayCenteredTextLine(4, "score in");
			nxtDisplayCenteredTextLine(5, "center goal");

			wait1Msec(2000);
			break;
		}
	}

	eraseDisplay();

	while(true)
	{
		eraseDisplay();
		nxtDisplayCenteredTextLine(1, "Should the robot");
		nxtDisplayCenteredTextLine(2, "knock down the");
		nxtDisplayCenteredTextLine(3, "kickstand");
		nxtDisplayCenteredTextLine(4, "right for yes");
		nxtDisplayCenteredTextLine(5, "left for no");

		while(nNxtButtonPressed == -1)
		{
		}
		if(nNxtButtonPressed == 1)
		{
			eraseDisplay();
			write(1);
			nxtDisplayCenteredTextLine(3, "robot will knock");
			nxtDisplayCenteredTextLine(4, "down the");
			nxtDisplayCenteredTextLine(5, "kickstand");
			wait1Msec(2000);
			break;
		}
		else if(nNxtButtonPressed == 2)
		{
			eraseDisplay();
			write(2);
			nxtDisplayCenteredTextLine(3, "robot will not");
			nxtDisplayCenteredTextLine(4, "knock down the");
			nxtDisplayCenteredTextLine(5, "kickstand");
			wait1Msec(2000);
			break;
		}
	}

	Close(writeTo, result);
	errorCheck(result);
}
