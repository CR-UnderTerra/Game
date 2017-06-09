/**
 * @file   AmazingText.h
 * @brief  AmazingTextクラスのヘッダファイル
 * @author kotani
 */
#ifndef AMAZINGTEXT_H
#define AMAZINGTEXT_H
#include "../ScoreBase.h"

class AmazingText : public ScoreBase
{
public:
	/**
	 * コンストラクタ
	 */
	AmazingText(int _textureIndex, D3DXVECTOR2* _pos);

	/**
	 * デストラクタ
	 */
	virtual ~AmazingText();

	/**
	 * 制御処理
	 */
	void Update() override;

};


#endif
