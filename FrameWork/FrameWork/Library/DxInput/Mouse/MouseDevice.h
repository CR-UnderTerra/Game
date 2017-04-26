/**
 * @file   MouseDevice.h
 * @brief  MouseDeviceクラスのヘッダファイル
 * @author kotani
 */
#ifndef MOUSEDEVICE_H
#define MOUSEDEVICE_H
#include <dinput.h>	
#include "..\..\Singleton.h"

namespace Lib
{
	/**
	 * マウスのボタンの状態を表したenum
	 */
	enum MOUSEBUTTONSTATE
	{
		MOUSEBUTTON_PUSH,	//!< マウスのボタンが押された瞬間の状態
		MOUSEBUTTON_RELEASE,//!< マウスのボタンが離された瞬間の状態
		MOUSEBUTTON_ON,		//!< マウスのボタンが押され続けている状態
		MOUSEBUTTON_OFF		//!< マウスのボタンが離されている状態
	};

	/**
	 * マウスのボタンを表したenum
	 */
	enum MOUSEBUTTON
	{
		MOUSEBUTTON_LEFT,	 //!< マウスの左ボタン
		MOUSEBUTTON_RIGHT,	 //!< マウスの右ボタン
		MOUSEBUTTON_MIDDLE,	 //!< マウスの中央ボタン
		MOUSEBUTTON_UNKNOWN,	 //!< なにか分からない
		MOUSEBUTTON_MAX
	};

	/**
	 * マウスの状態を格納する構造体
	 */
	struct MOUSESTATE
	{
		LONG    lX;						//!< マウスのX方向の移動量
		LONG    lY;						//!< マウスのY方向の移動量
		LONG    lZ;						//!< マウスのZ方向の移動量
		MOUSEBUTTONSTATE rgbButtons[MOUSEBUTTON_MAX];	//!< マウスのボタンの状態
		POINT	CursorPos;				//!< ウィンドウ内のカーソル位置
	};

	class MouseDevice
	{
		friend Singleton<MouseDevice>;
	public:
		/**
		 * 初期化関数
		 * @param[in] _pDInput8 DirectInputオブジェクト
		 * @param[in] _hWnd KeyDeviceに対応させるウィンドウハンドル
		 * @return デバイスの初期化に成功したらtrueが返る
		 */
		bool Init(LPDIRECTINPUT8 _pDInput8, HWND _hWnd);

		/**
		 * 解放関数
		 */
		void Release();

		/**
		 * マウスの状態を更新する
		 */
		void Update();

		/**
		 * マウスの状態を取得する
		 * @return マウスの状態が格納されている構造体
		 */
		inline const MOUSESTATE& GetMouseState() const
		{
			return m_MouseState;
		}

	private:
		/**
		 * MouseDeviceクラスのコンストラクタ
		 */
		MouseDevice();

		/**
		 * MouseDeviceクラスのデストラクタ
		 */
		~MouseDevice(){};

		LPDIRECTINPUT8			m_pDInput8;
		HWND					m_hWnd;
		LPDIRECTINPUTDEVICE8	m_pDInputDevice8;
		MOUSESTATE				m_MouseState;
		DIMOUSESTATE			m_DIMouseState;
		DIMOUSESTATE			m_OldDIMouseState;

	};
}

#endif
