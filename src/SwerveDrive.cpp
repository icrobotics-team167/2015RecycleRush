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
		talon1 = TalonSRX(talonNumber1);
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
		int angleToBeTurned = (angle + GetWheelAngle()) % 360;
		if ((angleToBeTurned - angle) > 180 || (angleToBeTurned - angle) < -180)
			speed = speed * -1;	//means the wheels don't have to spin over 180 degrees

		int distance = angle * rotateEncoderLines / 360;

		if(rotateEncoder1->GetRaw != distance % rotateEncoderLines)
		{
			rotateVictor1->Set(speed);
			rotateVictor2->Set(speed);
		}	//spins the motors until the wheels point in the right direction
		else
		{
			rotateVictor1->Set(0);
			rotateVictor2->Set(0);
		}	//stops the motors when the wheels are pointing the right way

	}
	int GetWheelAngle()
	{
		float gyroangle = gyro->GetAngle();
		int robotRelativeWheelAngle = rotateEncoder1->GetRaw() * 360 / rotateEncoderLines;
		double fieldRelativeWheelAngle = (gyroangle + robotRelativeWheelAngle) % 360;
		return fieldRelativeWheelAngle;
	}	//finds the angle the wheels are facing relative to the field
};
