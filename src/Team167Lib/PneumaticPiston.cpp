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
	DoubleSolenoid *sol;
public:

	/*
	 *	Constructor - Initialize variables and stuff
	 *	int compressorIndex - Index for the air compressor
	 *	int solenoidIndex1 - Index for the extend solenoid
	 *	int solenoidIndex2 - Index for the retract solenoid
	 */
	PneumaticPiston(int compressorIndex, int solenoidIndex1, int solenoidIndex2) {
		comp = new Compressor(compressorIndex);
		sol = new DoubleSolenoid(solenoidIndex1, solenoidIndex2);
	}

	/*
	 *	Destructor - Unload variables and stuff
	 */
	~PneumaticPiston() {
		delete comp;
		delete sol;
	}

	/*
	 * 	Extend piston
	 */
	void Extend() {
		// Lorem().ipsum().dolor().set().amet();
	}

	/*
	 * 	Retract piston
	 */
	void Retract() {
		// Lorem().ipsum().dolor().set().amet();
	}
};
