/*
 * ElevatorArms.h
 *
 *  Created on: Jan 23, 2015
 *      Author: Kazimier
 */

#ifndef SRC_ELEVATORARMS_H_
#define SRC_ELEVATORARMS_H_

#include "Team167Lib.h"

class ElevatorArms
{
private:
	PneumaticPiston *piston1;
	PneumaticPiston *piston2;
	PneumaticPiston *piston3;
	Talon *talon;

public:
	ElevatorArms(int compressorIndex,
					int solenoidIndex1_1, int solenoidIndex1_2,
					int solenoidIndex2_1, int solenoidIndex2_2,
					int solenoidIndex3_1, int solenoidIndex3_2,
					int talonPWMChannel);
	~ElevatorArms();

	void Raise(float speed);
	void Lower(float speed);
	void StopElevator();
	void Open();
	void Close();
	void Stop();
	void Open(int i);
	void Close(int i);
};


#endif /* SRC_ELEVATORARMS_H_ */
