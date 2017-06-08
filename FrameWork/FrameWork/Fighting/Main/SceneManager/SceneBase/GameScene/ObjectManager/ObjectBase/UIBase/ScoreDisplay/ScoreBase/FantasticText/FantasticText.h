/**
 * @file   FantasticText.h
 * @brief  FantasticTextクラスのヘッダファイル
 * @author kotani
 */
#ifndef FANTASTIC_H
#define FANTASTIC_H
#include "../ScoreBase.h"

class FantasticText : public ScoreBase
{
public:
	/**
	 * コンストラクタ
	 */
	FantasticText(int _textureIndex, D3DXVECTOR2* _pos);

	/**
	 * デストラクタ
	 */
	virtual ~FantasticText();

	/**
	 * 制御処理
	 */
	void Update() override;

};


#endif
