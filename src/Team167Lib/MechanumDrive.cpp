/*
 * MechanumDrive.cpp
 *
 *  Created on: Jan 31, 2015
 *      Author: moon_gecko
 */
#include "Team167Lib.h"
#include "MechanumDrive.h"

MechanumDrive::MechanumDrive(
		int victor1number,
		int victor2number,
		int victor3number,
		int victor4number,
		float voltagePercent)
{
	Wheels[0] = new Victor(victor1number); //front_left
	Wheels[1] = new Victor(victor2number); //front_right;
	Wheels[2] = new Victor(victor3number); //back_left;
	Wheels[3] = new Victor(victor4number); //back_right;
	voltage_percent = voltagePercent;
	return;
}
MechanumDrive::~MechanumDrive()
{
	delete Wheels;
	return;
}
void MechanumDrive::Disable()
{
	for (int i = 0; i < 4; i++)
		Wheels[i]->Disable();
	return;
}
void MechanumDrive::Stop()
{
	for (int i = 0; i < 4; i++)
			Wheels[i]->Set(0.0);
	return;
}
void MechanumDrive::SetVoltagePercent(float voltagePercent)
{
	voltage_percent = voltagePercent;
	return;
}
void MechanumDrive::Forward()
{
	Wheels[0]->Set(voltage_percent);
	Wheels[1]->Set(-voltage_percent);
	Wheels[2]->Set(voltage_percent);
	Wheels[3]->Set(-voltage_percent);
	return;
}
void MechanumDrive::Reverse()
{
	Wheels[0]->Set(-voltage_percent);
	Wheels[1]->Set(voltage_percent);
	Wheels[2]->Set(-voltage_percent);
	Wheels[3]->Set(voltage_percent);
	return;
}
void MechanumDrive::Left()
{
	Wheels[0]->Set(0.75);
	Wheels[2]->Set(-0.75);
	Wheels[1]->Set(0.75);
	Wheels[3]->Set(-0.75);
	return;
}
void MechanumDrive::Right()
{
	Wheels[0]->Set(-0.75);
	Wheels[2]->Set(0.75);
	Wheels[1]->Set(-0.75);
	Wheels[3]->Set(0.75);
	return;
}
void MechanumDrive::RotateLeft()
{
	Wheels[0]->Set(voltage_percent);
	Wheels[1]->Set(voltage_percent);
	Wheels[2]->Set(voltage_percent);
	Wheels[3]->Set(voltage_percent);
}
void MechanumDrive::RotateRight()
{
	Wheels[0]->Set(-voltage_percent);
	Wheels[1]->Set(-voltage_percent);
	Wheels[2]->Set(-voltage_percent);
	Wheels[3]->Set(-voltage_percent);
}
void MechanumDrive::ForwardLeft()
{
	Wheels[1]->Set(voltage_percent);
	Wheels[2]->Set(voltage_percent);
	Wheels[0]->Set(0.0);
	Wheels[3]->Set(0.0);
}
void MechanumDrive::ForwardRight()
{
	Wheels[0]->Set(voltage_percent);
	Wheels[3]->Set(voltage_percent);
	Wheels[1]->Set(0.0);
	Wheels[2]->Set(0.0);
}
void MechanumDrive::BackLeft()
{
	Wheels[0]->Set(-voltage_percent);
	Wheels[3]->Set(-voltage_percent);
	Wheels[1]->Set(0.0);
	Wheels[2]->Set(0.0);
}
void MechanumDrive::BackRight()
{
	Wheels[1]->Set(-voltage_percent);
	Wheels[2]->Set(-voltage_percent);
	Wheels[0]->Set(0.0);
	Wheels[3]->Set(0.0);
}
