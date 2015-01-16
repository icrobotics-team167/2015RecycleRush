/*
 * ElevatorArms.cpp
 *
 *  Created on: Jan 15, 2015
 *      Author: Katie Chace
 */

#include "WPILib.h"
#include "Team167Lib.h"


class ElevatorArms
{
private:
	PneumaticPiston *piston1;
	PneumaticPiston *piston2;
	PneumaticPiston *piston3;
	Talon *talon;


public:
	ElevatorArms(
				int compressorIndex,
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

	~ElevatorArms()
	{
		delete piston1;
		delete piston2;
		delete piston3;
		delete talon;
	}

	void Raise(float speed)
	{
		talon->Set(abs(speed));
	}

	void Lower(float speed)
	{
		talon->Set(-(abs(speed)));
	}

	void StopElevator()
	{
		talon->Set(0);
	}

	void Open()
	{
		piston1->Extend();
		piston2->Extend();
		piston3->Extend();
	}

	void Close()
	{
		piston1->Retract();
		piston2->Retract();
		piston3->Retract();
	}
};
