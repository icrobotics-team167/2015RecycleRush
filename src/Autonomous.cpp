/*
 * Autonomous.cpp
 *
 *  Created on: Jan 22, 2015
 *      Author: moon_gecko
 */

#include "Robot.h"

bool Robot::PickUpTote()
{
        elevatorArms->Open();
        bool done = swerveWheels->DriveACertainDistance(2.0, 1.0);
        if (done)
                elevatorArms->Close();
        return done;
}

void Robot::Stop()
{
        swerveWheels->Stop();
        elevatorArms->Stop();
}

bool Robot::DriveForward(double distance)
{
        return swerveWheels->DriveACertainDistance(distance, 1.0); //drive 8.92 feet and at speed 1.0 (full speed)
}

void Robot::StackBin ()
{
	elevatorArms->Raise(1.0);
	elevatorArms->Open();
	elevatorArms->Close();
	elevatorArms->Stop();
}

bool Robot::Turn(int angle)
{
	return swerveWheels->TurnRobot(angle);
}

bool Robot::Rotate(int gyroAngle, bool clockwise)
{
	swerveWheels->RotateRobot(clockwise, 1.0);
	return swerveWheels->GetGyroAngle();

}

