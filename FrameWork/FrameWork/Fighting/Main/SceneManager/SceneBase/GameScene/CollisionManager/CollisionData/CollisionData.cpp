/**
* @file   CollisionData.cpp
* @brief  CollisionDataクラスの実装
* @author kotani
*/
#include "CollisionData.h"
#include "Math/Math.h"

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

	auto CollisionCheck = [&](COLLISION_TYPE _v1, COLLISION_TYPE _v2)
	{
		if (v1.CollisionType == _v1 &&
			v2.CollisionType == _v2 ||
			v1.CollisionType == _v2 &&
			v2.CollisionType == _v2)
		{
			return true;
		}
		else
		{
			return false;
		}
	};

	if (!v2.IsEnable || !v1.IsEnable)
	{
		m_CollisionState.HitState = NON_HIT;
		return false;
	}

	
	if (CollisionCheck(AMAZING_PLAYER_KNIFE_TYPE, ENEMY_KNIFE_TYPE))
	{
		if (Lib::Math::GetDistance(v1.Pos, v2.Pos) < 20.f)
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

	if (v1.CollisionType == GOOD_PLAYER_KNIFE_TYPE ||
		v1.CollisionType == AMAZING_PLAYER_KNIFE_TYPE ||
		v1.CollisionType == FANTASTIC_PLAYER_KNIFE_TYPE &&
		v2.CollisionType == ENEMY_TYPE)
	{
		if (Lib::Math::GetDistance(v1.Pos, v2.Pos) < 20.f)
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

	if (v1.CollisionType == ENEMY_TYPE)
	{
		if (v2.CollisionType == GOOD_PLAYER_KNIFE_TYPE)
		{
			if (Lib::Math::GetDistance(v1.Pos, v2.Pos) < 20.f)
			{
				m_CollisionState.HitState = GOOD_HIT;
				return true;
			}
		}
		else if (v2.CollisionType == AMAZING_PLAYER_KNIFE_TYPE)
		{
			if (Lib::Math::GetDistance(v1.Pos, v2.Pos) < 20.f)
			{
				m_CollisionState.HitState = AMAZING_HIT;
				return true;
			}
		}
		else if (v2.CollisionType == FANTASTIC_PLAYER_KNIFE_TYPE)
		{
			if (Lib::Math::GetDistance(v1.Pos, v2.Pos) < 20.f)
			{
				m_CollisionState.HitState = FANTASTIC_HIT;
				return true;
			}
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
