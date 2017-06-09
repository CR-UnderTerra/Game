/**
 * @file   AmazingCountDisplay.h
 * @brief  AmazingCountDisplayクラスのヘッダファイル
 * @author kotani
 */
#ifndef AMAZINGTEXT_H
#define AMAZINGTEXT_H
#include "../CountDisplayBase.h"

class AmazingCountDisplay : public CountDisplayBase
{
public:
	/**
	 * コンストラクタ
	 */
	AmazingCountDisplay(int _textureIndex, D3DXVECTOR2* _pos);

	/**
	 * デストラクタ
	 */
	virtual ~AmazingCountDisplay();

	/**
	 * 制御処理
	 */
	bool Update() override;

};


#endif
