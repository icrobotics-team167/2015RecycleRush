/*
* ElevatorArms.cpp
*
*  Created on: Jan 15, 2015
*  Author: Katie Chace
*/

#include "ElevatorArms.h"

ElevatorArms::ElevatorArms(int compressorIndex,
							int solenoidIndex1_1, int solenoidIndex1_2,
							int talonPWMchannel) :
	ArmsDownSwitch(0),
	ArmsUpSwitch(1)

{
	piston1 = new PneumaticPiston(compressorIndex, solenoidIndex1_1, solenoidIndex1_2);
	talon = new Talon(talonPWMchannel);

	armsClosed = false;
}

ElevatorArms::~ElevatorArms()
{
	delete piston1;;
	delete talon;
}

void ElevatorArms::Raise(float speed)
{
	if (!ArmsUpSwitch.Get())
		talon->Set(-speed);
}

void ElevatorArms::Lower(float speed)
{
	if (!ArmsDownSwitch.Get())
		talon->Set(speed);
}

void ElevatorArms::StopElevator()
{
	talon->Set(0);
}

void ElevatorArms::Open()
{
	piston1->Extend();
	armsClosed = false;
}

void ElevatorArms::Close()
{
	piston1->Retract();
	armsClosed = true;
}

void ElevatorArms::Stop()
{
	piston1->ForceStop();
}
