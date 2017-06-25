/**
 * @file   KnifeManager.cpp
 * @brief  KnifeManagerクラスの実装
 * @author kotani
 */
#include "Knife/Knife.h"
#include "KnifeManager.h"
#include "Helper/Helper.h"

const int KnifeManager::m_KnifeMax = 3;


KnifeManager::~KnifeManager()
{
	for (int i = Knife::ANIM_MAX - 1; i >= 0; i--)
	{
		Lib::SafeDelete(m_pEnemyKnifeUv[i]);
	}

	for (int i = Knife::ANIM_MAX - 1; i >= 0; i--)
	{
		Lib::SafeDelete(m_pPlayerKnifeUv[i]);
	}

	for (int i = m_pKnife.size() - 1; i >= 0; i--)
	{
		Lib::SafeDelete(m_pKnife[i]);
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

	InitPlayerAnim("F_mail02", Knife::FRONT);
	InitPlayerAnim("R_mail02", Knife::RIGHT);
	InitPlayerAnim("L_mail02", Knife::LEFT);

	InitEnemyAnim("F_mail01", Knife::FRONT);
	InitEnemyAnim("L_mail01", Knife::RIGHT);
	InitEnemyAnim("R_mail01", Knife::LEFT);

	for (int i = 0; i < m_KnifeMax; i++)
	{
		m_pKnife.push_back(new Knife(_textureIndex));
	}
}

void KnifeManager::ThrowKnife(D3DXVECTOR2* _pos, GameDataManager::TARGET _myTarget, GameDataManager::TARGET _target, float _arriveTime)
{
	auto UvSelect = [this](GameDataManager::TARGET _myTarget, GameDataManager::TARGET _knifeTarget)
	{
		switch (_knifeTarget)
		{
		case GameDataManager::PLAYER_TARGET:
			if (_myTarget == GameDataManager::LEFT_ENEMY_TARGET)
			{
				return m_pEnemyKnifeUv[Knife::RIGHT];
			}
			else if (_myTarget == GameDataManager::FRONT_ENEMY_TARGET)
			{
				return m_pEnemyKnifeUv[Knife::FRONT];
			}
			else
			{
				return m_pEnemyKnifeUv[Knife::LEFT];
			}
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
			m_pKnife[i]->Throw(_pos, _target, _arriveTime, UvSelect(_myTarget, _target));
			return;
		}
	}
}

void KnifeManager::CatchKnifeControl(GameDataManager::TARGET _target, float _arriveTime)
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
