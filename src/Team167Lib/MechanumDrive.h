/*
 * MechanumDrive.h
 *
 *  Created on: Jan 31, 2015
 *      Author: moon_gecko
 */
#ifndef VICTORDRIVE_H
#define VICTORDRIVE_H
class VictorDrive
{
public:
VictorDrive(
Victor* front_left,
Victor* front_right,
Victor* back_left,
Victor* back_right,
float voltagePercent = 0.0);
~VictorDrive();
// disables the drive
void Disable();
// stop all motors
void Stop();
// sets the voltage percent to drive with
void SetVoltagePercent(float voltagePercent);
// drives forward
void Forward();
// drives backwards
void Reverse();
// strafes left
void Left();
// strafes right
void Right();
// rotates left
void RotateLeft();
// rotates right
void RotateRight();
// drives diagonally left
void ForwardLeft();
// drives diagonally left
void ForwardRight();
// drives diagonally left
void BackLeft();
// drives diagonally left
void BackRight();
private:
Victor* Wheels[4];
float voltage_percent;
};
#endif
