#ifndef SIMPLE_JOYSTICK_H
#define SIMPLE_JOYSTICK_H

class SimpleJoystick
{
public:
	SimpleJoystick(Joystick * my_joystick);
	~SimpleJoystick();
	
	void Update();
	bool Pressed(uint32_t button);
	bool Toggled(uint32_t button);
	bool Released(uint32_t button);
	
	void EnableToggle(uint32_t button);
	void DisableToggle(uint32_t button);
	
	// untoggles ALL buttons (Toggled will return false)
	void DisableToggleAll();
	
public:
	static const uint32_t NumButtons = 12;
	Joystick * _joystick;
	
	uint16_t _lastButtonState;	// state of the buttons before the last update
	uint16_t _currentButtonState;	// current state of the buttons since last update
	uint16_t _toggledButtons;		// Bit Masked list of buttons that are toggled.
};

#endif
