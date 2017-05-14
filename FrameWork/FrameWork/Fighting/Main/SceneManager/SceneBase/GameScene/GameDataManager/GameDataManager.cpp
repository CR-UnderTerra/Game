/**
 * @file   GameDataManager.cpp
 * @brief  GameDataManagerクラスの実装
 * @author kotani
 */
#include "GameDataManager.h"
#include "../ObjectManager/ObjectBase/UIBase/DistanceGaugeUI/DistanceGaugeUI.h"
#include "Window/Window.h"


GameDataManager::GameDataManager() :
m_PlayerHp(3)
{
	RECT ClientRect;
	GetClientRect(SINGLETON_INSTANCE(Lib::Window).GetWindowHandle(), &ClientRect);

	m_Pos[PLAYER_TARGET].x = static_cast<float>(ClientRect.right / 2);
	m_Pos[PLAYER_TARGET].y = static_cast<float>(ClientRect.bottom / 2 + 200);

	m_Pos[LEFT_ENEMY_TARGET].x = static_cast<float>(ClientRect.right / 2 - 150);
	m_Pos[LEFT_ENEMY_TARGET].y = 200.f;
	
	m_Pos[FRONT_ENEMY_TARGET].x = static_cast<float>(ClientRect.right / 2);
	m_Pos[FRONT_ENEMY_TARGET].y = 200.f;
	
	m_Pos[RIGHT_ENEMY_TARGET].x = static_cast<float>(ClientRect.right / 2 + 150);
	m_Pos[RIGHT_ENEMY_TARGET].y = 200.f;
}


GameDataManager::~GameDataManager()
{
}


//----------------------------------------------------------------------------------------------------
// Public Functions
//----------------------------------------------------------------------------------------------------

void GameDataManager::Update()
{
}

void GameDataManager::Draw()
{
}

void GameDataManager::SetKnifeDistance(float _distance, float _velocity,int _index)
{
	m_pDistanceGaugeUI->SetKnifeBar(_distance, _velocity, _index);
}

void GameDataManager::SetKnifeBarIsEnable(int _index,bool _isEnable)
{
	m_pDistanceGaugeUI->SetKnifeBarIsEnable(_index,_isEnable);
}