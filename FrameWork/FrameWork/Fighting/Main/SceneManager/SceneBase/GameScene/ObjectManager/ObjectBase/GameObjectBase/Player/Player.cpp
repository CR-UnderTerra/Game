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

const D3DXVECTOR2 Player::m_RectCollision = D3DXVECTOR2(100, 230);


Player::Player(int _textureIndex)
{
	m_pCollisionData = new CollisionData();
	m_pHandBase.push_back(new RightHand(_textureIndex));
	m_pHandBase.push_back(new LeftHand(_textureIndex));

	RECT ClientRect;
	GetClientRect(SINGLETON_INSTANCE(Lib::Window).GetWindowHandle(), &ClientRect);
	m_Pos.x = static_cast<float>(ClientRect.right / 2);
	m_Pos.y = static_cast<float>(ClientRect.bottom);
	m_pCollisionData->SetCollision(&m_Pos, &m_RectCollision, CollisionData::PLAYER_TYPE);
	m_pCollisionData->SetEnable(false);
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
			ThrowKnife(&D3DXVECTOR2(static_cast<float>(ClientRect.right / 2), 200), GameDataManager::PLAYER_TARGET, 1);
	}

	KnifeCatchControl();

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

void Player::KnifeCatchControl()
{
	RECT ClientRect;
	GetClientRect(SINGLETON_INSTANCE(Lib::Window).GetWindowHandle(), &ClientRect);

	CollisionData::HIT_STATE hitState = m_pCollisionData->GetCollisionState().HitState;

	if (m_OldHitState == CollisionData::CATCH_HIT &&
		SINGLETON_INSTANCE(Lib::KeyDevice).GetKeyState()[DIK_Z] == Lib::KEY_RELEASE)
	{
		KnifeThrowControl(GameDataManager::LEFT_ENEMY_TARGET);
	}
	else if (m_OldHitState == CollisionData::CATCH_HIT &&
		SINGLETON_INSTANCE(Lib::KeyDevice).GetKeyState()[DIK_X] == Lib::KEY_RELEASE)
	{
		KnifeThrowControl(GameDataManager::FRONT_ENEMY_TARGET);
	}
	else if (m_OldHitState == CollisionData::CATCH_HIT &&
		SINGLETON_INSTANCE(Lib::KeyDevice).GetKeyState()[DIK_C] == Lib::KEY_RELEASE)
	{
		KnifeThrowControl(GameDataManager::RIGHT_ENEMY_TARGET);
	}
}

void Player::KnifeThrowControl(GameDataManager::TARGET _target)
{
	switch (SINGLETON_INSTANCE(KnifeManager).GetCatchKnife()->GetCatchState())
	{
	case JudgeGaugeUI::FANTASTIC_JUDGE:
		SINGLETON_INSTANCE(KnifeManager).GetCatchKnife()->Throw(_target, 1 * 0.5f);
		break;
	case JudgeGaugeUI::AMAZING_JUDGE:
		SINGLETON_INSTANCE(KnifeManager).GetCatchKnife()->Throw(_target, 1 * 0.8);
		break;
	case JudgeGaugeUI::GOOD_JUDGE:
		SINGLETON_INSTANCE(KnifeManager).GetCatchKnife()->Throw(_target, 1);
		break;
	}
}

