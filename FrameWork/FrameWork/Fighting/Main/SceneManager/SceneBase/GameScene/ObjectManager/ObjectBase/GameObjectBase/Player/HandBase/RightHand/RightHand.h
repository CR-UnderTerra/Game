/**
 * @file   RightHand.h
 * @brief  RightHandクラスのヘッダファイル
 * @author kotani
 */
#ifndef RIGHTHAND_H
#define RIGHTHAND_H
#include "../../HandBase/HandBase.h"

class RightHand : public HandBase
{
public:
	/**
	* コンストラクタ
	* @param[in] _textureIndex 使用するテクスチャのインデックス
	*/
	RightHand(int _textureIndex);

	~RightHand();

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
