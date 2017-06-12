/**
* @file   XInput.h
* @brief  XInputクラスのヘッダファイル
* @author kotani
*/
#ifndef XINPUT_H
#define XINPUT_H

#include <windows.h>
#include <mmsystem.h>
#include <XInput.h>
#include "../Singleton.h"

namespace Lib
{
	struct CONTROLER_STATE
	{
		XINPUT_STATE		State;
		XINPUT_VIBRATION	Vib_State;
	};

	enum XINPUT_ID
	{
		GAMEPAD_ANALOG_UP,
		GAMEPAD_ANALOG_DOWN,
		GAMEPAD_ANALOG_LEFT,
		GAMEPAD_ANALOG_RIGHT,
		GAMEPAD_START,
		GAMEPAD_BACK,
		GAMEANALOG_LEFT_THUMB,
		GAMEANALOG_RIGHT_THUMB,
		GAMEANALOG_LEFT_SHOULDER,
		GAMEANALOG_RIGHT_SHOULDER,
		GAMEPAD_A,
		GAMEPAD_B,
		GAMEPAD_X,
		GAMEPAD_Y,
		XINPUT_IDMAX
	};

	enum XINPUTPAD
	{
		GAMEPAD1,
		GAMEPAD2,
		GAMEPAD3,
		GAMEPAD4,
		GAMEANALOG_MAX
	};

	enum PADSTATE
	{
		PAD_PUSH,
		PAD_RELEASE,
		PAD_ON,
		PAD_OFF
	};

	class XInput
	{
		friend Lib::Singleton<XInput>;
	public:
		/**
		* GamePadの状態チェック関数
		* @param[in] _pad チェックするGamePad
		*/
		void Update(XINPUTPAD _pad);

		/**
		* 指定のボタンの状態を更新する
		* @param[in] _pad チェックするGamePad
		* @param[in] _buttonId チェックするボタン
		* @param[in] _xinputButton 更新するXINPUT_GAMEPADのボタン
		*/
		void CheckButton(XINPUTPAD _pad, XINPUT_ID _buttonId, WORD _xinputButton);

		void CheckAnalogPad(XINPUTPAD _pad, XINPUT_ID _buttonId);

		/**
		* GamePadのボタンの状態を取得する
		* @param[in] id チェックするボタン
		* @param[in] pad チェックするGamePad
		*/
		PADSTATE GetButtonState(XINPUT_ID _buttonId, XINPUTPAD _pad);

	private:
		/**
		* コンストラクタ
		*/
		XInput();

		/**
		* デストラクタ
		*/
		~XInput() = default;

		CONTROLER_STATE m_PadControlState[GAMEANALOG_MAX];
		PADSTATE m_PadOldState[GAMEANALOG_MAX][XINPUT_IDMAX];
		PADSTATE m_PadState[GAMEANALOG_MAX][XINPUT_IDMAX];
	};
}


#endif