/**
 * @file   ScoreDisplay.h
 * @brief  ScoreDisplayクラスのヘッダファイル
 * @author kotani
 */
#ifndef SCOREDISPLAY_H
#define SCOREDISPLAY_H
#include "../UIBase.h"

class GoodText;
class AmazingText;
class FantasticText;

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
	GoodText*	   m_pGoodText;
	AmazingText*   m_pAmazingText;
	FantasticText* m_pFantasticText;

};


#endif
