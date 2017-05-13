/**
 * @file   GameDataManager.cpp
 * @brief  GameDataManagerクラスの実装
 * @author kotani
 */
#include "GameDataManager.h"
#include "../ObjectManager/ObjectBase/UIBase/DistanceGaugeUI/DistanceGaugeUI.h"

GameDataManager::GameDataManager()
{
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

void GameDataManager::SetKnifeDistance(float _distance, float _velocity)
{
	m_pDistanceGaugeUI->SetKnifeBar(_distance, _velocity);
}

