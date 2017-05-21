/**
 * @file   XInput.cpp
 * @brief  XInputクラスの実装
 * @author kotani
 */
#include "XInput.h"
#define CONDEADZONE 65535/4 //コントローラーのデッドゾーン
#define NO_SIGNAL 0x0000


Lib::XInput::XInput()
{
	for (int count = 0; count < GAMEANALOG_MAX; count++)
	{
		for (int i = 0; i < XINPUT_IDMAX; i++)
		{
			m_PadOldState[count][i] = PAD_OFF;
			m_PadState[count][i] = PAD_OFF;
		}
	}
}


//----------------------------------------------------------------------------------------------------
// Public Functions
//----------------------------------------------------------------------------------------------------

void Lib::XInput::Update(XINPUTPAD _pad)
{
	XINPUT_CAPABILITIES xInputCapabilities; 
	if (XInputGetCapabilities(0, 0, &xInputCapabilities) == ERROR_DEVICE_NOT_CONNECTED) return;
	XInputGetState(_pad, &m_PadControlState[_pad].State);
}

void Lib::XInput::CheckButton(XINPUTPAD _pad, XINPUT_ID _buttonId, WORD _xinputButton)
{
	XINPUT_CAPABILITIES xInputCapabilities;
	if (XInputGetCapabilities(0, 0, &xInputCapabilities) == ERROR_DEVICE_NOT_CONNECTED) return;
	if (m_PadControlState[_pad].State.Gamepad.wButtons & _xinputButton)
	{
		if (m_PadOldState[_pad][_buttonId] == PAD_ON)
		{
			m_PadState[_pad][_buttonId] = PAD_ON;
		}
		else
		{
			m_PadState[_pad][_buttonId] = PAD_PUSH;
		}
		m_PadOldState[_pad][_buttonId] = PAD_ON;
	}
	else
	{
		//前も入力されてたら
		if (m_PadOldState[_pad][_buttonId] == PAD_ON)
		{
			m_PadState[_pad][_buttonId] = PAD_RELEASE;
		}
		else
		{
			m_PadState[_pad][_buttonId] = PAD_OFF;
		}
		m_PadOldState[_pad][_buttonId] = PAD_OFF;
	}
}

Lib::PADSTATE Lib::XInput::GetButtonState(XINPUT_ID _buttonId, XINPUTPAD _pad)
{
	return m_PadState[_pad][_buttonId];
}

bool Lib::XInput::GetAnalogState(ANALOGPAD _analogId, XINPUTPAD _pad)
{
	switch (_analogId)
	{
	case ANALOG_LEFT:
		if (m_PadControlState[_pad].State.Gamepad.sThumbLX < -CONDEADZONE)
		{
			return true;
		}
		break;
	case ANALOG_RIGHT:
		if (m_PadControlState[_pad].State.Gamepad.sThumbLX > CONDEADZONE)
		{
			return true;
		}
		break;
	case ANALOG_UP:
		if (m_PadControlState[_pad].State.Gamepad.sThumbLY > CONDEADZONE)
		{
			return true;
		}
		break;
	case ANALOG_DOWN:
		if (m_PadControlState[_pad].State.Gamepad.sThumbLY < -CONDEADZONE)
		{
			return true;
		}
		break;
	}

	return false;
}
