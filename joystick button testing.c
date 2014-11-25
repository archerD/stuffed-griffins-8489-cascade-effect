#include "JoystickDriver.c"
task main()
{
	while(true)
	{
		getJoystickSettings(joystick);
		displayCenteredTextLine(3, "button value %d", joystick.joy1_Buttons);
	}
}
