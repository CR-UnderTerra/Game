/**
 * @file   ScoreDisplay.h
 * @brief  ScoreDisplayクラスのヘッダファイル
 * @author kotani
 */
#ifndef SCOREDISPLAY_H
#define SCOREDISPLAY_H
#include "../UIBase.h"
#include <array>
class ScoreBase;

class ScoreDisplay : public UIBase
{
public:
	/**
	 * コンストラクタ
	 */
	ScoreDisplay(int _textureIndex);

	/**
	 * デストラクタ
	 */
	~ScoreDisplay();

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
