TFileHandle readFrom;
TFileIOResult result;

void errorCheck(TFileIOResult check)
{
	if(check != 0)
	{
		nxtDisplayCenteredTextLine(4, "error");
		wait(2);
	}
}

byte lastRead()
{
	byte N;
	TFileIOResult result;
	ReadByte(readFrom, result, N);
	errorCheck(result);
	return N;
}

task main()
{
	word currentSize;
	OpenRead(readFrom, result, "auto.txt", currentSize);
	errorCheck(result);

	byte read = lastRead();
	if(read == 1)
	{
		nxtDisplayCenteredTextLine(3, "ramp");
		wait(2);
		eraseDisplay();
	}
	else if(read == 2)
	{
		nxtDisplayCenteredTextLine(3, "parking zone");
		wait(2);
		eraseDisplay();
	}

	read = lastRead();

	if(read == 1)
	{
		nxtDisplayCenteredTextLine(3, "ball tube");
		wait(2);
		eraseDisplay();
	}

	read = lastRead();

	if(read == 1)
	{
		nxtDisplayCenteredTextLine(3, "center goal");
		wait(2);
		eraseDisplay();
	}

	read = lastRead();

	if(read == 1)
	{
		nxtDisplayCenteredTextLine(3, "kickstand");
		wait(2);
		eraseDisplay();
	}

	Close(readFrom, result);
	errorCheck(result);
}
