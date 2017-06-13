/**
 * @file   CollisionManager.cpp
 * @brief  CollisionManagerクラスの実装
 * @author kotani
 */
#include "CollisionManager.h"


//----------------------------------------------------------------------------------------------------
// Public Functions
//----------------------------------------------------------------------------------------------------

void CollisionManager::AddCollision(CollisionData* _pCollisionData)
{
	m_pCollisionData.push_back(_pCollisionData);
}

void CollisionManager::Update()
{
	if (m_pCollisionData.size() < 1) return;

	for (unsigned int i = 0; i < m_pCollisionData.size(); i++)
	{
		for (unsigned int j = 0; j < m_pCollisionData.size(); j++)
		{
			if (i != j)
			{
				CollisionData::CollisionState collisionState = m_pCollisionData[j]->GetCollisionState();
				if (m_pCollisionData[i]->HitCheck(&collisionState))
				{
					break;
				}
			}
		}
	}
}
