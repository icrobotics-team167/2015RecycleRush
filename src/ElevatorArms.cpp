/*
 * ElevatorArms.cpp
 *
 *  Created on: Jan 15, 2015
 *      Author: Katie Chace
 */

#include "ElevatorArms.h"

ElevatorArms::ElevatorArms(int compressorIndex,
                int solenoidIndex1_1, int solenoidIndex1_2,
                int talonPWMchannel)

{
        piston1 = new PneumaticPiston(compressorIndex, solenoidIndex1_1, solenoidIndex1_2);
        talon = new Talon(talonPWMchannel);

}

ElevatorArms::~ElevatorArms()
{
        delete piston1;;
        delete talon;
}

void ElevatorArms::Raise(float speed)
{
        talon->Set(abs(speed));
}

void ElevatorArms::Lower(float speed)
{
        talon->Set(-(abs(speed)));
}

void ElevatorArms::StopElevator()
{
        talon->Set(0);
}

void ElevatorArms::Open()
{
        piston1->Extend();
}

void ElevatorArms::Close()
{
        piston1->Retract();
}

void ElevatorArms::Stop()
{
        piston1->ForceStop();
}
