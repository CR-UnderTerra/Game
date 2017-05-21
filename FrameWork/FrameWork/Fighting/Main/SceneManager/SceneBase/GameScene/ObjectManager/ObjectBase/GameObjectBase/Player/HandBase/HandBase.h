/**
 * @file   HandBase.h
 * @brief  HandBaseクラスのヘッダファイル
 * @author kotani
 */
#ifndef HANDBASE_H
#define HANDBASE_H
#include "../../../GameObjectBase/GameObjectBase.h"
#include "Vertex2D/Vertex2D.h"
#include "Animation/AnimUvController.h"
#include "../../../../../CollisionManager/CollisionManager.h"
#include "../../../../../CollisionManager/CollisionData/CollisionData.h"
#include "../../../../../GameDataManager/GameDataManager.h"

class HandBase : public GameObjectBase
{
public:
	/**
	 * コンストラクタ
	 * @param[in] _playerTopPos プレイヤーの上の座標
	 * @param[in] _animName 使用するアニメーションネーム
	 * @param[in] _textureIndex 使用するテクスチャインデックス
	 */
	HandBase(D3DXVECTOR2* _playerTopPos, LPCTSTR _animName, int _textureIndex);

	/**
	 * デストラクタ
	 */
	~HandBase();

	/**
	 * 制御関数
	 */
	virtual void Update() override = 0;

	/**
	 * 描画関数
	 */
	virtual void Draw() override = 0;

	/**
	 * 手の当たり状態を取得する
	 * @return 手の当たりの状態
	 */
	inline CollisionData::HIT_STATE GetHitState()
	{
		return m_pCollisionData->GetCollisionState().HitState;
	}

	inline GameDataManager::TARGET GetTarget()
	{
		return m_Target;
	}

protected:
	static const D3DXVECTOR2	   m_Rect;
	static const float			   m_Acceleration;
	static GameDataManager::TARGET m_Target;

	Lib::AnimUvController*   m_pAnimUvController;
	Lib::Vertex2D*			 m_pVertex;
	int						 m_TextureIndex;
	D3DXVECTOR2				 m_PlayerTopPos;
	D3DXVECTOR2				 m_Pos;
	D3DXVECTOR2				 m_StartPos;
	D3DXVECTOR2				 m_EndPos;
	float					 m_MoveSpeed;
	CollisionData*		     m_pCollisionData;

};


#endif
