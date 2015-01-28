/*
 * SwerveDrive.h
 *
 *  Created on: Jan 23, 2015
 *      Author: Kazimier
 */

#ifndef SRC_TEAM167LIB_SWERVEDRIVE_H_
#define SRC_TEAM167LIB_SWERVEDRIVE_H_

#include "WPILib.h"

class SwerveDrive
{
private:
	unsigned rotateEncoderLines;
	unsigned driveEncoderLines;
	unsigned feetToEncoderLinesRatio;
	unsigned driveDistance;
	bool finished;
	CANTalon *rotateTalon1;
	CANTalon *rotateTalon2;
	CANTalon *talon1;
	CANTalon *talon2;
	CANTalon *talon3;
	CANTalon *talon4;
	Gyro *gyro;

public:
	SwerveDrive(unsigned rotateEncLines, unsigned driveEncLines,
				unsigned feetToEncLinesR,
				unsigned short rotateTalon1Number,
				unsigned short rotateTalon2Number,
				unsigned short gyroChannel,
				int talon1Number,
				int talon2Number,
				int talon3Number,
				int talon4Number);
	~SwerveDrive();

	void Drive(int angle, double speed);
	void Stop();
	bool TurnRobot(int angle);
	bool DriveACertainDistance(double feet, double speed);
	void RotateRobot(bool clockwise, double speed);
	int GetWheelAngle();
	int GetGyroAngle();
};
#endif /* SRC_TEAM167LIB_SWERVEDRIVE_H_ */
