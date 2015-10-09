#include "Gamepad.h"

// Link the 'Xinput' library - Important!
#pragma comment(lib, "Xinput.lib")

// Default constructor
Gamepad::Gamepad() {}

// Overloaded constructor
Gamepad::Gamepad(int a_iIndex)
{
	// Set gamepad index
	m_iGamepadIndex = a_iIndex - 1;
}

XINPUT_STATE Gamepad::GetState()
{
	XINPUT_STATE GamepadState;
	ZeroMemory(&GamepadState, sizeof(XINPUT_STATE));

	XInputGetState(m_iGamepadIndex, &GamepadState);

	return GamepadState;
}

int Gamepad::GetIndex()
{
	return m_iGamepadIndex;
}

bool Gamepad::Connected()
{
	ZeroMemory(&m_State, sizeof(XINPUT_STATE));
	DWORD Result = XInputGetState(m_iGamepadIndex, &m_State);

	if (Result == ERROR_SUCCESS)
	{
		return true;
	}
	else
	{
		return false;
	}
}

void Gamepad::Update()
{
	m_State = GetState();
}

bool Gamepad::LStick_InDeadzone()
{
	// Obtain the X & Y axes of the stick
	short sX = m_State.Gamepad.sThumbLX;
	short sY = m_State.Gamepad.sThumbLY;

	// X axis is outside of deadzone
	if (sX > XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE ||
		sX < -XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE)
		return false;

	// Y axis is outside of deadzone
	if (sY > XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE ||
		sY < -XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE)
		return false;

	// One (or both axes) axis is inside of deadzone
	return true;
}

bool Gamepad::RStick_InDeadzone()
{
	// Obtain the X & Y axes of the stick
	short sX = m_State.Gamepad.sThumbRX;
	short sY = m_State.Gamepad.sThumbRY;

	// X axis is outside of deadzone
	if (sX > XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE ||
		sX < -XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE)
		return false;

	// Y axis is outside of deadzone
	if (sY > XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE ||
		sY < -XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE)
		return false;

	// One (or both axes) axis is inside of deadzone
	return true;
}


// Return X axis of left stick
float Gamepad::LeftStick_X()
{
	// Obtain X axis of left stick
	short sX = m_State.Gamepad.sThumbLX;

	// Return axis value, converted to a float
	return (static_cast<float>(sX) / 32768.0f);
}

// Return Y axis of left stick
float Gamepad::LeftStick_Y()
{
	// Obtain Y axis of left stick
	short sY = m_State.Gamepad.sThumbLY;

	// Return axis value, converted to a float
	return (static_cast<float>(sY) / 32768.0f);
}

// Return X axis of right stick
float Gamepad::RightStick_X()
{
	// Obtain X axis of right stick
	short sX = m_State.Gamepad.sThumbRX;

	// Return axis value, converted to a float
	return (static_cast<float>(sX) / 32768.0f);
}

// Return Y axis of right stick
float Gamepad::RightStick_Y()
{
	// Obtain the Y axis of the left stick
	short sY = m_State.Gamepad.sThumbRY;

	// Return axis value, converted to a float
	return (static_cast<float>(sY) / 32768.0f);
}

// Return value of left trigger
float Gamepad::LeftTrigger()
{
	// Obtain value of left trigger
	BYTE Trigger = m_State.Gamepad.bLeftTrigger;

	if (Trigger > XINPUT_GAMEPAD_TRIGGER_THRESHOLD)
		return Trigger / 255.0f;

	return 0.0f; // Trigger was not pressed
}

// Return value of right trigger
float Gamepad::RightTrigger()
{
	// Obtain value of right trigger
	BYTE Trigger = m_State.Gamepad.bRightTrigger;

	if (Trigger > XINPUT_GAMEPAD_TRIGGER_THRESHOLD)
		return Trigger / 255.0f;

	return 0.0f; // Trigger was not pressed
}

void Gamepad::Rumble(float a_fLeftMotor, float a_fRightMotor)
{
	// Vibration state
	XINPUT_VIBRATION VibrationState;

	// Zero memory
	ZeroMemory(&VibrationState, sizeof(XINPUT_VIBRATION));

	// Calculate vibration values
	int iLeftMotor = int(a_fLeftMotor * 65535.0f);
	int iRightMotor = int(a_fRightMotor * 65535.0f);

	// Set vibration values
	VibrationState.wLeftMotorSpeed = iLeftMotor;
	VibrationState.wRightMotorSpeed = iRightMotor;

	// Set the vibration state
	XInputSetState(m_iGamepadIndex, &VibrationState);
}