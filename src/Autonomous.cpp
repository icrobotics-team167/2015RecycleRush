#include "Robot.h"

void Robot::PickUpToteAndDrive()
{
	switch (autoStage)
	{
		case START:
		{
			mechanumWheels->SetVoltagePercent(0.7);
			autoStage = GRAB_STUFF;
			break;
		}

		case GRAB_STUFF:
		{
			if (AutonomousTimer.Get() < 0.5)
			{
				if (AutonomousTimer.Get() == 0)
					AutonomousTimer.Start();

				elevatorArms->Close();
			}
			else
			{
				elevatorArms->StopElevator();
				elevatorArms->Stop();
				AutonomousTimer.Stop();
				AutonomousTimer.Reset();

				autoStage = RAISE_STUFF;
			}

			break;
		}

		case RAISE_STUFF:
		{
			if (AutonomousTimer.Get() < 1)
			{
				if (AutonomousTimer.Get() == 0)
					AutonomousTimer.Start();

				elevatorArms->Raise(1.0);
			}
			else
			{
				elevatorArms->StopElevator();
				elevatorArms->Stop();
				AutonomousTimer.Stop();
				AutonomousTimer.Reset();

				autoStage = ROTATE_RIGHT;
			}

			break;
		}

		case ROTATE_RIGHT:
		{
			if (AutonomousTimer.Get() < 1)
			{
				if (AutonomousTimer.Get() == 0)
				{
					mechanumWheels->SetVoltagePercent(0.5);
					AutonomousTimer.Start();
				}

				mechanumWheels->RotateLeft();
			}
			else
			{
				mechanumWheels->Stop();
				AutonomousTimer.Stop();
				AutonomousTimer.Reset();
				mechanumWheels->SetVoltagePercent(0.7);

				autoStage = MOVE_FORWARDS;
			}

			break;
		}

		case MOVE_FORWARDS:
		{
			if (AutonomousTimer.Get() < 1.2)
			{
				if (AutonomousTimer.Get() == 0)
					AutonomousTimer.Start();

				mechanumWheels->Forward();
			}
			else
			{
				mechanumWheels->Stop();
				AutonomousTimer.Stop();
				AutonomousTimer.Reset();

				autoStage = ROTATE_LEFT;
			}

			break;
		}

		case ROTATE_LEFT:
				{
					if (AutonomousTimer.Get() < 1)
					{
						if (AutonomousTimer.Get() == 0)
						{
							mechanumWheels->SetVoltagePercent(0.5);
							AutonomousTimer.Start();
						}

						mechanumWheels->RotateRight();
					}
					else
					{
						mechanumWheels->Stop();
						AutonomousTimer.Stop();
						AutonomousTimer.Reset();
						mechanumWheels->SetVoltagePercent(0.7);

						autoStage = END;
					}

					break;
				}

		case END:
		{
			AutonomousTimer.Stop();
			AutonomousTimer.Reset();
			elevatorArms->StopElevator();
			elevatorArms->Stop();
			mechanumWheels->Stop();

			break;
		}

		default:
		{
			AutonomousTimer.Stop();
			AutonomousTimer.Reset();
			elevatorArms->StopElevator();
			elevatorArms->Stop();
			mechanumWheels->Stop();

			break;
		}
	}
}

void Robot::PickUpTrashAndTote()
{
	switch (autoStage)
	{
		case START:
		{
			mechanumWheels->SetVoltagePercent(0.7);
			autoStage = GRAB_STUFF;
			break;
		}

		case GRAB_STUFF:
		{
			elevatorArms->Close();
			autoStage = RAISE_STUFF;
			break;
		}

		case RAISE_STUFF:
		{
			if (AutonomousTimer.Get() < 2)
			{
				if (AutonomousTimer.Get() == 0)
					AutonomousTimer.Start();

				elevatorArms->Raise(1.0);
			}
			else
			{
				elevatorArms->StopElevator();
				elevatorArms->Stop();
				AutonomousTimer.Stop();
				AutonomousTimer.Reset();

				autoStage = MOVE_FORWARDS;
			}

			break;
		}

		case MOVE_FORWARDS:
		{
			if (AutonomousTimer.Get() < 1) {
				if (AutonomousTimer.Get() == 0) {
					AutonomousTimer.Start();

					mechanumWheels->Forward();
				}
			}
			else {
				mechanumWheels->Stop();
				AutonomousTimer.Stop();
				AutonomousTimer.Reset();

				autoStage = HOOK_STUFF;
			}

			break;
		}

		case HOOK_STUFF:
		{
			if (AutonomousTimer.Get() < 1) {
				if (AutonomousTimer.Get() == 0) {
					AutonomousTimer.Start();

					elevatorArms->Raise(0.7);
				}
			}
			else {
				elevatorArms->StopElevator();
				AutonomousTimer.Stop();
				AutonomousTimer.Reset();

				autoStage = MOVE_STUFF_LEFT;
			}

			break;
		}

		case MOVE_STUFF_LEFT:
		{
			if (AutonomousTimer.Get() < 3)
			{
				if (AutonomousTimer.Get() == 0)
					AutonomousTimer.Start();

				mechanumWheels->Left();
			}
			else
			{
				mechanumWheels->Stop();
				AutonomousTimer.Stop();
				AutonomousTimer.Reset();

				autoStage = END;
			}

			break;
		}

		case END:
		{
			AutonomousTimer.Stop();
			AutonomousTimer.Reset();
			elevatorArms->StopElevator();
			elevatorArms->Stop();
			mechanumWheels->Stop();

			break;
		}

		default:
		{
			AutonomousTimer.Stop();
			AutonomousTimer.Reset();
			elevatorArms->StopElevator();
			elevatorArms->Stop();
			mechanumWheels->Stop();

			break;
		}
	}
}

void Robot::DriveIntoZone() {
	if (AutonomousTimer.Get() < 3) {
		if (AutonomousTimer.Get() == 0) {
			AutonomousTimer.Start();
		}

		mechanumWheels->Reverse();
	}
	else {
		mechanumWheels->Stop();
		AutonomousTimer.Stop();
		AutonomousTimer.Reset();
	}
}
