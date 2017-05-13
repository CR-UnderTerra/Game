/**
 * @file   Player.cpp
 * @brief  Playerクラスの実装
 * @author kotani
 */
#include "Player.h"
#include "Window/Window.h"
#include "HandBase/RightHand/RightHand.h"
#include "HandBase/LeftHand/LeftHand.h"
#include "DxInput/KeyBoard/KeyDevice.h"
#include "../KnifeManager/KnifeManager.h"
#include "../../../../CollisionManager/CollisionManager.h"
#include "../../../../GameDataManager/GameDataManager.h"


Player::Player(int _textureIndex)
{
	m_pCollisionData = new CollisionData();
	m_pHandBase.push_back(new RightHand(_textureIndex));
	m_pHandBase.push_back(new LeftHand(_textureIndex));

	RECT ClientRect;
	GetClientRect(SINGLETON_INSTANCE(Lib::Window).GetWindowHandle(), &ClientRect);
	m_Pos.x = static_cast<float>(ClientRect.right / 2);
	m_Pos.y = static_cast<float>(ClientRect.bottom + 100);
	m_pCollisionData->SetCollision(&m_Pos,&D3DXVECTOR2(200,200),CollisionData::PLAYER_TYPE);
	m_pCollisionData->SetEnable(true);
	SINGLETON_INSTANCE(CollisionManager).AddCollision(m_pCollisionData);

}

Player::~Player()
{
	for (int i = m_pHandBase.size() - 1; i >= 0; i--)
	{
		delete m_pHandBase[i];
		m_pHandBase[i] = NULL;
	}

	delete m_pCollisionData;
	m_pCollisionData = NULL;
}


//----------------------------------------------------------------------------------------------------
// Public Functions
//----------------------------------------------------------------------------------------------------

void Player::Update()
{
	SINGLETON_INSTANCE(Lib::KeyDevice).KeyCheck(DIK_Z);
	SINGLETON_INSTANCE(Lib::KeyDevice).KeyCheck(DIK_X);
	SINGLETON_INSTANCE(Lib::KeyDevice).KeyCheck(DIK_C);
	SINGLETON_INSTANCE(Lib::KeyDevice).KeyCheck(DIK_W);
	m_pCollisionData->SetEnable(true);
	RECT ClientRect;
	GetClientRect(SINGLETON_INSTANCE(Lib::Window).GetWindowHandle(), &ClientRect);

	if (m_pHandBase[0]->GetIsCatch())
	{
		m_pCollisionData->SetCollision(&D3DXVECTOR2(m_Pos.x, m_Pos.y - 300), &D3DXVECTOR2(200, 200), CollisionData::HAND_TYPE);
	}
	else
	{
		m_pCollisionData->SetCollision(&m_Pos, &D3DXVECTOR2(100, 100), CollisionData::PLAYER_TYPE);
	}

	if (SINGLETON_INSTANCE(Lib::KeyDevice).GetKeyState()[DIK_W] == Lib::KEY_PUSH)
	{
		SINGLETON_INSTANCE(KnifeManager).
			ThrowKnife(&D3DXVECTOR2(static_cast<float>(ClientRect.right / 2), 200), Knife::PLAYER, 3.f);
	}

	KnifeThrow();
	m_OldHitState = m_pCollisionData->GetCollisionState().HitState;

	for (unsigned int i = 0; i < m_pHandBase.size(); i++)
	{
		m_pHandBase[i]->Update();
	}
}

void Player::Draw()
{
	for (unsigned int i = 0; i < m_pHandBase.size(); i++)
	{
		m_pHandBase[i]->Draw();
	}
}


//----------------------------------------------------------------------------------------------------
// Private Functions
//----------------------------------------------------------------------------------------------------

void Player::KnifeThrow()
{
	RECT ClientRect;
	GetClientRect(SINGLETON_INSTANCE(Lib::Window).GetWindowHandle(), &ClientRect);

	CollisionData::HIT_STATE hitState = m_pCollisionData->GetCollisionState().HitState;

	if (m_OldHitState == CollisionData::CATCH_HIT &&
		SINGLETON_INSTANCE(Lib::KeyDevice).GetKeyState()[DIK_Z] == Lib::KEY_RELEASE)
	{
		SINGLETON_INSTANCE(KnifeManager).GetCatchKnife()->Throw(Knife::LEFT_ENEMY, 3.f);
	}
	else if (m_OldHitState == CollisionData::CATCH_HIT &&
		SINGLETON_INSTANCE(Lib::KeyDevice).GetKeyState()[DIK_X] == Lib::KEY_RELEASE)
	{
		SINGLETON_INSTANCE(KnifeManager).GetCatchKnife()->Throw(Knife::FRONT_ENEMY, 3.f);
	}
	else if (m_OldHitState == CollisionData::CATCH_HIT &&
		SINGLETON_INSTANCE(Lib::KeyDevice).GetKeyState()[DIK_C] == Lib::KEY_RELEASE)
	{
		SINGLETON_INSTANCE(KnifeManager).GetCatchKnife()->Throw(Knife::RIGHT_ENEMY, 3.f);
	}
}
