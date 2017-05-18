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

	m_Pos.x = static_cast<float>(ClientRect.right / 2 - 150 - m_Rect.x / 2);
	m_Pos.y = static_cast<float>(ClientRect.bottom / 2 + 200);
	m_pCollisionData->SetCollision(&m_Pos, &D3DXVECTOR2(m_Rect.x, m_Rect.y - 250), CollisionData::HAND_TYPE);

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

		if (m_Pos.x > ClientRect.right / 2 - (m_Rect.x / 2 + 80.f))
		{
			m_pCollisionData->SetEnable(true);
		}

		if (m_Pos.x < ClientRect.right / 2 - m_Rect.x / 2)
		{
			if (m_pCollisionData->GetCollisionState().HitState != CollisionData::CATCH_HIT)
			{
				m_Pos.x += m_MoveSpeed;
				m_MoveSpeed += m_Acceleration;
			}
		}
		else
		{
			m_pCollisionData->SetEnable(false);
			m_Pos.x = ClientRect.right / 2 - m_Rect.x / 2;
		}
	}
	else
	{
		if (m_Pos.x > ClientRect.right / 2 - 150 - m_Rect.x / 2)
		{
			m_Pos.x -= 3.f;
		}
		else if (m_Pos.x < ClientRect.right / 2 - 150 - m_Rect.x / 2)
		{
			m_Pos.x = static_cast<float>(ClientRect.right / 2 - 150 - m_Rect.x / 2);
		}
	}
	m_pCollisionData->SetCollision(&m_Pos, &D3DXVECTOR2(m_Rect.x, m_Rect.y - 150 - m_Rect.x / 2), CollisionData::HAND_TYPE);
}

void LeftHand::Draw()
{
	m_pVertex->Draw(&m_Pos,m_pAnimUvController->GetUV());
}
