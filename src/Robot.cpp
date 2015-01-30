#include "Robot.h"

Robot::Robot()
{
        RealJoy1 = new Joystick(1);
        RealJoy2 = new Joystick(2);
        Joystick1 = new SimpleJoystick(RealJoy1);
        Joystick2 = new SimpleJoystick(RealJoy2);

        // current parameters are just placeholders for actual values
        elevatorArms = new ElevatorArms(3, 1, 4, 1, 5, 9, 2, 6);

        // current parameters are just placeholders for actual values
        swerveWheels = new SwerveDrive(400, 400, 1337, 1, 2, 3, 4, 5, 6, 7);

        autoState = PICK_UP_TOTE;
}

Robot::~Robot()
{
        delete RealJoy1;
        delete RealJoy2;
        delete Joystick1;
        delete Joystick2;
        delete swerveWheels;
        delete elevatorArms;
}

void Robot::RobotInit()
{

}

void Robot::AutonomousInit()
{

}

void Robot::AutonomousPeriodic()
{

        switch(autoState)
        {
                case PICK_UP_TOTE:
                		PickUpTote();

                        break;
                case STOP:
                        Stop();

                        break;
                case DRIVE_FORWARD:
                        DriveForward(1);			// Placeholder
                        break;
        }

}

void Robot::TeleopInit()
{

}

void Robot::TeleopPeriodic()
{
        JoystickOne();
        JoystickTwo();
}

void Robot::JoystickOne() {
        // Joy1 Control Code
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
                        speed *= std::max(abs_x, abs_y);
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

void Robot::JoystickTwo() {
        // Joy2 Control Code

        float y2 = -this->RealJoy2->GetAxis(Joystick::kYAxis);
        double throttle_mag2 = (this->RealJoy2->GetRawAxis(4) * -1.0 + 1.0) / 2.0;
        float abs_y2 = abs(y2);
        float armSpeed = throttle_mag2 * abs_y2;

        if (armSpeed < 0)
                elevatorArms->Raise(armSpeed);
        else
                elevatorArms->Lower(armSpeed);

        // Deprecated code
        /*bool open = Joystick2->Toggled(BUTTON_3);
        bool close = Joystick2->Toggled(BUTTON_1);

        if (open)
                elevatorArms->Open();
        if (close)
                elevatorArms->Close();

        if ((!open && !close) || (open && close))
                elevatorArms->Stop();*/

        if (Joystick2->Toggled(BUTTON_1))					// Trigger - Open all
                elevatorArms->Close();
        else {
                if (Joystick2->Toggled(BUTTON_8))
                        elevatorArms->Close(1);						// Button 7/8 - Open/close piston 1
                else if (Joystick2->Toggled(BUTTON_7))
                        elevatorArms->Open(1);

                if (Joystick2->Toggled(BUTTON_10))
                        elevatorArms->Close(2);						// Button 9/10 - Open/close piston 2
                else if (Joystick2->Toggled(BUTTON_9))
                        elevatorArms->Open(2);

                if (Joystick2->Toggled(BUTTON_12))
                        elevatorArms->Close(3);						// Button 11/12 - Open/close piston 3
                else if (Joystick2->Toggled(BUTTON_11))
                        elevatorArms->Open(3);
        }
}

START_ROBOT_CLASS(Robot);
