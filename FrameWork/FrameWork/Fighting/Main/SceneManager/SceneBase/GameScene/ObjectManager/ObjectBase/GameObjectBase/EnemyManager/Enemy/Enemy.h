#ifndef ENEMY_H
#define ENEMY_H
#include "../../GameObjectBase.h"
#include "Animation/AnimUvController.h"
#include "Vertex2D/Vertex2D.h"
#include "../../../../../CollisionManager/CollisionData/CollisionData.h"
#include "../../../../../../GameDataManager/GameDataManager.h"
//#include "../EnemyManager.h"

#define ENEMYROW		3		//敵出現パターン横列
#define ENEMYCOLUMN		13		//敵出現パターン縦列
#define FLASHTIME		6
#define CLEARINTERVAL	50
#define ATTACKINTERVAL	100

class Enemy : public GameObjectBase
{
public:
	enum ENEMYACTION
	{
		WAIT,
		THROW,
		ACTION_MAX
	};

	enum ATTACKENEMY
	{
		LEFT_ENEMY,
		CENTER_ENEMY,
		RIGHT_ENEMY,
	};

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

	void EnemyPosInit(D3DXVECTOR2 _pos);

	void EnemyCrush(D3DXVECTOR2 _pos, float _alpha);

	void Attack();

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
	int							   m_EnemyColumn;
	int							   m_EnemyRow;
	int							   m_LeftEnemyCount;
	int							   m_CenterEnemyCount;
	int							   m_RightEnemyCount;

	float						   m_ClearInterval;
	float						   m_FlashingCount;

	bool						   m_LeftEnemyHits;
	bool						   m_CenterEnemyHits;
	bool						   m_RightEnemyHits;

	bool						   m_HitFlashing;
	bool						   m_Hits;

	GameDataManager::TARGET		   m_Target;
	CollisionData*				   m_pCollisionData;
	Lib::Vertex2D*				   m_pVertex;
	Lib::Vertex2D*				   m_pVertexCrush;
	Lib::AnimUvController*		   m_pUvController;
	Lib::AnimUvController*		   m_pUvControllerCrush;
	D3DXVECTOR2					   m_PosLeft;
	D3DXVECTOR2					   m_PosCenter;
	D3DXVECTOR2					   m_PosRight;
	int							   m_EnemyLoad[ENEMYCOLUMN][ENEMYROW];

	ENEMYACTION					   m_Action;
	ATTACKENEMY					   m_AttackEnemy;
	float						   m_AttackInterval;

};

#endif // !ENEMY_H