/*
 * PneumaticPiston.h
 *
 *  Created on: Jan 23, 2015
 *      Author: Kazimier
 */

#ifndef SRC_TEAM167LIB_PNEUMATICPISTON_H_
#define SRC_TEAM167LIB_PNEUMATICPISTON_H_

#include "WPILib.h"

class PneumaticPiston
{
private:
	Compressor *comp;
	DoubleSolenoid *sol;

public:
	PneumaticPiston(int compressorIndex, int solenoidIndex1, int solenoidIndex2);
	~PneumaticPiston();

	void Extend();
	void Retract();
	void ForceStop();
};


#endif /* SRC_TEAM167LIB_PNEUMATICPISTON_H_ */
