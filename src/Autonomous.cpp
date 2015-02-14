/*
 * Autonomous.cpp
 *
 *  Created on: Jan 22, 2015
 *      Author: moon_gecko
 */

#include "Robot.h"

bool Robot::PickUpTote()
{
	elevatorArms->Close();
	elevatorArms->Raise(1.0);
	mechanumWheels->Right();
}

void Robot::Stop()
{
	mechanumWheels->Stop();
	elevatorArms->Stop();
}

void Robot::StackBin()
{
	elevatorArms->Raise(1.0);
	elevatorArms->Open();
	elevatorArms->Close();
	elevatorArms->Stop();
}

void Robot::RotateLeft()
{

}
