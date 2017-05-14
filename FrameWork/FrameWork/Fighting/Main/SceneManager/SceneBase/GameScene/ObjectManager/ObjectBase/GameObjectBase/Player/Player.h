/**
 * @file   Player.h
 * @brief  Playerクラスのヘッダファイル
 * @author kotani
 */
#ifndef PLAYER_H
#define PLAYER_H
#include <vector>
#include "../GameObjectBase.h"
#include "../../../../CollisionManager/CollisionData/CollisionData.h"

class HandBase;

class Player : public GameObjectBase
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


	static const D3DXVECTOR2 m_RectCollision;
private:
	/**
	 * ナイフの投げる方向処理
	 */
	void KnifeThrow();


	std::vector<HandBase*>   m_pHandBase;
	CollisionData*		     m_pCollisionData;
	CollisionData::HIT_STATE m_OldHitState;
	D3DXVECTOR2			     m_Pos;

};


#endif
