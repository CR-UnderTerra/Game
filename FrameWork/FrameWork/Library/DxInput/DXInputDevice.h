/**
 * @file   DXInputDevice.h
 * @brief  DXInputDeviceクラスのヘッダファイル
 * @author kotani
 */
#ifndef DXINPUTDEVICE_H
#define DXINPUTDEVICE_H
#include "Mouse/MouseDevice.h"
#include "KeyBoard/KeyDevice.h"
#include "..\Singleton.h"

namespace Lib
{
	class DXInputDevice
	{
		friend Singleton<DXInputDevice>;
	public:
		/**
		 * 初期化処理
		 */
		bool Init(HWND _hWnd);

		/**
		 * 開放処理
		 */
		void Release();

		inline LPDIRECTINPUT8 GetInputDevice()
		{
			return m_pDInput8;
		}

		///**
		//* KeyDeviceの状態を更新する
		//*/
		//void KeyUpdate();

		///**
		//* MouseDeviceの状態を更新する
		//*/
		//void MouseUpdate();

		///**
		//* キーの状態を更新する
		//* @param[in] 更新したいキーのDIK
		//*/
		//void KeyCheck(int _dik);

		///**
		//* キーの状態が格納されている配列を取得する
		//* @return キーの状態が格納されている配列
		//*/
		//const Lib::KEYSTATE* GetKeyState() const;

		///**
		//* マウスの状態を取得する
		//* @return マウスの状態が格納されている構造体
		//*/
		//const Lib::MOUSESTATE GetMouseState() const;

	private:
		DXInputDevice() :
			m_pDInput8(NULL),
			m_hWnd(NULL){};

		~DXInputDevice(){};

		LPDIRECTINPUT8	m_pDInput8;
		HWND			m_hWnd;

	};
}


#endif
