/**
 * @file   ObjectManager.h
 * @brief  ObjectManagerクラスのヘッダファイル
 * @author kotani
 */
#ifndef OBJECTMANAGER_H
#define OBJECTMANAGER_H
#include <vector>
#include "ObjectBase/GameObjectBase/GameObjectBase.h"


class ObjectManager
{
public:
	/**
	 * コンストラクタ
	 */
	ObjectManager();

	/**
	 * デストラクタ
	 */
	~ObjectManager();

	/**
	 * 制御関数
	 */
	void Update();

	/**
	 * 描画関数
	 */
	void Draw();

private:
	ObjectManager(const ObjectManager&);
	void operator=(const ObjectManager&);

	std::vector<GameObjectBase*> m_pGameObject;
	
	int							 m_TextureIndex1;
	int							 m_TextureIndex2;
	int							 m_TextureIndex3;

};


#endif
