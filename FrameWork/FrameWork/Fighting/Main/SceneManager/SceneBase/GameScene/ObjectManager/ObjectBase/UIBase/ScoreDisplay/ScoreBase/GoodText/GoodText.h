/**
 * @file   GoodText.h
 * @brief  GoodTextクラスのヘッダファイル
 * @author kotani
 */
#ifndef GOODTEXT_H
#define GOODTEXT_H
#include "../ScoreBase.h"

class GoodText : public ScoreBase
{
public:
	/**
	 * コンストラクタ
	 */
	GoodText(int _textureIndex, D3DXVECTOR2* _pos);

	/**
	 * デストラクタ
	 */
	virtual ~GoodText();
	
	/**
	 * 制御処理
	 */
	void Update() override;

};


#endif
