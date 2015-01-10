#ifndef SIMPLE_JOYSTICK_H
#define SIMPLE_JOYSTICK_H

class SimpleJoystick
{
public:
	SimpleJoystick(Joystick * my_joystick);
	~SimpleJoystick();
	
	void Update();
	bool Pressed(UINT32 button);
	bool Toggled(UINT32 button);
	bool Released(UINT32 button);
	
	void EnableToggle(UINT32 button);
	void DisableToggle(UINT32 button);
	
	// untoggles ALL buttons (Toggled will return false)
	void DisableToggleAll();
	
public:
	static const UINT32 NumButtons = 12;
	Joystick * _joystick;
	
	UINT16 _lastButtonState;	// state of the buttons before the last update
	UINT16 _currentButtonState;	// current state of the buttons since last update
	UINT16 _toggledButtons;		// Bit Masked list of buttons that are toggled.
};

#endif
