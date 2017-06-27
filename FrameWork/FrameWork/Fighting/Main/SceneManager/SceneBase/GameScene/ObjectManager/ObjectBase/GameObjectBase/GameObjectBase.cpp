#include "Event/EventManager.h"
#include "GameObjectBase.h"
#include "Math/Math.h"

GameObjectBase::GameObjectBase() :
m_VibRadius(5),
m_HeightVibAngle(0),
m_WidthVibAngle(0),
m_HeightTime(0),
m_WidthTime(0),
m_WidthVibValue(0),
m_HeightVibValue(0)
{
}

void GameObjectBase::Vibration()
{
	m_HeightVibValue = Lib::Math::GetAngleMovePos(m_VibRadius, m_HeightVibAngle).y;
	m_WidthVibValue = Lib::Math::GetAngleMovePos(m_VibRadius, m_WidthVibAngle).y;

	if (m_HeightTime <= 0)
	{
		m_HeightVibAngle = 0;
		m_HeightVibValue = 0.f;
	}

	if (m_WidthTime <= 0)
	{
		m_WidthVibAngle = 0;
		m_WidthVibValue = 0.f;
	}


	m_HeightTime--;
	m_WidthTime--;
	m_HeightVibAngle += 0.5f;
	m_WidthVibAngle += 0.5f;
}