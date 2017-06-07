/**
* @file   CollisionData.cpp
* @brief  CollisionDataクラスの実装
* @author kotani
*/
#include "CollisionData.h"

int CollisionData::m_IndexMax = 0;


CollisionData::CollisionData()
{
	m_Index = m_IndexMax;
	m_IndexMax++;
	m_CollisionState.IsEnable = false;
	m_CollisionState.HitState = NON_HIT;
}


//----------------------------------------------------------------------------------------------------
// Public Functions
//----------------------------------------------------------------------------------------------------

bool CollisionData::HitCheck(const CollisionState* _collisionState)
{
	CollisionState v1 = m_CollisionState;
	CollisionState v2 = *_collisionState;

	if (!v2.IsEnable)
	{
		m_CollisionState.HitState = NON_HIT;
		return false;
	}

	if (v1.CollisionType == PLAYER_KNIFE_TYPE &&
		v2.CollisionType == ENEMY_KNIFE_TYPE ||
		v1.CollisionType == ENEMY_KNIFE_TYPE &&
		v2.CollisionType == PLAYER_KNIFE_TYPE)
	{
		if (sqrt(pow(v2.Pos.x - v1.Pos.x, 2) + pow(v2.Pos.y - v1.Pos.y, 2)) < 12.f)
		{
			m_CollisionState.HitState = KNIFE_HIT;
			return true;	
		}
		else
		{
			m_CollisionState.HitState = NON_HIT;
			return false;
		}
	}

	if (v1.CollisionType == PLAYER_KNIFE_TYPE &&
		v2.CollisionType == ENEMY_TYPE ||
		v1.CollisionType == ENEMY_TYPE &&
		v2.CollisionType == PLAYER_KNIFE_TYPE)
	{
		if (sqrt(pow(v2.Pos.x - v1.Pos.x, 2) + pow(v2.Pos.y - v1.Pos.y, 2)) < 12.f)
		{
			m_CollisionState.HitState = KNIFE_HIT;
			return true;
		}
		else
		{
			m_CollisionState.HitState = NON_HIT;
			return false;
		}
	}

	if ((v1.Pos.x - v1.CollisionRect.x / 2) <= (v2.Pos.x + v2.CollisionRect.x / 2) &&
		(v1.Pos.x + v1.CollisionRect.x / 2) >= (v2.Pos.x - v2.CollisionRect.x / 2) &&
		(v1.Pos.y - v1.CollisionRect.y / 2) <= (v2.Pos.y + v2.CollisionRect.y / 2) &&
		(v1.Pos.y + v1.CollisionRect.y / 2) >= (v2.Pos.y - v2.CollisionRect.y / 2))
	{
		if (v1.CollisionType == ENEMY_KNIFE_TYPE &&
			v2.CollisionType == HAND_TYPE )
		{
			if (v1.IsCatchEnable && v2.HitState != CATCH_HIT)
			{
				m_CollisionState.HitState = CATCH_HIT;
				return true;
			}
		}
		else if (v1.CollisionType == HAND_TYPE &&
			v2.CollisionType == ENEMY_KNIFE_TYPE)
		{
			if (v2.IsCatchEnable)
			{
				m_CollisionState.HitState = CATCH_HIT;
				return true;
			}
		}
		else if (v1.CollisionType == ENEMY_KNIFE_TYPE &&
			v2.CollisionType == PLAYER_TYPE ||
			v1.CollisionType == PLAYER_TYPE &&
			v2.CollisionType == ENEMY_KNIFE_TYPE)
		{
			m_CollisionState.HitState = KNIFE_HIT;
			return true;
		}
	}
	m_CollisionState.HitState = NON_HIT;
	return false;
}
