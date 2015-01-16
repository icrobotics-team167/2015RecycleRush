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

	/*
	 *	Constructor - Initialize variables and stuff
	 *	int compressorIndex - Index for the air compressor
	 *	int solenoidIndex1 - Index for the extend solenoid
	 *	int solenoidIndex2 - Index for the retract solenoid
	 */
	PneumaticPiston(int compressorIndex, int solenoidIndex1, int solenoidIndex2) {
		comp = new Compressor(compressorIndex);
		solExtend = new Solenoid(solenoidIndex1);
		solRetract = new Solenoid(solenoidIndex2)
	}

	/*
	 *	Destructor - Unload variables and stuff
	 */
	~PneumaticPiston() {
		delete comp;
		delete solExtend;
		delete solRetract;
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
