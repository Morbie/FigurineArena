#pragma once

#ifndef GAMEPAD_H
#define GAMEPAD_H

#include <Xinput.h>
#include "Utility.h"

class Gamepad
{
public:
	// Constructors
	Gamepad();
	Gamepad(int a_iIndex);


	void Update();

	// Functions
	XINPUT_STATE GetState();
	int GetIndex();
	bool Connected();

private:
	// Member variables
	XINPUT_STATE m_State; // gamepad state
	int m_iGamepadIndex;  // Gamepad index



};

#endif // GAMEPAD_H