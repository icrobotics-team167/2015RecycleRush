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
	CANTalon *rotateTalon1;
	CANTalon *rotateTalon2;
	Encoder *rotateEncoder1;
	Encoder *rotateEncoder2;
	Gyro *gyro;
	CANTalon *talon1;
	CANTalon *talon2;
	CANTalon *talon3;
	CANTalon *talon4;

public:
	SwerveDrive(unsigned rotateEncLines, unsigned driveEncLines,
				unsigned short rotateTalon1Channel,
				unsigned short rotateTalon2Channel,
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
		rotateTalon1 = new CANTalon(rotateTalon1Channel);
		rotateTalon2 = new CANTalon(rotateTalon2Channel);
		rotateEncoder1 = new Encoder(rotateEnc1ChannelA, rotateEnc1ChannelB);
		rotateEncoder2 = new Encoder(rotateEnc2ChannelA, rotateEnc2ChannelB);
		gyro = new Gyro(gyroChannel);
		talon1 = new CANTalon(talonNumber1);
		talon2 = new CANTalon(talonNumber2);
		talon3 = new CANTalon(talonNumber3);
		talon4 = new CANTalon(talonNumber4);
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
		// always rotate the wheels at maximum speed
		double rotateWheelSpeed = 1.0;

		int angleToBeTurned = (angle + GetWheelAngle()) % 360;

		if (abs(angleToBeTurned - angle) > 180)
			speed = speed * -1;	//means the wheels don't have to spin over 180 degrees

		int distance = angle * rotateEncoderLines / 360;

		if (rotateEncoder1->GetRaw() != distance % rotateEncoderLines)
		{
			rotateTalon1->Set(rotateWheelSpeed);
			rotateTalon2->Set(rotateWheelSpeed);
			talon1->Set(0);
			talon2->Set(0);
			talon3->Set(0);
			talon4->Set(0);
		}	//spins the motors until the wheels point in the right direction and stops drive motors
		else
		{
			rotateTalon1->Set(0);
			rotateTalon2->Set(0);
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
