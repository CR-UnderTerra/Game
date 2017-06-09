/**
 * @file   GoodCountDisplay.h
 * @brief  GoodCountDisplayクラスのヘッダファイル
 * @author kotani
 */
#ifndef GOODCOUNTDISPLAY_H
#define GOODCOUNTDISPLAY_H
#include "../CountDisplayBase.h"

class GoodCountDisplay : public CountDisplayBase
{
public:
	/**
	 * コンストラクタ
	 */
	GoodCountDisplay(int _textureIndex, D3DXVECTOR2* _pos);

	/**
	 * デストラクタ
	 */
	virtual ~GoodCountDisplay();

	/**
	 * 制御処理
	 */
	bool Update() override;

};


#endif
