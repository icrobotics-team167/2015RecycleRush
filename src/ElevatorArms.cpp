/*
* ElevatorArms.cpp
*
*  Created on: Jan 15, 2015
*  Author: Katie Chace
*/

#include "ElevatorArms.h"

ElevatorArms::ElevatorArms(int solenoidIndex1_1, int solenoidIndex1_2,
							int talonPWMchannel, int roller1PWMChannel, int roller2PWMChannel) :
	ArmsUpSwitch(1),
	ArmsDownSwitch(2)


{
	piston1 = new PneumaticPiston(solenoidIndex1_1, solenoidIndex1_2);
	talon = new Talon(talonPWMchannel);

	roller1 = new Talon(roller1PWMChannel);
	roller2 = new Talon(roller2PWMChannel);

	armsClosed = false;
}

ElevatorArms::~ElevatorArms()
{
	delete piston1;
	delete talon;
}

bool ElevatorArms::Raise(float speed)
{
	if (!ArmsUpSwitch.Get())
	{
		talon->Set(-fabs(speed));
		return false;
	}
	else
	{
		talon->Set(0);
		return true;
	}
}

bool ElevatorArms::Lower(float speed)
{
	if (ArmsDownSwitch.Get())
	{
		talon->Set(fabs(speed));
		return false;
	}
	else
	{
		talon->Set(0);
		return true;
	}
}

void ElevatorArms::StopElevator()
{
	talon->Set(0);
}

void ElevatorArms::Open()
{
	piston1->Retract();
	armsClosed = false;
}

void ElevatorArms::Close()
{
	piston1->Extend();
	armsClosed = true;
}

void ElevatorArms::StopPiston()
{
	piston1->ForceStop();
}

void ElevatorArms::RollersIn()
{
	roller1->Set(1);
	roller2->Set(-1);
}

void ElevatorArms::RollersOut()
{
	roller1->Set(-1);
	roller2->Set(1);
}

void ElevatorArms::StopRollers()
{
	roller1->Set(0);
	roller2->Set(0);
}

void ElevatorArms::StopAll()
{
	StopElevator();
	StopPiston();
	StopRollers();
}
