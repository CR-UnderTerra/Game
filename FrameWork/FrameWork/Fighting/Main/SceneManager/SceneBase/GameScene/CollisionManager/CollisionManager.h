/**
 * @file   CollisionManager.h
 * @brief  CollisionManagerクラスのヘッダファイル
 * @author kotani
 */
#ifndef COLLISIONMANAGR_H
#define COLLISIONMANAGR_H
#include "Singleton.h"
#include <vector>
#include "CollisionData/CollisionData.h"

class CollisionManager
{
	friend Lib::Singleton<CollisionManager>;

public:
	/**
	* 当たり判定の追加
	* @param[in] _pCollisionData 追加する当たり判定
	*/
	void AddCollision(CollisionData* _pCollisionData);

	/**
	* 判定の更新
	*/
	void Update();

private:
	CollisionManager() = default;
	~CollisionManager() = default;

	std::vector<CollisionData*> m_pCollisionData;


};


#endif
