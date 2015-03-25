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
	Talon *roller1;
	Talon *roller2;

	DigitalInput ArmsUpSwitch;
	DigitalInput ArmsDownSwitch;
	bool armsClosed;

public:
	ElevatorArms(int solenoidIndex1_1, int solenoidIndex1_2,
					int talonPWMChannel, int roller1PWMChannel, int roller2PWMChannel);
	~ElevatorArms();

	// returns true if arms are fully raised, false otherwise
	bool Raise(float speed);
	// returns true if arms are fully lowered, false otherwise;
	bool Lower(float speed);
	void StopElevator();
	void Open();
	void Close();
	void StopPiston();
	bool ArmsClosed() { return armsClosed; };
	void RollersIn();
	void RollersOut();
	void StopRollers();
	void StopAll();
	void PickUpTote();
};


#endif /* SRC_ELEVATORARMS_H_ */
