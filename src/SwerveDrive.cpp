/*
 * SwerveDrive.cpp
 *
 *  Created on: Jan 8, 2015
 *      Author: Kazimier
 */

#include "WPILib.h"

class SwerveDrive
{
private:
	unsigned rotateEncoderLines;
	unsigned driveEncoderLines;
	Victor *rotateVictor1;
	Victor *rotateVictor2;
	Encoder *rotateEncoder1;
	Encoder *rotateEncoder2;
	Gyro *gyro;

public:
	SwerveDrive(unsigned rotateEncLines, unsigned driveEncLines,
				unsigned short rotateVictor1Channel,
				unsigned short rotateVictor2Channel,
				unsigned short rotateEnc1ChannelA, unsigned short rotateEnc1ChannelB,
				unsigned short rotateEnc2ChannelA, unsigned short rotateEnc2ChannelB,
				unsigned short gyroChannel)
	{
		rotateEncoderLines = rotateEncLines;
		driveEncoderLines = driveEncLines;
		rotateVictor1 = new Victor(rotateVictor1Channel);
		rotateVictor2 = new Victor(rotateVictor2Channel);
		rotateEncoder1 = new Encoder(rotateEnc1ChannelA, rotateEnc1ChannelB);
		rotateEncoder2 = new Encoder(rotateEnc2ChannelA, rotateEnc2ChannelB);
		gyro = new Gyro(gyroChannel);
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
