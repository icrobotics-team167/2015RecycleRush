/*
 * MechanumDrive.cpp
 *
 *  Created on: Jan 31, 2015
 *      Author: moon_gecko
 */
#include "_Team167Lib.h"
//-------------------------------------------------------------------------
//
//-------------------------------------------------------------------------
MechanumWheels::MechanumWheels(
Team167CanJaguar * front_left,
Team167CanJaguar * front_right,
Team167CanJaguar * back_left,
Team167CanJaguar * back_right,
UINT16 encoder_lines) :
FL_Pos(_cur_pos[0]),FR_Pos(_cur_pos[1]),
BL_Pos(_cur_pos[2]),BR_Pos(_cur_pos[3]),
FL_Tgt(_tgt_pos[0]),FR_Tgt(_tgt_pos[1]),
BL_Tgt(_tgt_pos[2]),BR_Tgt(_tgt_pos[3]),
CurrentTask(_currentTask),
_driveTimeout(0),_timeout(10),
_update_volts(true),_margin(3.5f),
_encoder_lines(encoder_lines)
{
Wheels[0] = front_left;
Wheels[1] = front_right;
Wheels[2] = back_left;
Wheels[3] = back_right;
_curVolts = 10.0f;
for(int i=0;i<4;i++)
{
_need_update[i] = false;
_tgt_pos[i] = 0.0f;
_cur_pos[i] = 0.0f;
}
_complete = true;
_currentTask = TaskFinished;
// 2011 robot
//_margin = 0.5f;
return;
}
//-------------------------------------------------------------------------
//
//-------------------------------------------------------------------------
MechanumWheels::~MechanumWheels()
{
// relase the pointers that we have
for(int i = 0;i < 4;i++)
Wheels[i] = NULL;
return;
}
//-------------------------------------------------------------------------
//
//-------------------------------------------------------------------------
double MechanumWheels::GetMaxVoltage()
{
return _curVolts;
}
//-------------------------------------------------------------------------
//
//-------------------------------------------------------------------------
void MechanumWheels::Disable()
{
for(int i = 0;i < 4;i++)
Wheels[i]->DisableControl();
return;
}
//-------------------------------------------------------------------------
//
//-------------------------------------------------------------------------
void MechanumWheels::Enable(bool use_waits)
{
Init(use_waits);
for(int i = 0;i < 4;i++)
{
if(use_waits) Wait(0.01);
Wheels[i]->EnableControl(0.0f);
}
_driveTimeout = 0;
return;
}
//-------------------------------------------------------------------------
//
//-------------------------------------------------------------------------
void MechanumWheels::FeedJags()
{
for(int i=0;i<4;i++)
{
if(Wheels[i])
{
Wheels[i]->Feed();
}
}
}
//-------------------------------------------------------------------------
// Checks to see if the current driving task is complete
// Sets the CurrentTask Flag to Finished if it complete
//-------------------------------------------------------------------------
void MechanumWheels::CheckComplete(float current_check)
{
// float current_pos[4]={0,0,0,0};
for(int i=0;i<4;i++)
{
_cur_pos[i] = Wheels[i]->GetPosition();
}
bool completed[4]={false,false,false,false};
for(int i=0;i<4;i++)
{
float val = _cur_pos[i] - _tgt_pos[i];
if(val < 0) val *= -1.0f;
if(val < 0.85)
completed[i] = true;
}
int complete_cnt = 0;
for(int i=0;i<4;i++)
{
if(completed[i])
complete_cnt++;
}
if(complete_cnt > 2)
{
_complete = true;
_currentTask = TaskFinished;
}
else
{
_complete = false;
}
int under_current_cnt = 0;
// Check to see if the wheels are being under powered.
for(int i=0;i<4;i++)
{
float cur = Wheels[i]->GetOutputCurrent();
// add 1 to under current check
if((cur < current_check) && !completed[i])
under_current_cnt++;
}
if(under_current_cnt == 0)
_driveTimeout = 0;
else
_driveTimeout++;
if(_driveTimeout > _timeout)
{
_complete = true;
_currentTask = TaskFinished;
}
}
//-------------------------------------------------------------------------
//
//-------------------------------------------------------------------------
void MechanumWheels::Init(bool use_waits)
{
for(int i = 0;i < 4;i++)
{
Wheels[i]->SetPositionReference(CANJaguar::kPosRef_QuadEncoder);
if(use_waits) Wait(0.01);
Wheels[i]->SetPID(50.0,0.0,0.0);
if(use_waits) Wait(0.01);
Wheels[i]->ConfigNeutralMode(CANJaguar::kNeutralMode_Brake);
if(use_waits) Wait(0.01);
Wheels[i]->ConfigEncoderCodesPerRev(_encoder_lines);
if(use_waits) Wait(0.01);
Wheels[i]->ConfigFaultTime(10.5f);
}
}
//-------------------------------------------------------------------------
// SetMaxVoltage
// Updates the Max voltage. If updated value is same as the current value
// the function just returns.
//-------------------------------------------------------------------------
void MechanumWheels::SetMaxVoltage(double Volt)
{
float testval = Volt - _curVolts;
if(testval < 0) testval *= -1.0f;
// return if the value is only different by a half volt
if(testval < 0.5f)
return;
if(Volt > _maxVolts) Volt = _maxVolts;
if(Volt < _minVolts) Volt = _minVolts;
_curVolts = Volt;
_update_volts = true;
return;
}
//-------------------------------------------------------------------------
// Stop
// Stops the wheels
//-------------------------------------------------------------------------
void MechanumWheels::StopJags()
{
Update(Stop);
}
//-------------------------------------------------------------------------
//
//-------------------------------------------------------------------------
void MechanumWheels::Move2Loc(DriveDir dir, float dist)
{
_currentTask = dir;
bool stop = false;
_driveTimeout = 0;
// float current_pos[4]={0,0,0,0};
for(int i=0;i<4;i++)
{
_cur_pos[i] = Wheels[i]->GetPosition();
}
// Drive some Wheels!
if(dir == Stop)
{
stop = true;
}
else if(dir == Forward)
{
// forward
for(int i=0;i<4;i++)
{
_tgt_pos[i]= _cur_pos[i]+dist;
_need_update[i] = true;
}
}
else if(dir == Reverse)
{
// reverse
for(int i=0;i<4;i++)
{
_tgt_pos[i]=_cur_pos[i]+ -dist;
_need_update[i] = true;
}
}
else if(dir == Right)
{
// right
for(int i=0;i<4;i++)
{
if(i == FL_JAG || i == BR_JAG)
{
_tgt_pos[i]= _cur_pos[i]+dist;
_need_update[i] = true;
}
else if(i == FR_JAG || i == BL_JAG)
{
_tgt_pos[i]=_cur_pos[i]+ -dist;
_need_update[i] = true;
}
}
}
else if(dir == Left)
{
// left
for(int i=0;i<4;i++)
{
if(i == FR_JAG || i == BL_JAG)
{
_tgt_pos[i]=_cur_pos[i]+dist;
_need_update[i] = true;
}
else if(i == FL_JAG || i == BR_JAG)
{
_tgt_pos[i]=_cur_pos[i]+ -dist;
_need_update[i] = true;
}
}
}
else if(dir == RotateLeft)
{
// rotate left
//put this in to fix stuff
for(int i=0;i<4;i++)
{
if(i == FL_JAG || i == BL_JAG)
{
_tgt_pos[i]=_cur_pos[i]+ -dist;
_need_update[i] = true;
}
else if(i == FR_JAG || i == BR_JAG)
{
_tgt_pos[i]=_cur_pos[i]+ dist;
_need_update[i] = true;
}
}
}
else if(dir == RotateRight)
{
// rotate right
//put this in to fix stuff
for(int i=0;i<4;i++)
{
if(i == FR_JAG || i == BR_JAG)
{
_tgt_pos[i]=_cur_pos[i]+ -dist;
_need_update[i] = true;
}
else if(i == FL_JAG || i == BL_JAG)
{
_tgt_pos[i]=_cur_pos[i]+ dist;
_need_update[i] = true;
}
}
}
else if(dir == BackRight)
{
// back right
for(int i=0;i<4;i++)
{
if(i == FR_JAG || i == BL_JAG)
{
_tgt_pos[i]=_cur_pos[i]+ - dist;
_need_update[i] = true;
}
}
}
else if(dir == BackLeft)
{
// back left
for(int i=0;i<4;i++)
{
if(i == FL_JAG || i == BR_JAG)
{
_tgt_pos[i]=_cur_pos[i]+ -dist;
_need_update[i] = true;
}
}
}
else if(dir == FwdLeft)
{
// front left
for(int i=0;i<4;i++)
{
if(i == FR_JAG || i == BL_JAG)
{
_tgt_pos[i]=_cur_pos[i]+dist;
_need_update[i] = true;
}
}
}
else if(dir == FwdRight)
{
// front right
for(int i=0;i<4;i++)
{
if(i == FL_JAG || i == BR_JAG)
{
_tgt_pos[i]=_cur_pos[i]+dist;
_need_update[i] = true;
}
}
}
// stop
if(stop)
{
for(int i = 0;i < 4;i++)
{
_tgt_pos[i] = _cur_pos[i];
if(Wheels[i]->GetPosition() == _tgt_pos[i])
continue;
else
_need_update[i] = true;
}
}
//---------------------------------------------------------------------
// Set the voltage
//---------------------------------------------------------------------
if(_update_volts)
{
for(int i = 0;i < 4;i++)
{
Wheels[i]->ConfigMaxOutputVoltage(_curVolts);
}
_update_volts = false;
}
//---------------------------------------------------------------------
// update the jaguars (if needed)
//---------------------------------------------------------------------
// actually set the jags
for(int i=0;i<4;i++)
{
if(_need_update[i])
{
Wheels[i]->Set(_tgt_pos[i]);
_need_update[i] = false;
}
}
}
//-------------------------------------------------------------------------
// Update
// Updates the wheels based on the drive direction given.
// Will only send updates to the jaguars when needed, no matter how many
// times you call update.
//-------------------------------------------------------------------------
void MechanumWheels::Update(DriveDir dir)
{
_currentTask = ManualDrive;
_driveTimeout = 0;
bool stop = false;
// float current_pos[4]={0,0,0,0};
for(int i=0;i<4;i++)
{
_cur_pos[i] = Wheels[i]->GetPosition();
}
// Drive some Wheels!
if(dir == Stop)
{
stop = true;
}
else if(dir == Forward)
{
// forward
for(int i=0;i<4;i++)
{
if(_cur_pos[i] > (_tgt_pos[i] - _margin))
{
_tgt_pos[i]=_cur_pos[i] + _margin*5.0f;
_need_update[i] = true;
}
}
}
else if(dir == Reverse)
{
// reverse
for(int i=0;i<4;i++)
{
if(_cur_pos[i] < (_tgt_pos[i] + _margin))
{
_tgt_pos[i]=_cur_pos[i] - _margin*5.0f;
_need_update[i] = true;
}
}
}
else if(dir == Right)
{
// right
for(int i=0;i<4;i++)
{
if(i == FL_JAG || i == BR_JAG)
{
if(_cur_pos[i] > (_tgt_pos[i] - _margin))
{
_tgt_pos[i]=_cur_pos[i] + _margin*5.0f;
_need_update[i] = true;
}
}
else if(i == FR_JAG || i == BL_JAG)
{
if(_cur_pos[i] < (_tgt_pos[i] + _margin))
{
_tgt_pos[i]=_cur_pos[i] - _margin*5.0f;
_need_update[i] = true;
}
}
}
}
else if(dir == Left)
{
// left
for(int i=0;i<4;i++)
{
if(i == FR_JAG || i == BL_JAG)
{
if(_cur_pos[i] > (_tgt_pos[i] - _margin))
{
_tgt_pos[i]=_cur_pos[i] + _margin*5.0f;
_need_update[i] = true;
}
}
else if(i == FL_JAG || i == BR_JAG)
{
if(_cur_pos[i] < (_tgt_pos[i] + _margin))
{
_tgt_pos[i]=_cur_pos[i] - _margin*5.0f;
_need_update[i] = true;
}
}
}
}
else if(dir == RotateLeft)
{
// rotate left
for(int i=0;i<4;i++)
{
if(i == FL_JAG || i == BL_JAG)
{
if(_cur_pos[i] < (_tgt_pos[i] + _margin))
{
_tgt_pos[i]=_cur_pos[i] - _margin*5.0f;
_need_update[i] = true;
}
}
else if(i == FR_JAG || i == BR_JAG)
{
if(_cur_pos[i] > (_tgt_pos[i] - _margin))
{
_tgt_pos[i]=_cur_pos[i] + _margin*5.0f;
_need_update[i] = true;
}
}
}
}
else if(dir == RotateRight)
{
// rotate right
for(int i=0;i<4;i++)
{
if(i == FR_JAG || i == BR_JAG)
{
if(_cur_pos[i] < (_tgt_pos[i] + _margin))
{
_tgt_pos[i]=_cur_pos[i] - _margin*5.0f;
_need_update[i] = true;
}
}
else if(i == FL_JAG || i == BL_JAG)
{
if(_cur_pos[i] > (_tgt_pos[i] - _margin))
{
_tgt_pos[i]=_cur_pos[i] + _margin*5.0f;
_need_update[i] = true;
}
}
}
}
else if(dir == BackRight)
{
// back right
for(int i=0;i<4;i++)
{
if(i == FR_JAG || i == BL_JAG)
{
if(_cur_pos[i] < (_tgt_pos[i] + _margin))
{
_tgt_pos[i]=_cur_pos[i] - _margin*5.0f;
_need_update[i] = true;
}
}
}
}
else if(dir == BackLeft)
{
// back left
for(int i=0;i<4;i++)
{
if(i == FL_JAG || i == BR_JAG)
{
if(_cur_pos[i] < (_tgt_pos[i] + _margin))
{
_tgt_pos[i]=_cur_pos[i] - _margin*5.0f;
_need_update[i] = true;
}
}
}
}
else if(dir == FwdLeft)
{
// front left
for(int i=0;i<4;i++)
{
if(i == FR_JAG || i == BL_JAG)
{
if(_cur_pos[i] > (_tgt_pos[i] - _margin))
{
_tgt_pos[i]=_cur_pos[i] + _margin*5.0f;
_need_update[i] = true;
}
}
}
}
else if(dir == FwdRight)
{
// front right
for(int i=0;i<4;i++)
{
if(i == FL_JAG || i == BR_JAG)
{
if(_cur_pos[i] > (_tgt_pos[i] - _margin))
{
_tgt_pos[i]=_cur_pos[i] + _margin*5.0f;
_need_update[i] = true;
}
}
}
}
// stop
if(stop)
{
for(int i = 0;i < 4;i++)
{
this->_tgt_pos[i] = _cur_pos[i];
if(Wheels[i]->GetPosition() == _tgt_pos[i])
continue;
else
_need_update[i] = true;
}
}
//---------------------------------------------------------------------
// Set the voltage
//---------------------------------------------------------------------
if(_update_volts)
{
for(int i = 0;i < 4;i++)
{
Wheels[i]->ConfigMaxOutputVoltage(_curVolts);
}
_update_volts = false;
}
//---------------------------------------------------------------------
// update the jaguars (if needed)
//---------------------------------------------------------------------
// actually set the jags
for(int i=0;i<4;i++)
{
if(_need_update[i])
{
Wheels[i]->Set(_tgt_pos[i]);
_need_update[i] = false;
}
}
}
void MechanumWheels::SetPID(int wheel_index, float p, float i, float d)
{
Wheels[wheel_index]->SetPID(p, i, d);
return;
}



