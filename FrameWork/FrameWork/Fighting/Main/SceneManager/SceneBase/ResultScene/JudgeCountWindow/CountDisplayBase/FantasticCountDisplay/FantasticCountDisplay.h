/**
 * @file   FantasticCountDisplay.h
 * @brief  FantasticCountDisplayクラスのヘッダファイル
 * @author kotani
 */
#ifndef FANTASTICCOUNTDISPLAY_H
#define FANTASTICCOUNTDISPLAY_H
#include "../CountDisplayBase.h"

class FantasticCountDisplay : public CountDisplayBase
{
public:
	/**
	 * コンストラクタ
	 */
	FantasticCountDisplay(int _textureIndex, D3DXVECTOR2* _pos);

	/**
	 * デストラクタ
	 */
	virtual ~FantasticCountDisplay();

	/**
	 * 制御処理
	 */
	bool Update() override;

};


#endif
