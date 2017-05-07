/**
 * @file   Player.h
 * @brief  Playerクラスのヘッダファイル
 * @author kotani
 */
#ifndef PLAYER_H
#define PLAYER_H
#include "../ObjectBase/ObjectBase.h"
#include <vector>

class HandBase;

class Player : public ObjectBase
{
public:
	/**
	 * コンストラクタ
	 * @param[in] _textureIndex 使用するテクスチャのインデックス
	 */
	Player(int _textureIndex);

	/**
	 * デストラクタ
	 */
	~Player();

	/**
	 * 制御関数
	 */
	void Update() override;

	/**
	 * 描画関数
	 */
	void Draw() override;

private:
	std::vector<HandBase*> m_pHandBase;
	int					   m_Hp;

};


#endif
