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
	TalonSRX *talon1;
	TalonSRX *talon2;
	TalonSRX *talon3;
	TalonSRX *talon4;

public:
	SwerveDrive(unsigned rotateEncLines, unsigned driveEncLines,
				unsigned short rotateVictor1Channel,
				unsigned short rotateVictor2Channel,
				unsigned short rotateEnc1ChannelA, unsigned short rotateEnc1ChannelB,
				unsigned short rotateEnc2ChannelA, unsigned short rotateEnc2ChannelB,
				unsigned short gyroChannel,
				int talonNumber1,
				int talonNumber2,
				int talonNumber3,
				int talonNumber4)
	{
		rotateEncoderLines = rotateEncLines;
		driveEncoderLines = driveEncLines;
		rotateVictor1 = new Victor(rotateVictor1Channel);
		rotateVictor2 = new Victor(rotateVictor2Channel);
		rotateEncoder1 = new Encoder(rotateEnc1ChannelA, rotateEnc1ChannelB);
		rotateEncoder2 = new Encoder(rotateEnc2ChannelA, rotateEnc2ChannelB);
		gyro = new Gyro(gyroChannel);
		talon1 = TalonSRX(talonNumber1);
		talon2 = TalonSRX(talonNumber2);
		talon3 = TalonSRX(talonNumber3);
		talon4 = TalonSRX(talonNumber4);
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
			talon1->Set(0);
			talon2->Set(0);
			talon3->Set(0);
			talon4->Set(0);
		}	//spins the motors until the wheels point in the right direction
		else
		{
			rotateVictor1->Set(0);
			rotateVictor2->Set(0);
			talon1->Set(speed);
			talon2->Set(speed);
			talon3->Set(speed);
			talon4->Set(speed);

		}	//stops the motors when the wheels are pointing the right way
			//and tells the drive motors to spin


	}
	int GetWheelAngle()
	{
		float gyroangle = gyro->GetAngle();
		int robotRelativeWheelAngle = rotateEncoder1->GetRaw() * 360 / rotateEncoderLines;
		double fieldRelativeWheelAngle = (gyroangle + robotRelativeWheelAngle) % 360;
		return fieldRelativeWheelAngle;
	}	//finds the angle the wheels are facing relative to the field
};
