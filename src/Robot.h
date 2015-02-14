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
	enum DrivingStage {START, GRAB_STUFF, RAISE_STUFF, MOVE_STUFF_RIGHT, END};

	Joystick *RealJoy1;
	Joystick *RealJoy2;
	SimpleJoystick *Joystick1;
	SimpleJoystick *Joystick2;

	MechanumDrive *mechanumWheels;
	ElevatorArms *elevatorArms;

	DrivingStage autoStage;

	Timer AutoRaiseArmsTimer;
	Timer AutoDriveTimer;

public:
	Robot();
	~Robot();

	void RobotInit();
	void AutonomousInit();
	void AutonomousPeriodic();
	void TeleopInit();
	void TeleopPeriodic();
	void JoystickOne();
	void JoystickTwo();

	// Autonomous routings
	void PickUpToteAndDrive();
};


#endif /* SRC_ROBOT_H_ */
