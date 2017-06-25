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
#include "XInput/XInput.h"
#include "Sound/DSoundManager.h"
#include "Helper/Helper.h"

const D3DXVECTOR2 Player::m_RectCollision = D3DXVECTOR2(100, 230);


Player::Player(int _textureIndex)
{
	m_pCollisionData = new CollisionData();
	m_pHandBase.push_back(new RightHand(_textureIndex));
	m_pHandBase.push_back(new LeftHand(_textureIndex));

	RECT ClientRect = SINGLETON_INSTANCE(Lib::Window).GetWindowSize();
	m_Pos.x = static_cast<float>(ClientRect.right / 2);
	m_Pos.y = static_cast<float>(ClientRect.bottom);
	m_pCollisionData->SetCollision(&D3DXVECTOR3(m_Pos), &m_RectCollision, CollisionData::PLAYER_TYPE);
	m_pCollisionData->SetEnable(false);
	SINGLETON_INSTANCE(CollisionManager).AddCollision(m_pCollisionData);
	SINGLETON_INSTANCE(Lib::DSoundManager).LoadSound("Resource/Sound/se/houchouSE_nagekaeshi.wav", &m_KnifeThrowSoundIndex);
}

Player::~Player()
{
	SINGLETON_INSTANCE(Lib::DSoundManager).ReleaseSound(m_KnifeThrowSoundIndex);
	for (int i = m_pHandBase.size() - 1; i >= 0; i--)
	{
		Lib::SafeDelete(m_pHandBase[i]);
	}

	Lib::SafeDelete(m_pCollisionData);
}


//----------------------------------------------------------------------------------------------------
// Public Functions
//----------------------------------------------------------------------------------------------------

void Player::Update()
{
	KeyCheck();
	GamePadCheck();

	m_pCollisionData->SetCollision(&D3DXVECTOR3(m_Pos), &m_RectCollision, CollisionData::PLAYER_TYPE);

	RECT ClientRect = SINGLETON_INSTANCE(Lib::Window).GetWindowSize();

	for (unsigned int i = 0; i < m_pHandBase.size(); i++)
	{
		m_pHandBase[i]->Update();
	}
	KnifeCatchControl();
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
	/* 指定された方向に投げる */
	auto ThrowControl = [this](GameDataManager::TARGET _target)
	{
		bool returnVal = false;
		switch (SINGLETON_INSTANCE(KnifeManager).GetCatchKnifeState())
		{
		case JudgeGaugeUI::FANTASTIC_JUDGE:
			SINGLETON_INSTANCE(KnifeManager).CatchKnifeControl(_target, 1 * 0.5f);
			returnVal = true;
			break;
		case JudgeGaugeUI::AMAZING_JUDGE:
			SINGLETON_INSTANCE(KnifeManager).CatchKnifeControl(_target, 1 * 0.8f);
			returnVal = true;
			break;
		case JudgeGaugeUI::GOOD_JUDGE:
			SINGLETON_INSTANCE(KnifeManager).CatchKnifeControl(_target, 1.f);
			returnVal = true;
			break;
		}
		return returnVal;
	};

	if (SINGLETON_INSTANCE(Lib::KeyDevice).GetKeyState()[DIK_Z] == Lib::KEY_RELEASE ||
		SINGLETON_INSTANCE(Lib::XInput).GetButtonState(Lib::GAMEPAD_X, Lib::GAMEPAD1) == Lib::PAD_RELEASE)
	{
		if (ThrowControl(GameDataManager::LEFT_ENEMY_TARGET))
		{
			SINGLETON_INSTANCE(Lib::DSoundManager).SoundOperation(m_KnifeThrowSoundIndex, Lib::DSoundManager::SOUND_PLAY);
			m_pHandBase[0]->InitPos();
			m_pHandBase[1]->InitPos();
		}
		
	}
	else if (SINGLETON_INSTANCE(Lib::KeyDevice).GetKeyState()[DIK_X] == Lib::KEY_RELEASE ||
		SINGLETON_INSTANCE(Lib::XInput).GetButtonState(Lib::GAMEPAD_Y, Lib::GAMEPAD1) == Lib::PAD_RELEASE)
	{
		if (ThrowControl(GameDataManager::FRONT_ENEMY_TARGET))
		{
			SINGLETON_INSTANCE(Lib::DSoundManager).SoundOperation(m_KnifeThrowSoundIndex, Lib::DSoundManager::SOUND_PLAY);
			m_pHandBase[0]->InitPos();
			m_pHandBase[1]->InitPos();
		}
	}
	else if (SINGLETON_INSTANCE(Lib::KeyDevice).GetKeyState()[DIK_C] == Lib::KEY_RELEASE || 
		SINGLETON_INSTANCE(Lib::XInput).GetButtonState(Lib::GAMEPAD_B, Lib::GAMEPAD1) == Lib::PAD_RELEASE)
	{
		if (ThrowControl(GameDataManager::RIGHT_ENEMY_TARGET))
		{
			SINGLETON_INSTANCE(Lib::DSoundManager).SoundOperation(m_KnifeThrowSoundIndex, Lib::DSoundManager::SOUND_PLAY);
			m_pHandBase[0]->InitPos();
			m_pHandBase[1]->InitPos();
		}
	}
}

void Player::KeyCheck()
{
	SINGLETON_INSTANCE(Lib::KeyDevice).KeyCheck(DIK_Z);
	SINGLETON_INSTANCE(Lib::KeyDevice).KeyCheck(DIK_X);
	SINGLETON_INSTANCE(Lib::KeyDevice).KeyCheck(DIK_C);
	SINGLETON_INSTANCE(Lib::KeyDevice).KeyCheck(DIK_W);
}

void Player::GamePadCheck()
{
	SINGLETON_INSTANCE(Lib::XInput).CheckButton(Lib::GAMEPAD1, Lib::GAMEPAD_X, XINPUT_GAMEPAD_X);
	SINGLETON_INSTANCE(Lib::XInput).CheckButton(Lib::GAMEPAD1, Lib::GAMEPAD_Y, XINPUT_GAMEPAD_Y);
	SINGLETON_INSTANCE(Lib::XInput).CheckButton(Lib::GAMEPAD1, Lib::GAMEPAD_B, XINPUT_GAMEPAD_B);
	SINGLETON_INSTANCE(Lib::XInput).CheckButton(Lib::GAMEPAD1, Lib::GAMEANALOG_RIGHT_SHOULDER, XINPUT_GAMEPAD_RIGHT_SHOULDER);
}
