/*
 * PneumaticCylinder.cpp
 *
 *  Created on: Jan 15, 2015
 *      Author: phanta
 */

#include "WPILib.h"

class PneumaticPiston {
private:
	Compressor *comp;
	Solenoid *solExtend;
	Solenoid *solRetract;
public:
	PneumaticPiston(int compressorIndex, int solenoidIndex1, int solenoidIndex2) {			// Constructor; initiate variables
		comp = new Compressor(compressorIndex);
		solExtend = new Solenoid(solenoidIndex1);
		solRetract = new Solenoid(solenoidIndex2)
	}

	~PneumaticPiston() {												// Destructor; unload stuff
		delete comp;
		delete solExtend;
		delete solRetract;
	}

	void Extend() {
		// Lorem().ipsum().dolor().set().amet();
	}

	void Retract() {
		// Lorem().ipsum().dolor().set().amet();
	}
};
