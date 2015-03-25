#include "Robot.h"
#include <iostream>

using std::cout;
using std::endl;

Robot::Robot()
{
	RealJoy1 = new Joystick(0);
	RealJoy2 = new Joystick(1);
	Joystick1 = new SimpleJoystick(RealJoy1);
	Joystick2 = new SimpleJoystick(RealJoy2);

	// current parameters are just placeholders for actual values
	elevatorArms = new ElevatorArms(1, 0, 4, 0, 3);

	// current parameters are actual values for the mechanum robot
	mechanumWheels = new MechanumDrive(7, 1, 9, 2, 1.0);

	autoStage = START;
	//prevJoyState = false;

	for (int i = 0; i < prevZsSize; ++i)
		prevZs[i] = 0;
	prevZsIndex = 0;

	pickUpToteDone = false;
}

Robot::~Robot()
{
	delete RealJoy1;
	delete RealJoy2;
	delete Joystick1;
	delete Joystick2;
	delete mechanumWheels;
	delete elevatorArms;
}

void Robot::RobotInit()
{
	Joystick1->DisableToggleAll();
	Joystick2->DisableToggleAll();
}

void Robot::DisabledInit()
{
	Joystick1->DisableToggleAll();
	Joystick2->DisableToggleAll();
}

void Robot::DisabledPeriodic()
{

}

void Robot::AutonomousInit()
{
	autoStage = START;
	AutonomousTimer.Stop();
	AutonomousTimer.Reset();
}

void Robot::AutonomousPeriodic()
{
	PickUpToteAndDrive();
}

void Robot::TeleopInit()
{
	Joystick1->DisableToggleAll();
	Joystick2->DisableToggleAll();
}

void Robot::TeleopPeriodic()
{
	JoystickOne();
	JoystickTwo();
}

void Robot::JoystickOne() {

	this->Joystick1->Update();

	//-------------------------
	// drive logic (input side)
	//-------------------------
	// get joystick position
	float x = this->RealJoy1->GetAxis(Joystick::kXAxis);
	float y = -this->RealJoy1->GetAxis(Joystick::kYAxis);
	float z = Vector3::GetRotation(x, y);

	// raw axis 3 is the twist axis on the Logitech Extreme 3D Pro joystick
	// we use the raw axis because the default mappings are incorrect
	//float twist = this->RealJoy1->GetRawAxis(3);

	// Set the throttle
	bool turbo = Joystick1->Toggled(BUTTON_12);

	/*
	* raw axis 4 is the throttle axis on the Logitech Extreme 3D Pro joystick
	* we use the raw axis because the default mappings are incorrect
	* the throttle, by default, returns values from -1.0 at the plus position to 1.0 at the minus position
	* we first multiply by -1.0 to get values from -1.0 at the minus position to 1.0 at the plus position
	* we then add 1.0 and divide by 2 to get final voltage percentages from 0.0 (off) at minus position
	* to 1.0 (full throttle) at the plus position
	*/
	double throttle_mag = (this->RealJoy1->GetThrottle() * -1.0 + 1.0) / 2.0;
	SmartDashboard::PutNumber("throttle", throttle_mag);

	float abs_x = fabs(x), abs_y = fabs(y);

	double voltagePercent = throttle_mag;

	if (!Joystick1->Pressed(BUTTON_5) && !Joystick1->Pressed(BUTTON_6))
	{
	// if we are not turning get the larger of the x and y values of the joystick posistion,
	// and multiply that by the throttle to get final voltage
		if (abs_x > abs_y)
			voltagePercent *= abs_x;
		else
			voltagePercent *= abs_y;
	}
	else
	{
		// if we are turning, the rate of turning depends only on the throttle setting,
		// and the rate of turning is limited to 80% voltage maximum
		voltagePercent *= 0.6;
	}

	if (voltagePercent < 0.1)
		voltagePercent = 0.1;

	if (!turbo)
		voltagePercent *= 0.7;

	if (voltagePercent > 1.0)
		voltagePercent = 1.0;

	mechanumWheels->SetVoltagePercent(voltagePercent);

	double strafeVoltagePercent = 0.75;

	SmartDashboard::PutNumber("abs_x", abs_x);
	SmartDashboard::PutNumber("abs_y", abs_y);
	SmartDashboard::PutNumber("voltagePercent", voltagePercent);
	SmartDashboard::PutNumber("z", z);

	// if we suddenly go from driving forward to driving backward, delay the switch so the robot doesn't tip over
	bool prevForward = false;
	for (int i = 0; i < prevZsSize; ++i)
	{
		if (prevZs[i] >= 45 && prevZs[i] < 135)
			prevForward = true;
	}

	if (prevForward && z >= 225 && z < 315)
		Wait(0.5);

	/*
	cout << "volt" << voltagePercent << endl;
	cout << "throttle" << throttle_mag << endl;
	*/

	if (Joystick1->Pressed(BUTTON_6))
	{
		// rotate right
		mechanumWheels->RotateLeft();
	}
	else if (Joystick1->Pressed(BUTTON_5))
	{
		// rotate left
		mechanumWheels->RotateRight();
	}
	else if (Vector3::GetMagnitude(x, y) < 0.25)
	{
		// stop
		mechanumWheels->Stop();
	}
	else if (z >= 225 && z < 315)
	{
		// forward
		mechanumWheels->Reverse();
	}
	else if ((z >= 315 && z <= 360) || (z >= 0 && z < 45))
	{
		// right
		mechanumWheels->SetVoltagePercent(strafeVoltagePercent);
		mechanumWheels->Left();
	}
	else if(z >= 45 && z < 135)
	{
		// backwards
		mechanumWheels->Forward();
	}
	else if (z >= 135 && z < 225)
	{
		// left
		mechanumWheels->SetVoltagePercent(strafeVoltagePercent);
		mechanumWheels->Right();
	}
	else
	{
		// stop
		mechanumWheels->Stop();
	}

	prevZs[prevZsIndex] = z;
	prevZsIndex = (prevZsIndex + 1) % prevZsSize;
}

void Robot::JoystickTwo() {
	// Joy2 Control Code

	this->Joystick2->Update();

	float y2 = -this->RealJoy2->GetAxis(Joystick::kYAxis);
	double throttle_mag2 = (this->RealJoy2->GetThrottle() * -1.0 + 1.0) / 2.0;
	float armSpeed = throttle_mag2 * y2;

	SmartDashboard::PutNumber("y2", y2);
	SmartDashboard::PutNumber("armspeed", armSpeed);

	if (armSpeed < 0)
        elevatorArms->Lower(armSpeed);
	else
        elevatorArms->Raise(armSpeed);


	if (Joystick2->Released(BUTTON_1) && elevatorArms->ArmsClosed())
		elevatorArms->Open();
	else if (Joystick2->Released(BUTTON_1) && !elevatorArms->ArmsClosed())
		elevatorArms->Close();
	else
		elevatorArms->StopPiston();

	if (Joystick2->Pressed(BUTTON_2))
		elevatorArms->RollersIn();
	else if (Joystick2->Pressed(BUTTON_12 ))
		elevatorArms->RollersOut();
	else
		elevatorArms->StopRollers();

	if (Joystick2->Toggled(BUTTON_11) && !pickUpToteDone)
		PickUpTote();
	else
	{
		toteStage = TOTE_END;
		PickUpTote();
		Joystick2->DisableToggle(BUTTON_11);
		pickUpToteDone = false;
	}
}

START_ROBOT_CLASS(Robot);
