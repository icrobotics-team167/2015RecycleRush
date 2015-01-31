/*
 * MechanumDrive.h
 *
 *  Created on: Jan 31, 2015
 *      Author: moon_gecko
 */
#ifndef MECHANUMWHEELS_H
#define MECHANUMWHEELS_H
class MechanumWheels
{
public:
// Directions that the robot is capable of moving to
typedef enum {Stop=0, Forward=1,Reverse=2,
Right=3,Left=4,RotateLeft=5, RotateRight=6,
BackRight=7,BackLeft=8,FwdLeft=9,FwdRight=10,
ManualDrive=11,TaskFinished=12} DriveDir;
MechanumWheels
{
private:
	Team167CanJaguar * front_left,
	Team167CanJaguar * front_right,
	Team167CanJaguar * back_left,
	Team167CanJaguar * back_right,
	UINT16 encoder_lines = 250);
public:
	MechanumDrive();

~MechanumWheels();

// gets the output voltage
double GetMaxVoltage();
// disables the drive
void Disable();
// enables the drive
void Enable(bool use_waits = false);
// inits the jaguars
void Init(bool use_waits = false);
// Sets the max voltage of the jaguars
void SetMaxVoltage(double Volt);
// Feeds the jaguars watchdogs
void FeedJags();
// Manual driving update
void Update(DriveDir dir);
// Moves the robot to a distance from its current location
void Move2Loc(DriveDir dir, float dist);
// Stops the Jaguars
void StopJags();
// gets the position of a particular wheel
float GetPos(int i){return Wheels[i%4]->GetPosition();};
// returns true if the task is complete
void CheckComplete(float current_check = 0.5);
//Sets PID for individual wheels
void SetPID(int wheel_index, float p, float i, float d);
public:
// positions of the wheel encoders (Read only)
const float & FL_Pos; // Position of the Front Left encoder
const float & FR_Pos; // Position of the Front Right encoder
const float & BL_Pos; // Poisition of the Back Left encoder
const float & BR_Pos; // Position of the Back Right encoder
const float & FL_Tgt; // Position of the Front Left encoder
const float & FR_Tgt; // Position of the Front Right encoder
const float & BL_Tgt; // Poisition of the Back Left encoder
const float & BR_Tgt; // Position of the Back Right encoder
// Current task of the drivetrain (read only)
const DriveDir & CurrentTask;
protected:
Team167CanJaguar * Wheels[4]; // Pointers to jaguar controllers
DriveDir _lastmode; // last set drive direction
DriveDir _currentTask; // the drive trains current task
int	_driveTimeout; // counter to check for under powered wheels
int	_timeout; // number of loops until timeout occurs
private:
double _curVolts; // Max voltage for the jaguars
static const float _minVolts = 2.0;
static const float _maxVolts = 12.0;
bool	_need_update[4]; // flags to determine if jaguars need to be updated
bool	_update_volts; // flag to update volts
float	_tgt_pos[4]; // target encoder positions
float	_cur_pos[4]; // current encoder positions
float	_margin; // margin to add to the set distance
UINT16 _encoder_lines; // number of lines for the encoder
bool	_complete;
};
#endif



