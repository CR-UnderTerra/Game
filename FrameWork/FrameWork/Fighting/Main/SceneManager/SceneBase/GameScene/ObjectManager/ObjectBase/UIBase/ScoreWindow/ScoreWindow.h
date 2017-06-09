/**
 * @file   ScoreWindow.h
 * @brief  ScoreWindowクラスのヘッダファイル
 * @author kotani
 */
#ifndef SCOREDISPLAY_H
#define SCOREDISPLAY_H
#include "../UIBase.h"
#include <array>
class ScoreBase;

class ScoreWindow : public UIBase
{
public:
	/**
	 * コンストラクタ
	 */
	ScoreWindow(int _textureIndex);

	/**
	 * デストラクタ
	 */
	~ScoreWindow();

	/**
	 * 制御関数
	 */
	void Update() override;

	/**
	 * 描画関数
	 */
	void Draw() override;

private:
	D3DXVECTOR2	   m_Pos;
	std::array<ScoreBase*, 3> m_pScoreBase;

};


#endif
