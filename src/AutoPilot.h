/*
 * AutoPilot.h
 *
 *  Created on: Feb 13, 2015
 *      Author: phanta
 */
#include <ctime>
#ifndef SRC_AUTOPILOT_H_
#define SRC_AUTOPILOT_H_

class AutoPilot {
private:
	enum DrivingStage {START, GRAB_STUFF, RAISE_STUFF, MOVE_STUFF_RIGHT, END};
	bool Active;
	DrivingStage CurrentStage;
	Robot *Controller;
	bool StageHasInitialized;
	long WaitTime;

public:
	AutoPilot(Robot bot, DrivingStage stage = START);
	virtual ~AutoPilot();
	void Drive();
	void SetStage(DrivingStage stage);
	bool IsActive();
	void SetActive(bool i);
	void AdvanceStage();
};

#endif /* SRC_AUTOPILOT_H_ */
