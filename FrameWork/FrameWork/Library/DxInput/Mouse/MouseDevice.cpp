﻿/**
 * @file   MouseDevice.cpp
 * @brief  MouseDeviceクラスの実装
 * @author kotani
 */
#include "MouseDevice.h"


Lib::MouseDevice::MouseDevice() :
m_pDInput8(NULL),
m_hWnd(NULL),
m_pDInputDevice8(NULL)
{
	for (int i = 0; i < 4; i++)
	{
		m_DIMouseState.rgbButtons[i] = 0;
		m_OldDIMouseState.rgbButtons[i] = 0;
	}
}


//----------------------------------------------------------------------------------------------------
// Public Functions
//----------------------------------------------------------------------------------------------------

bool Lib::MouseDevice::Init(LPDIRECTINPUT8 _pDInput8, HWND _hWnd)
{
	if (m_pDInput8 != NULL)
	{
		MessageBox(_hWnd, TEXT("MouseDeviceクラスは既に初期化されています"), TEXT("エラー"), MB_ICONSTOP);
		return false;
	}

	m_pDInput8 = _pDInput8;
	m_hWnd = _hWnd;

	if (m_pDInput8 == NULL)
	{
		MessageBox(m_hWnd, TEXT("DirectInput8オブジェクトが有効ではありません"), TEXT("エラー"), MB_ICONSTOP);
		return false;
	}

	if (FAILED(m_pDInput8->CreateDevice(GUID_SysMouse, &m_pDInputDevice8, NULL)))
	{
		MessageBox(m_hWnd, TEXT("DirectInput8マウスデバイスの生成に失敗しました"), TEXT("エラー"), MB_ICONSTOP);
		return false;
	}

	if (FAILED(m_pDInputDevice8->SetDataFormat(&c_dfDIMouse)))
	{
		MessageBox(m_hWnd, TEXT("DirectInput8マウスデバイスのデータフォーマットの設定に失敗しました"), TEXT("エラー"), MB_ICONSTOP);
		m_pDInputDevice8->Release();
		return false;
	}

	DIPROPDWORD DiProp;
	DiProp.diph.dwSize = sizeof(DiProp);
	DiProp.diph.dwHeaderSize = sizeof(DiProp.diph);
	DiProp.diph.dwObj = 0;
	DiProp.diph.dwHow = DIPH_DEVICE;
	DiProp.dwData = 1000;
	if (FAILED(m_pDInputDevice8->SetProperty(DIPROP_BUFFERSIZE, &DiProp.diph)))
	{
		MessageBox(m_hWnd, TEXT("DirectInput8マウスデバイスのバッファ設定に失敗しました"), TEXT("エラー"), MB_ICONSTOP);
		m_pDInputDevice8->Release();
		return false;
	}

	if (FAILED(m_pDInputDevice8->SetCooperativeLevel(m_hWnd, DISCL_NONEXCLUSIVE | DISCL_FOREGROUND)))
	{
		MessageBox(m_hWnd, TEXT("DirectInput8マウスデバイスの協調レベルの設定に失敗しました"), TEXT("エラー"), MB_ICONSTOP);
		m_pDInputDevice8->Release();
		return false;
	}

	m_pDInputDevice8->Acquire();

	OutputDebugString(TEXT("DirectInputのMouseDeviceの初期化に成功した\n"));

	return true;
}

void Lib::MouseDevice::Release()
{
	if (m_pDInputDevice8 != NULL)
	{
		m_pDInputDevice8->Release();
		m_pDInputDevice8 = NULL;
		m_pDInput8 = NULL;
	}
}

void Lib::MouseDevice::Update()
{
	HRESULT hr = m_pDInputDevice8->Acquire();
	if ((hr == DI_OK) || (hr == S_FALSE))
	{
		m_pDInputDevice8->GetDeviceState(sizeof(m_DIMouseState), &m_DIMouseState);
	}

	m_MouseState.lX = m_DIMouseState.lX;
	m_MouseState.lY = m_DIMouseState.lY;
	m_MouseState.lZ = m_DIMouseState.lZ;
	GetCursorPos(&m_MouseState.CursorPos);

	RECT WindowRect;
	RECT ClientRect;
	int TitleBarSize = GetSystemMetrics(SM_CYCAPTION);
	GetWindowRect(m_hWnd, &WindowRect);
	GetClientRect(m_hWnd, &ClientRect);
	m_MouseState.CursorPos.x -= WindowRect.left;
	m_MouseState.CursorPos.y -= WindowRect.top;

	m_MouseState.CursorPos.x -= (WindowRect.right - WindowRect.left - ClientRect.right - ClientRect.left) / 2;
	m_MouseState.CursorPos.y -= (WindowRect.bottom - WindowRect.top - ClientRect.bottom + TitleBarSize - ClientRect.top) / 2;

	for (int i = 0; i < MOUSEBUTTON_MAX; i++)
	{
		if (m_DIMouseState.rgbButtons[i])
		{
			if (m_OldDIMouseState.rgbButtons[i])
			{
				m_MouseState.rgbButtons[i] = MOUSEBUTTON_ON;
			}
			else
			{
				m_MouseState.rgbButtons[i] = MOUSEBUTTON_PUSH;
			}
			m_OldDIMouseState.rgbButtons[i] = m_DIMouseState.rgbButtons[i];
		}
		else
		{
			if (m_OldDIMouseState.rgbButtons[i])
			{
				m_MouseState.rgbButtons[i] = MOUSEBUTTON_RELEASE;
			}
			else
			{
				m_MouseState.rgbButtons[i] = MOUSEBUTTON_OFF;
			}
			m_OldDIMouseState.rgbButtons[i] = m_DIMouseState.rgbButtons[i];
		}
	}
}
