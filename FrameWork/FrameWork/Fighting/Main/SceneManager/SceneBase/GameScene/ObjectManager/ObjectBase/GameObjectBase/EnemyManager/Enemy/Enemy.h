#ifndef ENEMY_H
#define ENEMY_H
#include "../../GameObjectBase.h"
#include "Animation/AnimUvController.h"
#include "Vertex2D/Vertex2D.h"
#include "../../../../../CollisionManager/CollisionData/CollisionData.h"
#include "../../../../../GameDataManager/GameDataManager.h"
//#include "../EnemyManager.h"

#define ENEMYROW		3		//敵出現パターン横列
#define ENEMYCOLUMN		13		//敵出現パターン縦列
#define FLASHTIME		6
#define CLEARINTERVAL	50

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
	int							   m_EnemyColumn;
	int							   m_EnemyRow;
	int							   m_CenterEnemyCount;
	int							   m_RightEnemyCount;
	int							   m_LeftEnemyCount;

	float						   m_ClearInterval;
	float						   m_FlashingCount;

	bool						   m_CenterEnemyHits;
	bool						   m_RightEnemyHits;
	bool						   m_LeftEnemyHits;

	bool						   m_HitFlashing;
	bool						   m_Hits;

	bool						   m_CenterCollisionSwitch;
	bool						   m_RightCollisionSwitch;
	bool						   m_LeftCollisionSwitch;

	GameDataManager::TARGET		   m_Target;
	CollisionData*				   m_pCenterEnemyCollisionData;	 //!< 何番のインデックスにセットされているか
	CollisionData*				   m_pRightEnemyCollisionData;	 //!< 何番のインデックスにセットされているか
	CollisionData*				   m_pLeftEnemyCollisionData;	 //!< 何番のインデックスにセットされているか
	Lib::Vertex2D*				   m_pVertex;
	Lib::AnimUvController*		   m_pUvController;
	D3DXVECTOR2					   m_PosCenter;
	D3DXVECTOR2					   m_PosRight;
	D3DXVECTOR2					   m_PosLeft;
	int							   m_EnemyLoad[ENEMYCOLUMN][ENEMYROW];

};

#endif // !ENEMY_H