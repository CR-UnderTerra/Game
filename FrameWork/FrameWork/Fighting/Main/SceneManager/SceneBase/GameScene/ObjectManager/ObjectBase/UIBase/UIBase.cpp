#include "Event/EventManager.h"
#include "UIBase.h"
#include "Math/Math.h"

UIBase::UIBase() :
m_VibRadius(10),
m_VibAngle(0),
m_Time(0),
m_VibValue(0)
{
	/* プレイヤーがダメージを受けたときのEventの登録 */
	SINGLETON_INSTANCE(Lib::EventManager).AddEvent("PlayerDamage", [this]()
	{
		m_Time = 60;
	});
}

void UIBase::Vibration()
{
	if (m_Time == 0)
	{
		m_VibAngle = 0;
		m_VibValue = 0.f;
		return;
	}
	m_VibAngle += 0.5f;
	m_Time--;
	m_VibValue = Lib::Math::GetAngleMovePos(m_VibRadius, m_VibAngle).y;
}