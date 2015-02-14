/*
 * AutoPilot.cpp
 *
 *  Created on: Feb 13, 2015
 *      Author: phanta
 */

#include <AutoPilot.h>
#include <ctime>

AutoPilot::AutoPilot(Robot bot, DrivingStage stage = START) {
	Active = true;
	CurrentStage = stage;
	Controller = bot;
}

AutoPilot::~AutoPilot() {
	delete Controller;
}

void AutoPilot::Drive() { // Actually really inefficient - I think some kind of Runnable thing would have worked better
	if (!Active) {
		return;
	}

	switch (CurrentStage) {
		case START: {
			AdvanceStage();
			break;
		}

		case GRAB_STUFF: {
			if (!StageHasInitialized) {
				Controller->elevatorArms->Close();
				WaitTime = 10;
				StageHasInitialized = true;
			}

			if (WaitTime == 0) {
				AdvanceStage();
			}
			break;
		}

		case RAISE_STUFF: {
			if (!StageHasInitialized) {
				Controller->elevatorArms->Raise(1.0F);
				WaitTime = 70;
				StageHasInitialized = true;
			}

			if (WaitTime == 0) {
				AdvanceStage();
			}
			break;
		}

		case MOVE_STUFF_RIGHT: {
			if (!StageHasInitialized) {
				Controller->mechanumWheels->Right();
				WaitTime = 200;
				StageHasInitialized = true;
			}

			if (WaitTime == 0) {
				AdvanceStage();
			}
			break;
		}

		case END: {
			SetActive(false);
			break;
		}
	}

	if (WaitTime > 0) {
		WaitTime--;
	}
}

void AutoPilot::SetStage(DrivingStage stage) {
	CurrentStage = stage;
}

void AutoPilot::AdvanceStage() {
	CurrentStage++;
	StageHasInitialized = false;
}

bool AutoPilot::IsActive() {
	return Active;
}

void AutoPilot::SetActive(bool i) {
	Active = i;
}
