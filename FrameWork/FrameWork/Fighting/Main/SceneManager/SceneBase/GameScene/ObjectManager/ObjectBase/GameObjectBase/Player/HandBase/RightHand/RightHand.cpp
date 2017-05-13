/**
* @file   RightHand.cpp
* @brief  RightHandクラスの実装
* @author kotani
*/
#include "RightHand.h"
#include "Texture/TextureManager.h"
#include "Window/Window.h"
#include "Dx11/DX11Manager.h"
#include "DxInput/KeyBoard/KeyDevice.h"
#include "Window/Window.h"


RightHand::RightHand(int _textureIndex) :
HandBase(&D3DXVECTOR2(0, 0), "h_right", _textureIndex)
{
	RECT ClientRect;
	GetClientRect(SINGLETON_INSTANCE(Lib::Window).GetWindowHandle(), &ClientRect);

	m_Pos.x = static_cast<float>(ClientRect.right / 2 + 300);
	m_Pos.y = static_cast<float>(ClientRect.bottom / 2 + 200);
	m_pCollisionData->SetCollision(&m_Pos, &D3DXVECTOR2(m_Rect.x, m_Rect.y - 150), CollisionData::HAND_TYPE);
}

RightHand::~RightHand()
{
}


//----------------------------------------------------------------------------------------------------
// Public Functions
//----------------------------------------------------------------------------------------------------

void RightHand::Update()
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
		if (m_Pos.x < ClientRect.right / 2 + (m_Rect.x / 2 + 80.f))
		{
			m_pCollisionData->SetEnable(true);
			m_IsCatch = true;
		}

		if (m_Pos.x > ClientRect.right / 2 + m_Rect.x / 2)
		{
			if (m_pCollisionData->GetCollisionState().HitState != CollisionData::CATCH_HIT)
			{
				m_Pos.x -= m_MoveSpeed;
				m_MoveSpeed += m_Acceleration;
			}
		}
		else
		{
			m_pCollisionData->SetEnable(false);
			m_Pos.x = ClientRect.right / 2 + m_Rect.x / 2;
		}
	}
	else
	{
		if (m_Pos.x < ClientRect.right / 2 + 300)
		{
			m_Pos.x += m_MoveSpeed;
			m_MoveSpeed += m_Acceleration;
		}
		else if (m_Pos.x > ClientRect.right / 2 + 300)
		{
			m_Pos.x = static_cast<float>(ClientRect.right / 2 + 300.f);
		}
	}
	m_pCollisionData->SetCollision(&m_Pos, &D3DXVECTOR2(m_Rect.x, m_Rect.y - 150), CollisionData::HAND_TYPE);

}

void RightHand::Draw()
{
	m_pVertex->Draw(&m_Pos, m_pAnimUvController->GetUV());
}
