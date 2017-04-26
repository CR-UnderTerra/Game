/**
 * @file   KeyDevice.h
 * @brief  KeyDeviceクラスのヘッダファイル
 * @author kotani
 */
#ifndef KEYDEVICE_H
#define KEYDEVICE_H
#include <dinput.h>	
#include "..\..\Singleton.h"

namespace Lib
{
	/**
	 * キーの状態を表したenum
	 */
	enum KEYSTATE
	{
		KEY_PUSH,	//!< キーが押された瞬間の状態
		KEY_RELEASE,//!< キーが離された瞬間の状態
		KEY_ON,		//!< キーが押され続けている状態
		KEY_OFF		//!< キーが押されていない状態
	};

	class KeyDevice
	{
		friend Singleton<KeyDevice>;
	public:
		/**
		 * KeyDeviceの初期化関数
		 * @param[in] _pDInput8 DirectInputオブジェクト
		 * @param[in] _hWnd KeyDeviceに対応させるウィンドウハンドル
		 * @return デバイスの初期化に成功したらtrueが返る
		 */
		bool Init(LPDIRECTINPUT8 _pDInput8, HWND _hWnd);

		/**
		 * KeyDeviceの解放関数
		 */
		void Release();

		/**
		 * KeyDeviceの状態を更新する
		 */
		void Update();

		/**
		 * キーの状態を更新する
		 * @param[in] 更新したいキーのDIK
		 */
		void KeyCheck(int _dik);

		/**
		 * キーの状態が格納されている配列を取得する
		 * @return キーの状態が格納されている配列
		 */
		const KEYSTATE* GetKeyState() const;

	private:
		/**
		 * KeyDeviceクラスのコンストラクタ
		 */
		KeyDevice();

		/**
		 * KeyDeviceクラスのデストラクタ
		 */
		~KeyDevice(){};

		LPDIRECTINPUT8			m_pDInput8;
		HWND					m_hWnd;
		LPDIRECTINPUTDEVICE8	m_pDInputDevice8;
		KEYSTATE				m_pKeyState[256];
		BYTE					m_pDIKeyState[256];
		BYTE					m_pOldDIKeyState[256];

	};
}


#endif
