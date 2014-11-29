TFileHandle readFrom;
TFileIOResult result;
byte lastRead()
{
	byte N;
	TFileIOResult result;
	ReadByte(readFrom, result, N);
	return N;
}

task main()
{
	word currentSize;
	OpenRead(readFrom, result, "auto.txt", currentSize);

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
}
