/*
 * ElevatorArms.h
 *
 *  Created on: Jan 23, 2015
 *      Author: Kazimier
 */

#ifndef SRC_ELEVATORARMS_H_
#define SRC_ELEVATORARMS_H_

#include "Team167Lib/Team167Lib.h"

class ElevatorArms
{
private:
	PneumaticPiston *piston1;
	Talon *talon;

public:
	ElevatorArms(int compressorIndex,
					int solenoidIndex1_1, int solenoidIndex1_2,
					int talonPWMChannel);
	~ElevatorArms();

	void Raise(float speed);
	void Lower(float speed);
	void StopElevator();
	void Open();
	void Close();
	void Stop();;
};


#endif /* SRC_ELEVATORARMS_H_ */
