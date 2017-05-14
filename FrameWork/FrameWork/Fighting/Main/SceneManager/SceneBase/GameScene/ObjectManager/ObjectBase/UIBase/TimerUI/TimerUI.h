/**
 * @file   TimerUI.h
 * @brief  TimerUIクラスのヘッダファイル
 * @author kotani
 */
#ifndef SCOREUI_H
#define SCOREUI_H
#include "../UIBase.h"

class TimerUI : public UIBase
{
public:
	TimerUI();
	~TimerUI();

	void Update() override;

	void Draw() override;

private:

};


#endif
