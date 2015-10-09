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

	//thumbstick functions
	bool LStick_InDeadzone();
	bool RStick_InDeadzone();

	float LeftStick_X();  // Return X axis of left stick
	float LeftStick_Y();  // Return Y axis of left stick
	float RightStick_X(); // Return X axis of right stick
	float RightStick_Y(); // Return Y axis of right stick

	//trigger functoins 
	float LeftTrigger();  
	float RightTrigger(); 

	// Rumble rumble
	void Rumble(float a_fLeftMotor = 0.0f, float a_fRightMotor = 0.0f);


private:
	// Member variables
	XINPUT_STATE m_State; // gamepad state
	int m_iGamepadIndex;  // Gamepad index



};

#endif // GAMEPAD_H