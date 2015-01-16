#include "_Team167Lib.h"

//-------------------------------------------------------------------------
// Simple Joystick Constructor.  
//    Needs to call ctor of base class (joystick)
//-------------------------------------------------------------------------
SimpleJoystick::SimpleJoystick(Joystick * my_joy):
	_joystick(my_joy),
  _lastButtonState(0),
  _currentButtonState(0),
  _toggledButtons(0)
{
	
}

//-------------------------------------------------------------------------
// Simple Joystick Destructor
//    clean up any resources that we allocated
//-------------------------------------------------------------------------
SimpleJoystick::~SimpleJoystick()
{
	delete _joystick;
}

//-------------------------------------------------------------------------
// Update Call
//    1) Sets the last button state to the current button state.
//    2) Finds the new current button state
//    3) Sets the proper toggles if toggles are set.
//
//   Notes:  This routine looks for rising edge (i.e. from 0 to 1), not
//      falling edge (1 to 0).
//
//   This uses bit masking to hold the button states:
//   	so we "or" a button to our current state.
// 		In binary the current state starts off by looking
// 		like: "0000 0000".  If buttons 1,2,3,4 the current state
// 		number would then look like "0000 1111" with the msb on the
// 		left.  If you looked at the button as a number it would be 15 b/c
//		2^0 + 2^1 + 2^2 + 2^3 or 8 + 4 + 2 + 1. We use the "or" operator '|'
//		because it is a really cheap operation for a processor to do whereas
//      the power function is a very expensive function for the processor.
//-------------------------------------------------------------------------
void SimpleJoystick::Update()
{
	// set the last button state
	_lastButtonState = _currentButtonState;
	
	// reset the current button state
	_currentButtonState = 0;
	
	// update the current button state
	for(uint16_t i = 1; i <= NumButtons; i++)
	{
		uint16_t tmp = 1;
		
		// shift the number by i places (each button has its own bit)
		uint16_t btn_num = tmp << i;
		
		bool pressed = _joystick->GetRawButton((uint32_t)i);
		
		// add it to our list
		if(pressed)
		{
			// add the button to the current list
			_currentButtonState = _currentButtonState | btn_num;

			uint16_t dif = _lastButtonState ^ _currentButtonState;
						
			if((dif & btn_num) != 0)
			{
				// it is a toggle, change its state (xor)
				_toggledButtons = (_toggledButtons ^ btn_num); 
			}
		}
	} // end of for loop
}

//-------------------------------------------------------------------------
// Pressed
//    Returns true is a button was pressed
//-------------------------------------------------------------------------
bool SimpleJoystick::Pressed(uint32_t button)
{
	if((_currentButtonState & button) > 0)
	{
		return true;
	}
	else
	{
		return false;
	}
}

//-------------------------------------------------------------------------
// Toggled
//    Returns true is a button was toggled
//-------------------------------------------------------------------------
bool SimpleJoystick::Toggled(uint32_t button)
{
	if((_toggledButtons & button) > 0)
	{
		return true;
	}
	else
	{
		return false;
	}
}

/*
 * Released
 * returns true if the button was just released
 */

bool SimpleJoystick::Released(uint32_t button)
{
	// first, ensure the button was previously pressed
	// then, check that it is now released
	return ((_lastButtonState & button) > 0) && ((_currentButtonState & button) == 0);
}

// toggle a button
void SimpleJoystick::EnableToggle(uint32_t button)
{
	_toggledButtons = _toggledButtons | button;
}

// untoggle a button
void SimpleJoystick::DisableToggle(uint32_t button)
{
	_toggledButtons = _toggledButtons & ~button;
}

void SimpleJoystick::DisableToggleAll()
{
	_toggledButtons = 0;
}
