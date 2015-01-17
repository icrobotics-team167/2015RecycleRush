/*
 * SwerveDrive.cpp
 *
 *  Created on: Jan 8, 2015
 *      Author: Kazimier
 */

#include "WPILib.h"

class SwerveDrive
{
private:
	unsigned rotateEncoderLines;
	unsigned driveEncoderLines;
	CANTalon *rotateTalon1;
	CANTalon *rotateTalon2;
	CANTalon *talon1;
	CANTalon *talon2;
	CANTalon *talon3;
	CANTalon *talon4;
	Gyro *gyro;

public:
	SwerveDrive(unsigned rotateEncLines, unsigned driveEncLines,
				unsigned short rotateTalon1Number,
				unsigned short rotateTalon2Number,
				unsigned short gyroChannel,
				int talon1Number,
				int talon2Number,
				int talon3Number,
				int talon4Number)
	{
		rotateEncoderLines = rotateEncLines;
		driveEncoderLines = driveEncLines;
		rotateTalon1 = new CANTalon(rotateTalon1Number);
		rotateTalon2 = new CANTalon(rotateTalon2Number);
		talon1 = new CANTalon(talon1Number);
		talon2 = new CANTalon(talon2Number);
		talon3 = new CANTalon(talon3Number);
		talon4 = new CANTalon(talon4Number);
		gyro = new Gyro(gyroChannel);
	}

	/*
	 * talon1--talon3
	 * |			|
	 * |			|
	 * talon2--talon4
	 */
	~SwerveDrive()
	{
		delete rotateTalon1;
		delete rotateTalon2;
		delete gyro;
		delete talon1;
		delete talon2;
		delete talon3;
		delete talon4;
	}

	/*
	 * angle: the direction relative to the field in which the
	 * robot should drive; field forward is 0/360 degrees
	 *
	 * speed: double ranging from -1.0 to 1.0 which represents the speed at
	 * which the wheels should be driven; -1.0 is full reverse, 1.0 is full forward
	 */
	void Drive(int angle, double speed)
	{
		if (angle == -1) {
			return;
		} // If they joystick is in neutral position, do nothing.

		// always rotate the wheels at maximum speed
		double rotateWheelSpeed = 1.0;
		//we assume that when (rotateWheelSpeed == 1.0) the wheels will
		//rotate in a counterclockwise direction

		int angleToBeTurned = 0;

		if (angle > GetWheelAngle())
			angleToBeTurned = (angle - GetWheelAngle()) % 360;
		else
			angleToBeTurned = (GetWheelAngle() - angle) % 360;

		if (abs(angleToBeTurned - angle) % 360 > 90)
		{
			if ((abs(angleToBeTurned - angle) % 360) > 270)
				//makes wheels rotate towards the original angle if they're closer to that
					rotateWheelSpeed *= -1;
			else	//if the wheels are closer to (180 + angle) than (angle), they turn to (180 + angle)
			{
				angleToBeTurned = -(180 - angleToBeTurned) % 360;
				//finds the opposite of the angle needed to be turned relative to the robot
				if (angleToBeTurned < 0)
				{
					angleToBeTurned *= -1;
					speed *= -1;
				}//makes sure wheels rotate the shortest distance
			}
		} //the if statement means the wheels won't have to turn over 90 degrees


		int distance = angleToBeTurned * rotateEncoderLines / 360;

		if (rotateTalon1->GetEncPosition() != distance % rotateEncoderLines)
		{
			rotateTalon1->Set(rotateWheelSpeed);
			rotateTalon2->Set(rotateWheelSpeed);
			talon1->Set(0);
			talon2->Set(0);
			talon3->Set(0);
			talon4->Set(0);
		}	//spins the motors until the wheels point in the right direction and stops drive motors
		else
		{
			rotateTalon1->Set(0);
			rotateTalon2->Set(0);
			talon1->Set(speed);
			talon2->Set(speed);
			talon3->Set(speed);
			talon4->Set(speed);
		}	//stops the motors when the wheels are pointing the right way
			//and tells the drive motors to spin

	}

	void RotateRobot(bool clockwise, double speed) { // Rotate the robot in a given direction by speed 'speed'
		if (clockwise) {
			talon1->Set(speed);
			talon2->Set(speed);
			talon3->Set(-speed);
			talon4->Set(-speed);
		}
		else {
			talon1->Set(-speed);
			talon2->Set(-speed);
			talon3->Set(speed);
			talon4->Set(speed);
		}
	}

	int GetWheelAngle()
	{
		float gyroangle = gyro->GetAngle();
		int robotRelativeWheelAngle = rotateTalon1->GetEncPosition() * 360 / rotateEncoderLines;
		int fieldRelativeWheelAngle = (gyroangle + robotRelativeWheelAngle) % 360;
		return fieldRelativeWheelAngle;
	}	//finds the angle the wheels are facing relative to the field
};
