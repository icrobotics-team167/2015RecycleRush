/*
 * SwerveDrive.cpp
 *
 *  Created on: Jan 8, 2015
 *      Author: Kazimier
 */

#include "WPILib.h"

class SwerveDrive
{
public:
	const int encoderLines = 497;

	SwerveDrive()
	{

	}

	~SwerveDrive()
	{

	}

	/*
	 * angle: the direction relative to the field in which the
	 * robot should drive; field forward is 0/360 degrees
	 *
	 * speed: double ranging from -1.0 to 1.0 which represents the speed at
	 * which the wheels should be driven; -1.0 is full reverse, 1.0 is full forward
	 */
	void Drive(int angle, double speed)
	{

		int c = Encoder->GetRaw();
		int a = (angle + (c * encoderLines / 360)) % 360;
		bool clockwise;
		if (a - angle < 180)
			clockwise = false;
		else
			clockwise = true;
		int d = angle * 497 / 360;

		if (clockwise)
			speed = speed * -1;

		while(Encoder.GetRaw != d % encoderLines)
		{
			Victor1::Set(speed, 0);
			Victor2::Set(speed, 0);
		}

	}
	int GetWheelAngle()
	{
		float gyroangle = gyro->GetAngle();
		int anglewheel = Encoder->GetRaw() * 360 / encoderLines;
		double wheelangle = (gyroangle + anglewheel) % 360;
		return wheelangle;

	}
};
