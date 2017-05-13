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
	for (int i = m_pKnife.size() - 1; i >= 0; i--)
	{
		delete m_pKnife[i];
		m_pKnife[i] = NULL;
	}
	delete m_pAnimUvController;
	m_pAnimUvController = NULL;
}


//----------------------------------------------------------------------------------------------------
// Public Functions
//----------------------------------------------------------------------------------------------------

void KnifeManager::Init(int _textureIndex)
{
	m_TextureIndex = _textureIndex;
	m_pAnimUvController = new Lib::AnimUvController();
	m_pAnimUvController->LoadAnimation("Resource/test_001.anim", "F_sword01");
	for (int i = 0; i < m_KnifeMax; i++)
	{
		m_pKnife.push_back(new Knife(_textureIndex, m_pAnimUvController));
	}
}

void KnifeManager::ThrowKnife(D3DXVECTOR2* _pos, Knife::TARGET _target, float _velocity)
{
	for (int i = 0; i < m_KnifeMax; i++)
	{
		if (!m_pKnife[i]->GetIsThrow())
		{
			m_pKnife[i]->Throw(_pos, _target, _velocity);
			return;
		}
	}
}

Knife* const KnifeManager::GetCatchKnife()
{
	for (int i = 0; i < m_KnifeMax; i++)
	{
		if (m_pKnife[i]->GetIsCatch())
		{
			return m_pKnife[i];
		}
	}
	return m_pKnife[m_KnifeMax - 1];
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
