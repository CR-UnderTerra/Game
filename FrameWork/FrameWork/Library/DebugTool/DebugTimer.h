/**
 * @file   DebugTimer.h
 * @brief  DebugTimerクラスのヘッダファイル
 * @author kotani
 */
#ifndef DEBUGTIMER_H
#define DEBUGTIMER_H
#include <Windows.h>
#include <MMsystem.h>
#include <stdio.h>
namespace Lib
{
	/**
	 * 処理速度表示用クラス
	 */
	class DebugTimer
	{
	public:
		/**
		 * コンストラクタ
		 * @param[in] _frameCount 何フレームごとに表示するか
		 */
		DebugTimer(int _showFrame);
		~DebugTimer(){};

		/**
		 * 計測の開始
		 */
		void Begin();

		/**
		 * 計測の終了
		 */
		void End();

		/**
		 * 結果の表示
		 */
		void TimerShow();

	private:
		LARGE_INTEGER m_CpuFreq, m_StartTime, m_EndTime;
		int			  m_Count, m_ShowFrame;

	};
}


#endif
