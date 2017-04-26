/**
 * @file   EventManager.cpp
 * @brief  EventManagerクラスの実装
 * @author kotani
 */
#include "EventManager.h"
#include "Event.h"


//----------------------------------------------------------------------------------------------------
// Public Functions
//----------------------------------------------------------------------------------------------------

bool Lib::EventManager::AddEvent(std::string _eventName,Event* _pEvent)
{
	m_pEvent[_eventName] = _pEvent;
	return true;
}

bool Lib::EventManager::CallEvent(std::string _eventName, int _eventId)
{
	if (m_pEvent.find(_eventName) == m_pEvent.end()){
		return false;
	}
	if (m_pEvent[_eventName] != NULL)
	{
		m_pEvent[_eventName]->Action(_eventId);
	}
	return true;
}
