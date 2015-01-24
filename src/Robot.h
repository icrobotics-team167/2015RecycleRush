/*
 * Robot.h
 *
 *  Created on: Jan 22, 2015
 *      Author: Kazimier
 */

#ifndef SRC_ROBOT_H_
#define SRC_ROBOT_H_


#include "Team167Lib.h"
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
	void AutonomousInit();
	void AutonomousPeriodic();
	void TeleopInit();
	void TeleopPeriodic();
	void JoystickOne();
	void JoystickTwo();
	bool PickUpTote();
	void Stop();
	bool DriveForward(double distance);
	void StackBin();
	bool Turn(int angle);
};


#endif /* SRC_ROBOT_H_ */
