/*
 * Robot.h
 *
 *  Created on: Jan 22, 2015
 *      Author: Kazimier
 */

#ifndef SRC_ROBOT_H_
#define SRC_ROBOT_H_

#include <Timer.h>
#include "Team167Lib/Team167Lib.h"
#include "ElevatorArms.h"

class Robot: public IterativeRobot
{
private:
	enum DrivingStage {START, GRAB_STUFF, RAISE_STUFF, MOVE_FORWARDS, HOOK_STUFF, MOVE_STUFF_LEFT, MOVE_STUFF_RIGHT, ROTATE_RIGHT, ROTATE_LEFT, END};

	Joystick *RealJoy1;
	Joystick *RealJoy2;
	SimpleJoystick *Joystick1;
	SimpleJoystick *Joystick2;

	MechanumDrive *mechanumWheels;
	ElevatorArms *elevatorArms;
	//bool prevJoyState;

	DrivingStage autoStage;

	Timer AutonomousTimer;

	static const int prevZsSize = 3;
	float prevZs[prevZsSize];
	int prevZsIndex;


public:
	Robot();
	~Robot();

	void RobotInit();
	void DisabledInit();
	void DisabledPeriodic();
	void AutonomousInit();
	void AutonomousPeriodic();
	void TeleopInit();
	void TeleopPeriodic();
	void JoystickOne();
	void JoystickTwo();

	// Autonomous routines
	void PickUpToteAndDrive();
	void PickUpTrashAndTote();
	void DriveIntoZone();
};


#endif /* SRC_ROBOT_H_ */
