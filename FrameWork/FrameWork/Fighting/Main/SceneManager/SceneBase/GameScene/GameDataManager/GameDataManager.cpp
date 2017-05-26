/**
 * @file   GameDataManager.cpp
 * @brief  GameDataManagerクラスの実装
 * @author kotani
 */
#include "GameDataManager.h"
#include "../ObjectManager/ObjectBase/UIBase/DistanceGaugeUI/DistanceGaugeUI.h"
#include "Window/Window.h"


GameDataManager::GameDataManager() :
m_PlayerHp(3),
m_IsGameOver(false)
{
	RECT ClientRect;
	GetClientRect(SINGLETON_INSTANCE(Lib::Window).GetWindowHandle(), &ClientRect);

	m_Pos[PLAYER_TARGET].x = static_cast<float>(ClientRect.right / 2);
	m_Pos[PLAYER_TARGET].y = static_cast<float>(ClientRect.bottom / 2 + 300);

	m_Pos[LEFT_ENEMY_TARGET].x = static_cast<float>(ClientRect.right / 2 - 150);
	m_Pos[LEFT_ENEMY_TARGET].y = 500.f;
	
	m_Pos[FRONT_ENEMY_TARGET].x = static_cast<float>(ClientRect.right / 2);
	m_Pos[FRONT_ENEMY_TARGET].y = 500.f;
	
	m_Pos[RIGHT_ENEMY_TARGET].x = static_cast<float>(ClientRect.right / 2 + 150);
	m_Pos[RIGHT_ENEMY_TARGET].y = 500.f;
}


//----------------------------------------------------------------------------------------------------
// Public Functions
//----------------------------------------------------------------------------------------------------

void GameDataManager::Update()
{
	if (m_PlayerHp == 0)
	{
		m_IsGameOver = true;
	}
}

void GameDataManager::SetKnifeDistance(float _distance, float _velocity,int _index)
{
	m_pDistanceGaugeUI->SetKnifeBar(_distance, _velocity, _index);
}

void GameDataManager::SetKnifeBarIsEnable(int _index,bool _isEnable)
{
	m_pDistanceGaugeUI->SetKnifeBarIsEnable(_index,_isEnable);
}

JudgeGaugeUI::JUDGE GameDataManager::KnifeJadge(int _index)
{
	return m_pDistanceGaugeUI->KnifeJadge(_index);
}