/**
 * @file   LeftHand.cpp
 * @brief  LeftHandクラスの実装
 * @author kotani
 */
#include "LeftHand.h"
#include "DxInput/KeyBoard/KeyDevice.h"
#include "Window/Window.h"


LeftHand::LeftHand(int _textureIndex) :
HandBase(&D3DXVECTOR2(0, 0), "h_left", _textureIndex)
{
	RECT ClientRect;
	GetClientRect(SINGLETON_INSTANCE(Lib::Window).GetWindowHandle(), &ClientRect);

	m_Pos.x = static_cast<float>(ClientRect.right / 2 - 300);
	m_Pos.y = static_cast<float>(ClientRect.bottom / 2 + 200);

}

LeftHand::~LeftHand()
{
}


//----------------------------------------------------------------------------------------------------
// Public Functions
//----------------------------------------------------------------------------------------------------

void LeftHand::Update()
{
	RECT ClientRect;
	GetClientRect(SINGLETON_INSTANCE(Lib::Window).GetWindowHandle(), &ClientRect);

	if (SINGLETON_INSTANCE(Lib::KeyDevice).GetKeyState()[DIK_Z] == Lib::KEY_PUSH ||
		SINGLETON_INSTANCE(Lib::KeyDevice).GetKeyState()[DIK_X] == Lib::KEY_PUSH ||
		SINGLETON_INSTANCE(Lib::KeyDevice).GetKeyState()[DIK_C] == Lib::KEY_PUSH ||
		SINGLETON_INSTANCE(Lib::KeyDevice).GetKeyState()[DIK_Z] == Lib::KEY_RELEASE ||
		SINGLETON_INSTANCE(Lib::KeyDevice).GetKeyState()[DIK_X] == Lib::KEY_RELEASE ||
		SINGLETON_INSTANCE(Lib::KeyDevice).GetKeyState()[DIK_C] == Lib::KEY_RELEASE)
	{
		m_MoveSpeed = 1;
	}
	else if (SINGLETON_INSTANCE(Lib::KeyDevice).GetKeyState()[DIK_Z] == Lib::KEY_ON ||
		SINGLETON_INSTANCE(Lib::KeyDevice).GetKeyState()[DIK_X] == Lib::KEY_ON ||
		SINGLETON_INSTANCE(Lib::KeyDevice).GetKeyState()[DIK_C] == Lib::KEY_ON)
	{
		if (m_Pos.x < ClientRect.right / 2 - m_Rect.x / 2)
		{
			m_Pos.x += m_MoveSpeed;
			m_MoveSpeed += m_Acceleration;
		}
		else
		{
			m_Pos.x = ClientRect.right / 2 - m_Rect.x / 2;
		}
	}
	else
	{
		if (m_Pos.x > ClientRect.right / 2 - 300)
		{
			m_Pos.x -= m_MoveSpeed;
			m_MoveSpeed += m_Acceleration;
		}
		else if (m_Pos.x < ClientRect.right / 2 - 300)
		{
			m_Pos.x = ClientRect.right / 2 - 300;
		}
	}
}

void LeftHand::Draw()
{
	m_pVertex->Draw(&m_Pos,m_pAnimUvController->GetUV());
}
