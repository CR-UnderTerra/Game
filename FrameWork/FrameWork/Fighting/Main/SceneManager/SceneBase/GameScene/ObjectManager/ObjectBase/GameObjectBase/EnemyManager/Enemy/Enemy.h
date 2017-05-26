#ifndef ENEMY_H
#define ENEMY_H
#include "../../GameObjectBase.h"
#include "Animation/AnimUvController.h"
#include "Vertex2D/Vertex2D.h"
#include "../../../../../CollisionManager/CollisionData/CollisionData.h"
#include "../../../../../GameDataManager/GameDataManager.h"
//#include "../EnemyManager.h"

#define ENEMYROW		3		//敵出現パターン横列
#define ENEMYCOLUMN		1/*13*/		//敵出現パターン縦列

class Enemy : public GameObjectBase
{
public:
	/**
	* コンストラクタ
	*/
	Enemy(int _textureIndex, Lib::AnimUvController* _pUvController);

	/**
	* デストラクタ
	*/
	~Enemy();

	/**
	* 制御関数
	*/
	void Update() override;

	/**
	* 描画関数
	*/
	void Draw() override;

	//Test
	void EnemyLoad(const char*);

	void Hit();

private:
	/**
	* 当たり判定処理
	*/
	void CollisionControl();

	/**
	* 当たり判定更新
	*/
	void CollisionUpdate();

	static const D3DXVECTOR2	   m_Rect;
	static int					   m_IndexMax;
	int							   m_TextureIndex;		 //!< テクスチャのインデックス
	bool						   m_Hits;
	bool						   m_IsDeath;
	GameDataManager::TARGET		   m_Target;
	CollisionData*				   m_pCollisionData;	 //!< 何番のインデックスにセットされているか
	Lib::Vertex2D*				   m_pVertex;
	Lib::AnimUvController*		   m_pUvController;
	D3DXVECTOR2					   m_PosCenter;
	D3DXVECTOR2					   m_PosRight;
	D3DXVECTOR2					   m_PosLeft;
	int							   m_EnemyLoad[ENEMYCOLUMN][ENEMYROW];

};

#endif // !ENEMY_H