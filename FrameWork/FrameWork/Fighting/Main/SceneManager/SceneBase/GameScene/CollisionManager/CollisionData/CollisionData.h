/**
 * @file   CollisionData.h
 * @brief  CollisionDataクラスのヘッダファイル
 * @author kotani
 */
#ifndef COLLISIONDATA_H
#define COLLISIONDATA_H
#include <D3DX10.h>

class CollisionData
{
public:
	enum COLLISION_TYPE
	{
		ENEMY_TYPE,
		PLAYER_TYPE,
		HAND_TYPE,
		PLAYER_KNIFE_TYPE,
		ENEMY_KNIFE_TYPE
	};

	enum HIT_STATE
	{
		KNIFE_HIT,
		CATCH_HIT,
		NON_HIT
	};

	struct CollisionState
	{
		D3DXVECTOR2	   Pos;
		D3DXVECTOR2    CollisionRect;
		COLLISION_TYPE CollisionType;
		HIT_STATE      HitState;
		bool		   IsEnable;
	};
	/**
	 * コンストラクタ
	 */
	CollisionData();

	/**
	* デストラクタ
	*/
	~CollisionData() = default;

	/**
	* 判定チェック
	* @param[in]
	*/
	bool HitCheck(const CollisionState* _collisionState);

	/**
	 * 当たり判定の設定
	 */
	inline void SetCollision(const D3DXVECTOR2* _pos, const D3DXVECTOR2* _collisionRect, COLLISION_TYPE _collisionType)
	{
		m_CollisionState.Pos = *_pos;
		m_CollisionState.CollisionRect = *_collisionRect;
		m_CollisionState.CollisionType = _collisionType;
	}

	/**
	 * 当たり判定の取得
	 */
	inline CollisionState GetCollisionState() const
	{
		return m_CollisionState;
	}

	/**
	 * 当たり判定を有効化するかの設定
	 */
	inline void SetEnable(bool _enable)
	{
		m_CollisionState.IsEnable = _enable;
	}

	inline int GetIndex()
	{
		return m_Index;
	}

private:
	static int     m_IndexMax;
	CollisionState m_CollisionState;
	int			   m_Index; //!< 何番目の配列にセットされたか?

};


#endif
