/*
 * PneumaticCylinder.cpp
 *
 *  Created on: Jan 15, 2015
 *      Author: phanta
 */

#include "WPILib.h"
	PneumaticPiston::PneumaticPiston(int compressorIndex, int solenoidIndex1, int solenoidIndex2) {
		comp = new Compressor(compressorIndex);
		sol = new DoubleSolenoid(solenoidIndex1, solenoidIndex2);
	}

	/*
	 *	Destructor - Unload variables and stuff
	 */
	PneumaticPiston::~PneumaticPiston() {
		delete comp;
		delete sol;
	}

	/*
	 * 	Extend piston
	 */
	void PneumaticPiston::Extend() {
		sol->Set(DoubleSolenoid::kForward);
		comp->Start();
	}

	/*
	 * 	Retract piston
	 */
	void PneumaticPiston::Retract() {
		sol->Set(DoubleSolenoid::kReverse);
		comp->Start();
	}

	/*
	 * 	Force the piston to stop whatever it's doing (e.g. extending or retracting)
	 */
	void PneumaticPiston::ForceStop() {
		sol->Set(DoubleSolenoid::kOff);
		comp->Stop();
	}
};
