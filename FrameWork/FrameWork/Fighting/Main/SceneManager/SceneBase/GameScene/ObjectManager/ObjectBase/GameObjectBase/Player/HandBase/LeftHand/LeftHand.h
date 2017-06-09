/**
 * @file   LeftHand.h
 * @brief  LeftHandクラスのヘッダファイル
 * @author kotani
 */
#ifndef LEFTHAND_H
#define LEFTHAND_H
#include "../../HandBase/HandBase.h"

class LeftHand : public HandBase
{
public:
	/**
	 * コンストラクタ
	 * @param[in] _textureIndex 使用するテクスチャのインデックス
	 */
	LeftHand(int _textureIndex);

	~LeftHand();

	/**
	 * 制御関数
	 */
	void Update() override;

	/**
	 * 描画関数
	 */
	void Draw() override;

private:

};


#endif
