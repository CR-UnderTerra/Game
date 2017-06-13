/**
 * @file   ObjectManager.h
 * @brief  ObjectManagerクラスのヘッダファイル
 * @author kotani
 */
#ifndef OBJECTMANAGER_H
#define OBJECTMANAGER_H
#include <vector>
#include "ObjectBase/GameObjectBase/GameObjectBase.h"
#include "ObjectBase/UIBase/UIBase.h"
#include "Vertex2D/Vertex2D.h"


class KnifeManager;
class EnemyManager;

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

	GameObjectBase*		 m_pBackGround;
	KnifeManager*		 m_pKnifeManager;
	GameObjectBase*		 m_pPlayer;
	std::vector<UIBase*> m_pUIBase;
	EnemyManager*		 m_pEnemyManager;

	int					 m_TextureIndex1;
	int					 m_TextureIndex2;
	int					 m_TextureIndex3;

};


#endif
