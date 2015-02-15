/*
 * SwerveDrive.cpp
 *
 *  Created on: Jan 8, 2015
 *      Author: Kazimier
 */

#include "SwerveDrive.h"
#include <iostream>

using std::cout;
using std::endl;

SwerveDrive::SwerveDrive(int rotateEncLines, int driveEncLines,
                        int feetToEncLinesR,
                        short rotateTalon1Number,
                        short rotateTalon2Number,
                        short gyroChannel,
                        int talon1Number,
                        int talon2Number,
                        int talon3Number,
                        int talon4Number)
{
        rotateEncoderLines = rotateEncLines;
        driveEncoderLines = driveEncLines;
        feetToEncoderLinesRatio = feetToEncLinesR;

        rotateTalon1 = new CANTalon(rotateTalon1Number);
        rotateTalon2 = new CANTalon(rotateTalon2Number);

        rotateTalon1->SetControlMode(CANSpeedController::kPosition);
        rotateTalon2->SetControlMode(CANSpeedController::kPosition);
        rotateTalon1->SetFeedbackDevice(CANTalon::QuadEncoder);
        rotateTalon2->SetFeedbackDevice(CANTalon::QuadEncoder);
        //rotateTalon1->SetPID(1.0, 0.001, 0.1);
        //rotateTalon2->SetPID(1.0, 0.001, 0.1);
        rotateTalon1->SetPID(0.6, 2.97, 0.96);
        rotateTalon2->SetPID(0.6, 2.97, 0.96);
        rotateTalon1->EnableControl();
        rotateTalon2->EnableControl();
        rotateTalon1->SetSensorDirection(true);
        rotateTalon2->SetSensorDirection(true);


        talon1 = new CANTalon(talon1Number);
        talon2 = new CANTalon(talon2Number);
        talon3 = new CANTalon(talon3Number);
        talon4 = new CANTalon(talon4Number);

        gyro = new Gyro(gyroChannel);
        ResetGyro();

        driveDistance = 0;

        finished = true;
}

/*
 * talon1--talon3
 * |			|
 * |			|
 * talon2--talon4
 */
