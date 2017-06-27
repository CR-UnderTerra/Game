#include "Event/EventManager.h"
#include "UIBase.h"
#include "Math/Math.h"

UIBase::UIBase() :
m_VibRadius(10),
m_HeightVibAngle(0),
m_WidthVibAngle(0),
m_HeightTime(0),
m_WidthTime(0),
m_WidthVibValue(0),
m_HeightVibValue(0)
{
	/* プレイヤーがダメージを受けたときのEventの登録 */
	SINGLETON_INSTANCE(Lib::EventManager).AddEvent("PlayerDamage", [this]()
	{
		m_HeightTime = 60;
	});

	SINGLETON_INSTANCE(Lib::EventManager).AddEvent("EnemyDamage", [this]()
	{
		m_WidthTime = 30;
	});
}

void UIBase::Vibration()
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