/*
 * MechanumDrive.cpp
 *
 *  Created on: Jan 31, 2015
 *      Author: moon_gecko
 */
#include "Team167Lib.h"
MechanumDrive::MechanumDrive(
Victor* front_left,
Victor* front_right,
Victor* back_left,
Victor* back_right,
float voltagePercent)
{
Wheels[0] = front_left;
Wheels[1] = front_right;
Wheels[2] = back_left;
Wheels[3] = back_right;
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
for (int i = 0; i < 4; i++)
Wheels[i]->Set(voltage_percent);
return;
}
void MechanumDrive::Reverse()
{
for (int i = 0; i < 4; i++)
Wheels[i]->Set(-voltage_percent);
return;
}
void MechanumDrive::Left()
{
Wheels[0]->Set(voltage_percent);
Wheels[2]->Set(-voltage_percent);
Wheels[1]->Set(-voltage_percent);
Wheels[3]->Set(voltage_percent);
return;
}
void MechanumDrive::Right()
{
Wheels[0]->Set(-voltage_percent);
Wheels[2]->Set(voltage_percent);
Wheels[1]->Set(voltage_percent);
Wheels[3]->Set(-voltage_percent);
return;
}
void MechanumDrive::RotateLeft()
{
Wheels[0]->Set(voltage_percent);
Wheels[2]->Set(voltage_percent);
Wheels[1]->Set(-voltage_percent);
Wheels[3]->Set(-voltage_percent);
}
void MechanumDrive::RotateRight()
{
Wheels[0]->Set(-voltage_percent);
Wheels[2]->Set(-voltage_percent);
Wheels[1]->Set(voltage_percent);
Wheels[3]->Set(voltage_percent);
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



