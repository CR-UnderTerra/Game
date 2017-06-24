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

	class EventListnerBase
	{
		friend class EventManager;
	public:
		EventListnerBase();
		~EventListnerBase();

	private:
		virtual void Action() = 0;

	};
}


#endif
