/*
 * MechanumDrive.cpp
 *
 *  Created on: Jan 31, 2015
 *      Author: moon_gecko
 */
#include "_Team167Lib.h"
VictorDrive::VictorDrive(
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
VictorDrive::~VictorDrive()
{
delete Wheels;
return;
}
void VictorDrive::Disable()
{
for (int i = 0; i < 4; i++)
Wheels[i]->Disable();
return;
}
void VictorDrive::Stop()
{
for (int i = 0; i < 4; i++)
Wheels[i]->Set(0.0);
return;
}
void VictorDrive::SetVoltagePercent(float voltagePercent)
{
voltage_percent = voltagePercent;
return;
}
void VictorDrive::Forward()
{
for (int i = 0; i < 4; i++)
Wheels[i]->Set(voltage_percent);
return;
}
void VictorDrive::Reverse()
{
for (int i = 0; i < 4; i++)
Wheels[i]->Set(-voltage_percent);
return;
}
void VictorDrive::Left()
{
Wheels[0]->Set(voltage_percent);
Wheels[2]->Set(-voltage_percent);
Wheels[1]->Set(-voltage_percent);
Wheels[3]->Set(voltage_percent);
return;
}
void VictorDrive::Right()
{
Wheels[0]->Set(-voltage_percent);
Wheels[2]->Set(voltage_percent);
Wheels[1]->Set(voltage_percent);
Wheels[3]->Set(-voltage_percent);
return;
}
void VictorDrive::RotateLeft()
{
Wheels[0]->Set(voltage_percent);
Wheels[2]->Set(voltage_percent);
Wheels[1]->Set(-voltage_percent);
Wheels[3]->Set(-voltage_percent);
}
void VictorDrive::RotateRight()
{
Wheels[0]->Set(-voltage_percent);
Wheels[2]->Set(-voltage_percent);
Wheels[1]->Set(voltage_percent);
Wheels[3]->Set(voltage_percent);
}
void VictorDrive::ForwardLeft()
{
Wheels[1]->Set(voltage_percent);
Wheels[2]->Set(voltage_percent);
Wheels[0]->Set(0.0);
Wheels[3]->Set(0.0);
}
void VictorDrive::ForwardRight()
{
Wheels[0]->Set(voltage_percent);
Wheels[3]->Set(voltage_percent);
Wheels[1]->Set(0.0);
Wheels[2]->Set(0.0);
}
void VictorDrive::BackLeft()
{
Wheels[0]->Set(-voltage_percent);
Wheels[3]->Set(-voltage_percent);
Wheels[1]->Set(0.0);
Wheels[2]->Set(0.0);
}
void VictorDrive::BackRight()
{
Wheels[1]->Set(-voltage_percent);
Wheels[2]->Set(-voltage_percent);
Wheels[0]->Set(0.0);
Wheels[3]->Set(0.0);
}



