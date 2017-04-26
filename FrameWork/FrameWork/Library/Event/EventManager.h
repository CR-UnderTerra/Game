/**
 * @file   EventManager.h
 * @brief  EventManagerクラスのヘッダファイル
 * @author kotani
 */
#ifndef EVENTMANAGER_H
#define EVENTMANAGER_H

#include <map>
#include "Event.h"
#include "..\Singleton.h"

namespace Lib
{
	class EventManager
	{
		friend Singleton<EventManager>;
	public:
		bool AddEvent(std::string _eventName, Event* _pEvent);
		bool CallEvent(std::string _eventName,int _eventId);

	private:
		EventManager(){};
		~EventManager(){};
		std::map<std::string,Event*> m_pEvent;
	};
}


#endif