SwerveDrive::~SwerveDrive()
{
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
void SwerveDrive::Drive(int angle, double speed)
{
        if (angle == -1 || speed == 0) {
                talon1->Set(0);
                talon2->Set(0);
                talon3->Set(0);
                talon4->Set(0);
                rotateTalon1->StopMotor();
                rotateTalon2->StopMotor();
                return;
        } // If they joystick is in neutral position or the speed is zero, do nothing.

        EnableTurnMotors();

        RotateRobotFront(angle);
        RotateRobotBack(angle);
        talon1->Set(speed);
        talon2->Set(speed);
        talon3->Set(speed);
        talon4->Set(speed);
}

void SwerveDrive::Stop()
{
        Drive(-1, 0);
}

void SwerveDrive::RotateRobotFront(int angle)
{
        int desiredAngleRobotRelative = 0;
        if (angle > GetGyroAngle())
                desiredAngleRobotRelative = angle - GetGyroAngle();
        else
                desiredAngleRobotRelative = 360 - abs(angle - GetGyroAngle());

        int desiredPosition = (int) ((double) desiredAngleRobotRelative * rotateEncoderLines / 360.0);

        int rotations = rotateTalon1->GetEncPosition() / rotateEncoderLines;
        desiredPosition += (rotations * rotateEncoderLines);

        rotateTalon1->Set(-desiredPosition);

        cout << "ROTATETALON1 SPEED: " << rotateTalon1->GetSpeed() << endl;
        SmartDashboard::PutNumber("RotateTalon1 Speed", rotateTalon1->GetSpeed());
        SmartDashboard::PutNumber("RotateTalon1 Enc", rotateTalon1->GetEncPosition());
        SmartDashboard::PutNumber("target1", rotateTalon1->GetSetpoint());



}

void SwerveDrive::RotateRobotBack(int angle)
{
        int desiredAngleRobotRelative = 0;
        if (angle > GetGyroAngle())
        	desiredAngleRobotRelative = angle - GetGyroAngle();
        else
        	desiredAngleRobotRelative = 360 - abs(angle - GetGyroAngle());

        int desiredPosition = (int) ((double) desiredAngleRobotRelative * rotateEncoderLines / 360.0);

        int rotations = rotateTalon1->GetEncPosition() / rotateEncoderLines;
        desiredPosition += (rotations * rotateEncoderLines);

        rotateTalon2->Set(-desiredPosition);

        cout << "ROTATETALON2 SPEED: " << rotateTalon2->GetSpeed() << endl;
        SmartDashboard::PutNumber("RotateTalon2 Speed", rotateTalon2->GetSpeed());
        SmartDashboard::PutNumber("RotateTalon2 Enc", rotateTalon2->GetEncPosition());
        SmartDashboard::PutNumber("target2", rotateTalon2->GetSetpoint());
        SmartDashboard::PutNumber("desired", desiredPosition);


}

bool SwerveDrive::DriveACertainDistance(double feet, double speed)
{
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
        if (driveDistance <= 0)
        {
                finished = true;
                driveDistance = 0;
        }

        return finished;
}

void SwerveDrive::RotateRobot(bool clockwise, double speed)
{ // Rotate the robot in a given direction by speed 'speed'
        if (clockwise) {
                talon1->Set(speed);
                talon2->Set(speed);
                talon3->Set(-speed);
                talon4->Set(-speed);
        }
        else {
                talon1->Set(-speed);
                talon2->Set(-speed);
                talon3->Set(speed);
                talon4->Set(speed);
        }
}

int SwerveDrive::GetFrontWheelAngleRobotRelative()
{
	return ConvertFrontEncoderValue() / (double) rotateEncoderLines * 360;
}

int SwerveDrive::GetBackWheelAngleRobotRelative()
{
	return ConvertBackEncoderValue() / (double) rotateEncoderLines * 360;
}

int SwerveDrive::GetFrontWheelAngleFieldRelative()
{
	float gyroangle = GetGyroAngle();
	int robotRelativeWheelAngle = GetFrontWheelAngleRobotRelative();
	int fieldRelativeWheelAngle = ((int)gyroangle + robotRelativeWheelAngle) % 360;
	return fieldRelativeWheelAngle;
}	//finds the angle the wheels are facing relative to the field

int SwerveDrive::GetBackWheelAngleFieldRelative()
{
	float gyroangle = GetGyroAngle();
	int robotRelativeWheelAngle = GetBackWheelAngleRobotRelative();
	int fieldRelativeWheelAngle = ((int)gyroangle + robotRelativeWheelAngle) % 360;
	return fieldRelativeWheelAngle;
}

int SwerveDrive::GetGyroAngle()
{
	//return (int) (gyro->GetAngle()) % 360;
	return 0;
}

int SwerveDrive::ConvertFrontEncoderValue()
{
	int rawEncPos = rotateTalon1->GetEncPosition();
	int moddedValue = rawEncPos % rotateEncoderLines;
	if (0 > moddedValue)
		moddedValue = rotateEncoderLines + moddedValue;
	return moddedValue;
}

int SwerveDrive::ConvertBackEncoderValue()
{
	int rawEncPos = rotateTalon2->GetEncPosition();
	int moddedValue = rawEncPos % rotateEncoderLines;
	if (0 > moddedValue)
		moddedValue = rotateEncoderLines + moddedValue;
	return moddedValue;
}

void SwerveDrive::ZeroRotateEncoders()
{
	rotateTalon1->SetPosition(0);
	rotateTalon2->SetPosition(0);
}

void SwerveDrive::ZeroDriveEncoders()
{
	talon1->SetPosition(0);
	talon2->SetPosition(0);
	talon3->SetPosition(0);
	talon4->SetPosition(0);
}

void SwerveDrive::ResetGyro()
{
	gyro->InitGyro();
}

void SwerveDrive::EnableTurnMotors()
{
    rotateTalon1->EnableControl();
    rotateTalon2->EnableControl();
}
