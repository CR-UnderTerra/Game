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

const D3DXVECTOR2 Player::m_RectCollision = D3DXVECTOR2(100, 250);


Player::Player(int _textureIndex) :
m_Hp(3)
{
	m_pCollisionData = new CollisionData();
	m_pHandBase.push_back(new RightHand(_textureIndex));
	m_pHandBase.push_back(new LeftHand(_textureIndex));

	RECT ClientRect;
	GetClientRect(SINGLETON_INSTANCE(Lib::Window).GetWindowHandle(), &ClientRect);
	m_Pos.x = static_cast<float>(ClientRect.right / 2);
	m_Pos.y = static_cast<float>(ClientRect.bottom);
	m_pCollisionData->SetCollision(&m_Pos, &m_RectCollision, CollisionData::PLAYER_TYPE);
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
	m_pCollisionData->SetCollision(&m_Pos, &m_RectCollision, CollisionData::PLAYER_TYPE);

	RECT ClientRect;
	GetClientRect(SINGLETON_INSTANCE(Lib::Window).GetWindowHandle(), &ClientRect);


	if (SINGLETON_INSTANCE(Lib::KeyDevice).GetKeyState()[DIK_W] == Lib::KEY_PUSH)
	{
		SINGLETON_INSTANCE(KnifeManager).
			ThrowKnife(&D3DXVECTOR2(static_cast<float>(ClientRect.right / 2), 200), Knife::PLAYER, 4.5f);
	}

	KnifeThrow();

	if (m_pCollisionData->GetCollisionState().HitState == CollisionData::KNIFE_HIT)
	{
		m_Hp--;
		SINGLETON_INSTANCE(GameDataManager).SetPlayerHp(m_Hp);
	}

	for (unsigned int i = 0; i < m_pHandBase.size(); i++)
	{
		m_pHandBase[i]->Update();
	}

	m_OldHitState = m_pHandBase[0]->GetHitState();
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
		SINGLETON_INSTANCE(KnifeManager).GetCatchKnife()->Throw(Knife::LEFT_ENEMY, 4.5f);
	}
	else if (m_OldHitState == CollisionData::CATCH_HIT &&
		SINGLETON_INSTANCE(Lib::KeyDevice).GetKeyState()[DIK_X] == Lib::KEY_RELEASE)
	{
		SINGLETON_INSTANCE(KnifeManager).GetCatchKnife()->Throw(Knife::FRONT_ENEMY, 4.5f);
	}
	else if (m_OldHitState == CollisionData::CATCH_HIT &&
		SINGLETON_INSTANCE(Lib::KeyDevice).GetKeyState()[DIK_C] == Lib::KEY_RELEASE)
	{
		SINGLETON_INSTANCE(KnifeManager).GetCatchKnife()->Throw(Knife::RIGHT_ENEMY, 4.5f);
	}
}
