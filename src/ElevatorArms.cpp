/*
 * ElevatorArms.cpp
 *
 *  Created on: Jan 15, 2015
 *      Author: Katie Chace
 */

#include "ElevatorArms.h"

ElevatorArms::ElevatorArms(int compressorIndex,
                int solenoidIndex1_1, int solenoidIndex1_2,
                int solenoidIndex2_1, int solenoidIndex2_2,
                int solenoidIndex3_1, int solenoidIndex3_2,
                int talonPWMchannel)

{
        piston1 = new PneumaticPiston(compressorIndex, solenoidIndex1_1, solenoidIndex1_2);
        piston2 = new PneumaticPiston(compressorIndex, solenoidIndex2_1, solenoidIndex2_2);
        piston3 = new PneumaticPiston(compressorIndex, solenoidIndex3_1, solenoidIndex3_2);
        talon = new Talon(talonPWMchannel);

}

ElevatorArms::~ElevatorArms()
{
        delete piston1;
        delete piston2;
        delete piston3;
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
        piston2->Extend();
        piston3->Extend();
}

void ElevatorArms::Close()
{
        piston1->Retract();
        piston2->Retract();
        piston3->Retract();
}

void ElevatorArms::Stop() {
        piston1->ForceStop();
        piston2->ForceStop();
        piston3->ForceStop();
}

void ElevatorArms::Open(int i) {
        switch (i) {
        case 1:
                piston1->Extend();
                break;
        case 2:
                piston2->Extend();
                break;
        case 3:
                piston3->Extend();
                break;
        }
}

void ElevatorArms::Close(int i) {
        switch (i) {
        case 1:
                piston1->Retract();
                break;
        case 2:
                piston2->Retract();
                break;
        case 3:
                piston3->Retract();
                break;
        }
}
