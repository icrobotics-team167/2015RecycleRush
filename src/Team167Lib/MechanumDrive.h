/*
 * MechanumDrive.h
 *
 *  Created on: Jan 31, 2015
 *      Author: moon_gecko
 */
#ifndef MECHANUMDRIVE_H
#define MECHANUMDRIVE_H
class MechanumDrive
{
public:
MechanumDrive(
	int victor1number,
	int victor2number,
	int victor3number,
	int victor4number,
	float voltagePercent = 0.0);
~MechanumDrive();
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
