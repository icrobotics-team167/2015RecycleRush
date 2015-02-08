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
	static const int ENCODER_ERROR_AMOUNT = 100;
	enum SwerveState { DRIVE_NOT, DRIVE_FORWARDS, DRIVE_BACKWARDS };
	int rotateEncoderLines;
	int driveEncoderLines;
	int feetToEncoderLinesRatio;
	int driveDistance;
	bool finished;
	CANTalon *rotateTalon1;
	CANTalon *rotateTalon2;
	CANTalon *talon1;
	CANTalon *talon2;
	CANTalon *talon3;
	CANTalon *talon4;
	Gyro *gyro;

public:
	SwerveDrive(int rotateEncLines, int driveEncLines,
				int feetToEncLinesR,
				short rotateTalon1Number,
				short rotateTalon2Number,
				short gyroChannel,
				int talon1Number,
				int talon2Number,
				int talon3Number,
				int talon4Number);
	~SwerveDrive();

	void Drive(int angle, double speed);
	void Stop();
	void RotateRobotFront(int angle);
	void RotateRobotBack(int angle);
	bool DriveACertainDistance(double feet, double speed);
	void RotateRobot(bool clockwise, double speed);
	int GetFrontWheelAngleRobotRelative();
	int GetBackWheelAngleRobotRelative();
	int GetFrontWheelAngleFieldRelative();
	int GetBackWheelAngleFieldRelative();
	int GetGyroAngle();
	int ConvertFrontEncoderValue();
	int ConvertBackEncoderValue();
	void ZeroRotateEncoders();
	void ZeroDriveEncoders();
	void ResetGyro();
};
#endif /* SRC_TEAM167LIB_SWERVEDRIVE_H_ */
