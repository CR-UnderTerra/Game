/**
 * @file   Event.h
 * @brief  Eventクラスのヘッダファイル
 * @author kotani
 */
#ifndef EVENT_H
#define EVENT_H

namespace Lib
{
	class EventManager;

	class Event
	{
		friend class EventManager;
	public:
		Event();
		~Event();

	private:
		virtual void Action(int _eventId) = 0;

	};
}


#endif
