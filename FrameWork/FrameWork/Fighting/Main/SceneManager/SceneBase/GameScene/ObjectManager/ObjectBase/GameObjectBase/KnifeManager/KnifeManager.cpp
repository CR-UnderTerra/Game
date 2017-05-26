/**
 * @file   KnifeManager.cpp
 * @brief  KnifeManagerクラスの実装
 * @author kotani
 */
#include "Knife/Knife.h"
#include "KnifeManager.h"

const int KnifeManager::m_KnifeMax = 3;


KnifeManager::~KnifeManager()
{
	for (int i = Knife::ANIM_MAX - 1; i >= 0; i--)
	{
		delete m_pEnemyKnifeUv[i];
		m_pEnemyKnifeUv[i] = NULL;
	}

	for (int i = Knife::ANIM_MAX - 1; i >= 0; i--)
	{
		delete m_pPlayerKnifeUv[i];
		m_pPlayerKnifeUv[i] = NULL;
	}

	for (int i = m_pKnife.size() - 1; i >= 0; i--)
	{
		delete m_pKnife[i];
		m_pKnife[i] = NULL;
	}
}


//----------------------------------------------------------------------------------------------------
// Public Functions
//----------------------------------------------------------------------------------------------------

void KnifeManager::Init(int _textureIndex)
{
	m_TextureIndex = _textureIndex;
	auto InitPlayerAnim = [this](LPCTSTR _animName,Knife::KNIFE_ANIM_TYPE _animType)
	{
		m_pPlayerKnifeUv[_animType] = new Lib::AnimUvController();
		m_pPlayerKnifeUv[_animType]->LoadAnimation("Resource/test_001.anim", _animName);
	};

	auto InitEnemyAnim = [this](LPCTSTR _animName, Knife::KNIFE_ANIM_TYPE _animType)
	{
		m_pEnemyKnifeUv[_animType] = new Lib::AnimUvController();
		m_pEnemyKnifeUv[_animType]->LoadAnimation("Resource/test_001.anim", _animName);
	};

	InitPlayerAnim("F_sword02", Knife::FRONT);
	InitPlayerAnim("R_sword02", Knife::RIGHT);
	InitPlayerAnim("L_sword02", Knife::LEFT);

	InitEnemyAnim("F_sword01", Knife::FRONT);
	InitEnemyAnim("R_sword01", Knife::RIGHT);
	InitEnemyAnim("L_sword01", Knife::LEFT);

	for (int i = 0; i < m_KnifeMax; i++)
	{
		m_pKnife.push_back(new Knife(_textureIndex));
	}
}

void KnifeManager::ThrowKnife(D3DXVECTOR2* _pos, GameDataManager::TARGET _target, float _arriveTime)
{
	auto UvSelect = [this](GameDataManager::TARGET _knifeTarget)
	{
		switch (_knifeTarget)
		{
		case GameDataManager::PLAYER_TARGET:
			return m_pEnemyKnifeUv[Knife::FRONT];
			break;
		case GameDataManager::LEFT_ENEMY_TARGET:
			return m_pPlayerKnifeUv[Knife::LEFT];
			break;
		case GameDataManager::FRONT_ENEMY_TARGET:
			return m_pPlayerKnifeUv[Knife::FRONT];
			break;
		case GameDataManager::RIGHT_ENEMY_TARGET:
			return m_pPlayerKnifeUv[Knife::RIGHT];
			break;
		default:
			return m_pPlayerKnifeUv[Knife::FRONT];
			break;
		}
	};

	for (int i = 0; i < m_KnifeMax; i++)
	{
		if (!m_pKnife[i]->GetIsThrow())
		{
			m_pKnife[i]->Throw(_pos, _target, _arriveTime, UvSelect(_target));
			return;
		}
	}
}

void KnifeManager::CatchThrowKnife(GameDataManager::TARGET _target, float _arriveTime)
{
	auto UvSelect = [this](GameDataManager::TARGET _knifeTarget)
	{
		switch (_knifeTarget)
		{
		case GameDataManager::PLAYER_TARGET:
			return m_pEnemyKnifeUv[Knife::FRONT];
			break;
		case GameDataManager::LEFT_ENEMY_TARGET:
			return m_pPlayerKnifeUv[Knife::LEFT];
			break;
		case GameDataManager::FRONT_ENEMY_TARGET:
			return m_pPlayerKnifeUv[Knife::FRONT];
			break;
		case GameDataManager::RIGHT_ENEMY_TARGET:
			return m_pPlayerKnifeUv[Knife::RIGHT];
			break;
		default:
			return m_pPlayerKnifeUv[Knife::FRONT];
			break;
		}
	};

	for (int i = 0; i < m_KnifeMax; i++)
	{
		if (m_pKnife[i]->GetIsCatch())
		{
			m_pKnife[i]->Throw(_target, 1 * 0.5f, UvSelect(_target));
		}
	}
}

JudgeGaugeUI::JUDGE KnifeManager::GetCatchKnifeState()
{
	for (int i = 0; i < m_KnifeMax; i++)
	{
		if (m_pKnife[i]->GetIsCatch())
		{
			return m_pKnife[i]->GetCatchState();
		}
	}
	return JudgeGaugeUI::FAILED_JUDGE;
}

void KnifeManager::Update()
{
	for (int i = 0; i < m_KnifeMax; i++)
	{
		m_pKnife[i]->Update();
	}
}

void KnifeManager::Draw()
{
	for (int i = 0; i < m_KnifeMax; i++)
	{
		m_pKnife[i]->Draw();
	}
}
