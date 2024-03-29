/*
 * Robot.h
 *
 *  Created on: Jan 22, 2015
 *      Author: Kazimier
 */

#ifndef SRC_ROBOT_H_
#define SRC_ROBOT_H_


#include "Team167Lib/Team167Lib.h"
#include "ElevatorArms.h"

class Robot: public IterativeRobot
{
private:
	enum AutonomousState { PICK_UP_TOTE, STOP, DRIVE_FORWARD };
	Joystick *RealJoy1;
	Joystick *RealJoy2;
	SimpleJoystick *Joystick1;
	SimpleJoystick *Joystick2;

	SwerveDrive *swerveWheels;
	ElevatorArms *elevatorArms;
	AutonomousState autoState;

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
	void PickUpTote();
	void Stop();
	void DriveForward();
	void StackBin();
};


#endif /* SRC_ROBOT_H_ */
