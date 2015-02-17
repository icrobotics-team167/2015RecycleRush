/*
 * PneumaticCylinder.cpp
 *
 *  Created on: Jan 15, 2015
 *      Author: phanta
 */

#include "PneumaticPiston.h"

PneumaticPiston::PneumaticPiston(int solenoidIndex1, int solenoidIndex2) {
        sol = new DoubleSolenoid(solenoidIndex1, solenoidIndex2);
}

/*
 *	Destructor - Unload variables and stuff
 */
PneumaticPiston::~PneumaticPiston()
{
        delete sol;
}

/*
 * 	Extend piston
 */
void PneumaticPiston::Extend()
{
        sol->Set(DoubleSolenoid::kReverse);
}

/*
 * 	Retract piston
 */
void PneumaticPiston::Retract()
{
        sol->Set(DoubleSolenoid::kForward);
}

/*
 * 	Force the piston to stop whatever it's doing (e.g. extending or retracting)
 */
void PneumaticPiston::ForceStop()
{
        sol->Set(DoubleSolenoid::kOff);
}
