/**
 * @file   ScoreUI.h
 * @brief  ScoreUIクラスのヘッダファイル
 * @author kotani
 */
#ifndef SCOREUI_H
#define SCOREUI_H
#include "../UIBase.h"

class ScoreUI : public UIBase
{
public:
	ScoreUI();
	~ScoreUI();

	void Update() override;

	void Draw() override;

private:

};


#endif
