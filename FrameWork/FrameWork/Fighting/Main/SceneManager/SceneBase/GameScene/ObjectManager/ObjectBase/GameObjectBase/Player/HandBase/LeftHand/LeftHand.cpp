/**
 * @file   LeftHand.cpp
 * @brief  LeftHandクラスの実装
 * @author kotani
 */
#include "LeftHand.h"
#include "DxInput/KeyBoard/KeyDevice.h"
#include "Window/Window.h"
#include "../../../../../../../../../XInput/XInput.h"


LeftHand::LeftHand(int _textureIndex) :
HandBase(&D3DXVECTOR2(0, 0), "h_left", _textureIndex)
{
	RECT ClientRect;
	GetClientRect(SINGLETON_INSTANCE(Lib::Window).GetWindowHandle(), &ClientRect);

	m_Pos.x = static_cast<float>(ClientRect.right / 2 - 150 - m_Rect.x / 2);
	m_Pos.y = static_cast<float>(ClientRect.bottom / 2 + 200);
	m_StartPos = m_Pos;
	m_EndPos.x = static_cast<float>(ClientRect.right / 2 - m_Rect.x / 2);
	m_EndPos.y = m_StartPos.y;
	m_pCollisionData->SetCollision(&m_Pos, &D3DXVECTOR2(m_Rect.x, m_Rect.y), CollisionData::HAND_TYPE);
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

	if (SINGLETON_INSTANCE(Lib::KeyDevice).GetKeyState()[DIK_Z] == Lib::KEY_ON)
	{
		m_Target = GameDataManager::LEFT_ENEMY_TARGET;
	}
	else if (SINGLETON_INSTANCE(Lib::KeyDevice).GetKeyState()[DIK_X] == Lib::KEY_ON)
	{
		m_Target = GameDataManager::FRONT_ENEMY_TARGET;
	}
	else if (SINGLETON_INSTANCE(Lib::KeyDevice).GetKeyState()[DIK_C] == Lib::KEY_ON)
	{
		m_Target = GameDataManager::RIGHT_ENEMY_TARGET;
	}

	if (SINGLETON_INSTANCE(Lib::KeyDevice).GetKeyState()[DIK_Z] == Lib::KEY_ON ||
		SINGLETON_INSTANCE(Lib::KeyDevice).GetKeyState()[DIK_X] == Lib::KEY_ON ||
		SINGLETON_INSTANCE(Lib::KeyDevice).GetKeyState()[DIK_C] == Lib::KEY_ON ||
		SINGLETON_INSTANCE(Lib::XInput).GetButtonState(Lib::GAMEPAD_X, Lib::GAMEPAD1) == Lib::PAD_ON ||
		SINGLETON_INSTANCE(Lib::XInput).GetButtonState(Lib::GAMEPAD_Y, Lib::GAMEPAD1) == Lib::PAD_ON ||
		SINGLETON_INSTANCE(Lib::XInput).GetButtonState(Lib::GAMEPAD_B, Lib::GAMEPAD1) == Lib::PAD_ON)
	{
		if (m_Pos.x < m_EndPos.x)
		{
			if (m_pCollisionData->GetCollisionState().HitState != CollisionData::CATCH_HIT)
			{
				m_Pos.x += m_MoveSpeed;
				m_MoveSpeed += m_Acceleration;
			}
		}
		else if (m_Pos.x > (m_EndPos.x + 80.f))
		{
			m_pCollisionData->SetEnable(true);
		}
		else
		{
			m_pCollisionData->SetEnable(false);
			m_Pos.x = m_EndPos.x;
		}
	}
	else
	{
		m_MoveSpeed = 1;
		if (m_Pos.x > m_StartPos.x)
		{
			m_Pos.x -= 3.f;
		}
		else if (m_Pos.x < m_StartPos.x)
		{
			m_Pos.x = m_StartPos.x;
		}
	}
	m_pCollisionData->SetCollision(&m_Pos, &D3DXVECTOR2(m_Rect.x, m_Rect.y), CollisionData::HAND_TYPE);
}

void LeftHand::Draw()
{
	m_pVertex->Draw(&m_Pos,m_pAnimUvController->GetUV());
}
