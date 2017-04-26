/**
 * @file   DebugTimer.cpp
 * @brief  DebugTimerクラスの実装
 * @author kotani
 */
#include "DebugTimer.h"


Lib::DebugTimer::DebugTimer(int _showFrame) :
m_ShowFrame(_showFrame),
m_Count(0)
{
	QueryPerformanceFrequency(&m_CpuFreq);
}

void Lib::DebugTimer::Begin()
{
	QueryPerformanceCounter(&m_StartTime);
}

void Lib::DebugTimer::End()
{
	QueryPerformanceCounter(&m_EndTime);
}

void Lib::DebugTimer::TimerShow()
{
	m_Count++;
	if (m_Count > m_ShowFrame)
	{
		char    str[16];
		sprintf_s(str, "%f[ms]\n", 1000.0*((double)m_EndTime.QuadPart - m_StartTime.QuadPart) / m_CpuFreq.QuadPart);
		OutputDebugString(str);
		m_Count = 0;
	}
}
