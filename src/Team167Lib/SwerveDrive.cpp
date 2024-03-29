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
                rotateTalon1->Set(0);
                rotateTalon2->Set(0);
                return;
        } // If they joystick is in neutral position or the speed is zero, do nothing.

        /*
        SwerveState swerveState1 = TurnRobotFront(angle, speed);
        SwerveState swerveState2 = TurnRobotBack(angle, speed);
        if (swerveState1 != DRIVE_NOT && swerveState2 != DRIVE_NOT)
        {
                rotateTalon1->Set(0);
                rotateTalon2->Set(0);
                talon1->Set(speed);
                talon2->Set(speed);
                talon3->Set(speed);
                talon4->Set(speed);
        }	//stops the motors when the wheels are pointing the right way
                //and tells the drive motors to spin

                 */

        RotateRobotFront(angle);
        //RotateRobotBack(angle);
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
        // always rotate the wheels at maximum speed
        double rotateWheelSpeed1 = 0.5;
        //we assume that when (rotateWheelSpeed == 1.0) the wheels will
        //rotate in a counterclockwise direction

        /*
        int angleToBeTurned = 0;

        if (angle > GetFrontWheelAngle())
                angleToBeTurned = (angle - GetFrontWheelAngle()) % 360;
        else
                angleToBeTurned = (GetFrontWheelAngle() - angle) % 360;
        */

        int currentPosition = ConvertFrontEncoderValue();
        int currentAngleRobotRelative = GetFrontWheelAngleRobotRelative();

        int desiredAngleRobotRelative = 0;
        if (angle > GetGyroAngle())
                desiredAngleRobotRelative = angle - GetGyroAngle();
        else
                desiredAngleRobotRelative = 360 - abs(angle - GetGyroAngle());

        /*
        cout << "currentAngleRobotRelative front = " << currentAngleRobotRelative << endl;
        cout << "desiredAngleRobotRelative front = " << desiredAngleRobotRelative << endl;
        */

        int targetPosition = desiredAngleRobotRelative / 360.0 * rotateEncoderLines;

        //make sure wheels won't have to turn over 180 degrees
        int currentPositionRotated180 = (currentPosition + rotateEncoderLines / 2) % rotateEncoderLines;
        if (targetPosition <= currentPosition && targetPosition >= currentPositionRotated180)
        	rotateWheelSpeed1 *= -1;

        /*
        cout << "rotateWheelSpeed1 = " <<  rotateWheelSpeed1 << endl;
        cout << "currentPosition front = " << currentPosition << endl;
        cout << "targetPosition front = " << targetPosition << endl;
        */

       	//the if statement doesn't use == because that level of precision is practically unattainable for the 'bot
        int difference = abs(currentPosition - targetPosition);
        if (difference > ENCODER_ERROR_AMOUNT && rotateEncoderLines - difference > ENCODER_ERROR_AMOUNT)
        {
        	cout << "currentPosition = " << currentPosition << endl;
        	cout << "targetPosition = " << targetPosition << endl;
        	cout << "so rotate front wheels " << rotateWheelSpeed1 << endl;
        	rotateTalon1->Set(rotateWheelSpeed1);
        }
        else
        	rotateTalon1->Set(0);
}

void SwerveDrive::RotateRobotBack(int angle)
{
		SwerveState returnValue = DRIVE_FORWARDS;

        // always rotate the wheels at maximum speed
        double rotateWheelSpeed2 = 0.5;
        //we assume that when (rotateWheelSpeed == 1.0) the wheels will
        //rotate in a counterclockwise direction

        /*
        int angleToBeTurned = 0;

        if (angle > GetBackWheelAngle())
                angleToBeTurned = (angle - GetBackWheelAngle()) % 360;
        else
                angleToBeTurned = (GetBackWheelAngle() - angle) % 360;

        if (abs(angleToBeTurned - angle) % 360 > 180)
        {
        	rotateWheelSpeed2 *= -1;
        } //the if statement means the wheels won't have to turn over 180 degrees

        int distance = angleToBeTurned / (double) rotateEncoderLines * 360;

        int currentPosition = ConvertBackEncoderValue();
        int targetPosition = distance % rotateEncoderLines;
        */

        int currentPosition = ConvertBackEncoderValue();
        int currentAngleRobotRelative = GetBackWheelAngleRobotRelative();

        int desiredAngleRobotRelative = 0;
        if (angle > GetGyroAngle())
        	desiredAngleRobotRelative = angle - GetGyroAngle();
        else
        	desiredAngleRobotRelative = 360 - abs(angle - GetGyroAngle());

        /*
        cout << "rotateWheelSpeed2 = " <<  rotateWheelSpeed2 << endl;
        cout << "currentAngleRobotRelative back = " << currentAngleRobotRelative << endl;
        cout << "desiredAngleRobotRelative back = " << desiredAngleRobotRelative << endl;
        */

        //make sure wheels won't have to turn over 180 degrees
        if (desiredAngleRobotRelative >= (currentAngleRobotRelative + 180) % 360 && desiredAngleRobotRelative <= currentAngleRobotRelative)
        {
        	rotateWheelSpeed2 *= -1;
        }

        int targetPosition = desiredAngleRobotRelative / 360.0 * rotateEncoderLines;

        /*
        cout << "currentPosition back = " << currentPosition << endl;
        cout << "targetPosition back = " << targetPosition << endl;
        */

       	//the if statement doesn't use == because that level of precision is practically unattainable for the 'bot
        if (abs(currentPosition - targetPosition) > ENCODER_ERROR_AMOUNT)
        {
        	/*
        	cout << "currentPosition = " << currentPosition << endl;
        	cout << "targetPosition = " << targetPosition << endl;
        	cout << "so rotate back wheels " << rotateWheelSpeed2 << endl;
        	*/
        	rotateTalon2->Set(rotateWheelSpeed2);
        }
        else
        	rotateTalon2->Set(0);
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
