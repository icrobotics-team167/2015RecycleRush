/*
 * SwerveDrive.cpp
 *
 *  Created on: Jan 8, 2015
 *      Author: Kazimier
 */

#include <iostream>
#include "SwerveDrive.h"

using std::cout;
using std::endl;

SwerveDrive::SwerveDrive(unsigned rotateEncLines, unsigned driveEncLines,
		unsigned feetToEncLinesR, unsigned short rotateTalon1Number,
		unsigned short rotateTalon2Number, unsigned short gyroChannel,
		int talon1Number, int talon2Number, int talon3Number,
		int talon4Number) {
	rotateEncoderLines = rotateEncLines;
	driveEncoderLines = driveEncLines;
	feetToEncoderLinesRatio = feetToEncLinesR;

	rotateTalon1 = new CANTalon(rotateTalon1Number);
	rotateTalon2 = new CANTalon(rotateTalon2Number);

	cout << "rotateTalon1 initial encoder position = "
			<< rotateTalon1->GetEncPosition() << endl;

	talon1 = new CANTalon(talon1Number);
	talon2 = new CANTalon(talon2Number);
	talon3 = new CANTalon(talon3Number);
	talon4 = new CANTalon(talon4Number);

	gyro = new Gyro(gyroChannel);
	gyro->InitGyro();

	driveDistance = 0;
	finished = true;
}

/*
 * talon1--talon3
 * |			|
 * |			|
 * talon2--talon4
 */
SwerveDrive::~SwerveDrive() {
	delete rotateTalon1;
	delete rotateTalon2;
	delete gyro;
	delete talon1;
	delete talon2;
	delete talon3;
	delete talon4;
}

/*
 * angle: the direction relative to the field in which the
 * robot should drive; field forward is 0/360 degrees
 *
 * speed: double ranging from -1.0 to 1.0 which represents the speed at
 * which the wheels should be driven; -1.0 is full reverse, 1.0 is full forward
 */
void SwerveDrive::Drive(int angle, double speed) {
	cout << "rotateTalon1 encoder position = " << rotateTalon1->GetEncPosition()
			<< endl;

	RotateWheelsOnce();
	return;

	if (angle == -1 || speed == 0) {
		talon1->Set(0);
		talon2->Set(0);
		talon3->Set(0);
		talon4->Set(0);
		rotateTalon1->Set(0);
		rotateTalon2->Set(0);
		return;
	} // If they joystick is in neutral position or the speed is zero, do nothing.

	SwerveState swerveState = TurnRobot(angle);
	if (swerveState != DRIVE_NOT) {
		speed *= ((swerveState == DRIVE_FORWARDS) ? 1 : -1);
		rotateTalon1->Set(0);
		rotateTalon2->Set(0);
		talon1->Set(speed);
		talon2->Set(speed);
		talon3->Set(speed);
		talon4->Set(speed);
	}	//stops the motors when the wheels are pointing the right way
		//and tells the drive motors to spin

}

void SwerveDrive::Stop() {
	Drive(-1, 0);
}

SwerveDrive::SwerveState SwerveDrive::TurnRobot(int i) {
	int p = RoundToSix(i);
	if (p == GetWheelAngle()) {							// Angle already correct
		SteerWheels(DRIVE_NOT);
		return DRIVE_FORWARDS;
	} else if (p == GetInvertedAngle(GetWheelAngle())) {// Angle correct backwards
		SteerWheels(DRIVE_NOT);
		return DRIVE_BACKWARDS;
	}

	if (abs(p - GetWheelAngle()) > abs(p - GetInvertedAngle(GetWheelAngle()))) {// Original wheel angle closer
		SteerWheels(
				(p - GetWheelAngle() < 0) ?
						(DRIVE_BACKWARDS) : (DRIVE_FORWARDS));
	} else {									// Inverted wheel angle closer
		SteerWheels(
				(p - GetInvertedAngle(GetWheelAngle()) < 0) ?
						(DRIVE_BACKWARDS) : (DRIVE_FORWARDS));
	}
	return DRIVE_NOT;
}

int SwerveDrive::GetInvertedAngle(int i) {
	return (i + 180) % 360;
}

int SwerveDrive::RoundToSix(int i) {
	int offset = i % 6;
	if (offset >= 3) {
		return i + (6 - offset);
	} else {
		return i - offset;
	}
}

void SwerveDrive::SteerWheels(SwerveState i) {
	int j = 0;
	switch (i) {
	case DRIVE_FORWARDS:
		j = 1;
		break;
	case DRIVE_BACKWARDS:
		j = -1;
		break;
	case DRIVE_NOT:
		rotateTalon1->Set(0);
		rotateTalon2->Set(0);
		return;
	}
	rotateTalon1->Set(j);
	rotateTalon2->Set(j);
	talon1->Set(0);
	talon2->Set(0);
	talon3->Set(0);
	talon4->Set(0);
}

bool SwerveDrive::DriveACertainDistance(double feet, double speed) {
	if (driveDistance == 0 && finished)
		driveDistance = feet / feetToEncoderLinesRatio;

	finished = false;

	int startPosition = talon1->GetEncPosition();

	talon1->Set(speed);
	talon2->Set(speed);
	talon3->Set(speed);
	talon4->Set(speed);

	int endPosition = talon1->GetEncPosition();

	driveDistance = driveDistance - abs(endPosition - startPosition);
	if (driveDistance <= 0) {
		finished = true;
		driveDistance = 0;
	}

	return finished;
}

void SwerveDrive::RotateRobot(bool clockwise, double speed) { // Rotate the robot in a given direction by speed 'speed'
	if (clockwise) {
		talon1->Set(speed);
		talon2->Set(speed);
		talon3->Set(-speed);
		talon4->Set(-speed);
	} else {
		talon1->Set(-speed);
		talon2->Set(-speed);
		talon3->Set(speed);
		talon4->Set(speed);
	}
}

int SwerveDrive::GetWheelAngle() {
	int gyroangle = (int) gyro->GetAngle() % 360;
	int robotRelativeWheelAngle = rotateTalon1->GetEncPosition() * 360
			/ rotateEncoderLines;
	int fieldRelativeWheelAngle = ((int) gyroangle + robotRelativeWheelAngle)
			% 360;
	return fieldRelativeWheelAngle;
}	//finds the angle the wheels are facing relative to the field

int SwerveDrive::GetGyroAngle() {
	return (int) (gyro->GetAngle()) % 360;
}

int SwerveDrive::ConvertEncoderValue() {
	int moddedValue = talon1->GetEncPosition() % rotateEncoderLines;
	if (0 > moddedValue)
		moddedValue = rotateEncoderLines + moddedValue;
	return moddedValue;
}

void SwerveDrive::RotateWheelsOnce() {
	if (ConvertEncoderValue() > (rotateEncoderLines / 2 + ENCODER_ERROR_AMOUNT)
			|| ConvertEncoderValue()
					< (rotateEncoderLines / 2 - ENCODER_ERROR_AMOUNT)) {
		rotateTalon1->Set(1);
		rotateTalon2->Set(1);
	} else {
		rotateTalon1->Set(0);
		rotateTalon2->Set(0);
	}
}
