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
			elevatorArms->Close();
			autoStage = RAISE_STUFF;
			break;
		}

		case RAISE_STUFF:
		{
			if (AutoRaiseArmsTimer.Get() < 2)
			{
				if (AutoRaiseArmsTimer.Get() == 0)
					AutoRaiseArmsTimer.Start();

				elevatorArms->Raise(1.0);
			}
			else
			{
				elevatorArms->StopElevator();
				elevatorArms->Stop();
				AutoRaiseArmsTimer.Stop();
				AutoRaiseArmsTimer.Reset();

				autoStage = MOVE_STUFF_RIGHT;
			}

			break;
		}

		case MOVE_STUFF_RIGHT:
		{
			if (AutoDriveTimer.Get() < 3)
			{
				if (AutoDriveTimer.Get() == 0)
					AutoDriveTimer.Start();

				mechanumWheels->Right();
			}
			else
			{
				mechanumWheels->Stop();
				AutoDriveTimer.Stop();
				AutoDriveTimer.Reset();

				autoStage = END;
			}

			break;
		}

		case END:
		{
			AutoRaiseArmsTimer.Stop();
			AutoRaiseArmsTimer.Reset();
			AutoDriveTimer.Stop();
			AutoDriveTimer.Reset();
			elevatorArms->StopElevator();
			elevatorArms->Stop();
			mechanumWheels->Stop();

			break;
		}

		default:
		{
			AutoRaiseArmsTimer.Stop();
			AutoRaiseArmsTimer.Reset();
			AutoDriveTimer.Stop();
			AutoDriveTimer.Reset();
			elevatorArms->StopElevator();
			elevatorArms->Stop();
			mechanumWheels->Stop();

			break;
		}
	}
}
