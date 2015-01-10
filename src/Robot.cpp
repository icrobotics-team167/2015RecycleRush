#include "WPILib.h"
#include "Team167Lib.h"

class Robot: public IterativeRobot
{
private:
	LiveWindow *lw;

	Joystick *RealJoy1;
	Joystick *RealJoy2;
	SimpleJoystick *Joystick1;
	SimpleJoystick *Joystick2;

	SwerveDrive *swerveWheels;

	Robot()
	{
		RealJoy1 = new Joystick(1);
		RealJoy2 = new Joystick(2);
		Joystick1 = new SimpleJoystick(RealJoy1);
		Joystick2 = new SimpleJoystick(RealJoy2);

		swerveWheels = new SwerveDrive(400, 400, 1, 2, 3, 4, 5, 6, 7, 1, 2, 3, 4);
	}

	void RobotInit()
	{
		lw = LiveWindow::GetInstance();
	}

	void AutonomousInit()
	{

	}

	void AutonomousPeriodic()
	{

	}

	void TeleopInit()
	{

	}

	void TeleopPeriodic()
	{
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

		// Set the Throttle
		bool turbo = Joystick1->Toggled(BUTTON_8);

		/*
		 * raw axis 4 is the throttle axis on the Logitech Extreme 3D Pro joystick
		 * we use the raw axis because the default mappings are incorrect
		 * the throttle, by default, returns values from -1.0 at the plus position to 1.0 at the minus position
		 * we first multiply by -1.0 to get values from -1.0 at the minus position to 1.0 at the plus position
		 * we then add 1.0 and divide by 2 to get final voltage percentages from 0.0 (off) at minus position
		 * to 1.0 (full throttle) at the plus position
		 */
		double throttle_mag = (this->RealJoy1->GetRawAxis(4) * -1.0 + 1.0) / 2.0;

		float abs_x = abs(x), abs_y = abs(y);

		double speed = throttle_mag;

		if (!Joystick1->Pressed(BUTTON_5) && !Joystick1->Pressed(BUTTON_6))
		{
				// if we are not turning get the larger of the x and y values of the joystick posistion,
				// and multiply that by the throttle to get final voltage
				speed *= max(abs_x, abs_y);
		}
		else
		{
				// if we are turning, the rate of turning depends only on the throttle setting,
				// and the rate of turning is limited to 80% voltage maximum
				speed *= 0.8;
		}

		if (speed < 0.1)
			speed = 0.1;

		if (turbo)
			speed *= 1.5;

		if (speed > 1.0)
				speed = 1.0;

		swerveWheels->Drive(z, speed);
	}

	void TestPeriodic()
	{
		lw->Run();
	}
};
