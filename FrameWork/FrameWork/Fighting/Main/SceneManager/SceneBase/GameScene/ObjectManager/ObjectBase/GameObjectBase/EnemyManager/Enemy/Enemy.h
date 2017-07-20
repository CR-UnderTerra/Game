#ifndef ENEMY_H
#define ENEMY_H
#include "../../GameObjectBase.h"
#include "Animation/AnimUvController.h"
#include "Vertex2D/Vertex2D.h"
#include "../../../../../CollisionManager/CollisionData/CollisionData.h"
#include "../../../../../../GameDataManager/GameDataManager.h"

#define ENEMYROW		 3		//敵出現パターン横列
#define ENEMYCOLUMN		 21		//敵出現パターン縦列
#define HITINTERVAL		 30.f
#define ATTACKINTERVAL	 100.f
#define ATTACKTIME		 30.f
#define FIRSTATTACKTIME	 30
#define SECONDATTACKTIME 80
#define THIRDATTACKTIME	 130

class Enemy : public GameObjectBase
{
public:
	enum EXPLOSION_TYPE
	{
		GOOD_EXPLOSION,
		AMAZING_EXPLOSION,
		FANTASTIC_EXPLOSION,
		EXPLOSION_MAX
	};

	enum ATTACK_ENEMY
	{
		LEFT_ENEMY_ATTACK,
		CENTER_ENEMY_ATTACK,
		RIGHT_ENEMY_ATTACK,
		NOT_ENEMY_ATTACK,
		ENEMY_ATTACK_MAX
	};

	enum ATTACK_TURN
	{
		FIRST_ATTACK,
		SECOND_ATTACK,
		THIRD_ATTACK,
		ATTACK_MAX,
	};

	/*struct ENEMYSTATE
	{
	D3DXVECTOR2				 Position;
	CollisionData*			 CollisionData;
	Lib::Vertex2D*			 Vertex;
	Lib::AnimUvController*   UvController;
	bool					 Hits;
	ENEMY_ACTION			 EnemyAction;
	ATTACK_ENEMY			 AttackEnemy;
	CollisionData::HIT_STATE HitState;
	};*/

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

	//Enemyの配置用CSVの読み込み関数
	void EnemyLoad(const char*);

	//Enemyの初期化関数
	void EnemyPosInit(CollisionData** _pcollisiondata, D3DXVECTOR2 _pos, Lib::Vertex2D** _vertex, CollisionData::HIT_STATE _hitstate);

	void EnemyWaitUvInit(int random_);

	void EnemyAttackUvInit(int random_);

	void EnemyExplosionUvInit();

	void EnemyDrawInit(bool enemyhit_, bool enemyattack_, int random_, Lib::Vertex2D** vertex_, D3DXVECTOR2 pos_);

	//爆風の描画用関数
	void EnemyExplosionDraw(D3DXVECTOR2 _pos, float _alpha, EXPLOSION_TYPE explosiontype_);

	void Hit();

	void Attack();

	ATTACK_TURN AttackTurn(int column_, int _row);

	float ThrowSpeed(int _column, int _row);

private:
	/**
	* 当たり判定処理
	*/
	void CollisionControl();

	static const D3DXVECTOR2	   m_Rect;
	static int					   m_IndexMax;
	int							   m_TextureIndex;		 //!< テクスチャのインデックス
	int							   m_LeftEnemyCount;
	int							   m_CenterEnemyCount;
	int							   m_RightEnemyCount;

	float						   m_HitInterval;

	bool						   m_LeftEnemyHits;
	bool						   m_CenterEnemyHits;
	bool						   m_RightEnemyHits;

	bool						   m_HitFlashing;
	bool						   m_Hits;

	CollisionData*				   m_pLeftEnemyCollisionData;
	CollisionData*				   m_pCenterEnemyCollisionData;
	CollisionData*				   m_pRightEnemyCollisionData;
	Lib::Vertex2D*				   m_pLeftEnemyVertex;
	Lib::Vertex2D*				   m_pCenterEnemyVertex;
	Lib::Vertex2D*				   m_pRightEnemyVertex;
	Lib::Vertex2D*				   m_pEnemyExplosionVertex;
	Lib::Vertex2D*				   m_pEnemyGoodExplosionVertex;
	Lib::Vertex2D*				   m_pEnemyAmazingExplosionVertex;
	Lib::Vertex2D*				   m_pEnemyFantasticExplosionVertex;
	Lib::AnimUvController*		   m_pWaitUvController;
	Lib::AnimUvController*		   m_pAttackUvController;
	Lib::AnimUvController*		   m_pEnemyExplosionUvController;
	Lib::AnimUvController*		   m_pEnemyGoodExplosionUvController;
	Lib::AnimUvController*		   m_pEnemyAmazingExplosionUvController;
	Lib::AnimUvController*		   m_pEnemyFantasticExplosionUvController;
	D3DXVECTOR2					   m_PosLeft;
	D3DXVECTOR2					   m_PosCenter;
	D3DXVECTOR2					   m_PosRight;
	int							   m_EnemyLoad[ENEMYCOLUMN][ENEMYROW];

	ATTACK_ENEMY				   m_AttackEnemy;
	bool						   m_LeftEnemyAttack;
	bool						   m_CenterEnemyAttack;
	bool						   m_RightEnemyAttack;
	float						   m_AttackInterval;
	float						   m_AttackTime;

	CollisionData::HIT_STATE	   m_LeftEnemyHitState;
	CollisionData::HIT_STATE	   m_CenterEnemyHitState;
	CollisionData::HIT_STATE	   m_RightEnemyHitState;

	float						   m_LeftEnemyCrowdAlfa;
	float						   m_CenterEnemyCrowdAlfa;
	float						   m_RightEnemyCrowdAlfa;
	float						   m_WaitEnemyAlfa;
	float						   m_AttackEnemyAlfa;

	float						   m_ThrowSpeed;
	float						   m_ExplosionTime;
	bool						   m_IsLeftEnemyExplosion;
	bool						   m_IsCenterEnemyExplosion;
	bool						   m_IsRightEnemyExplosion;

	bool						   m_GoodHit;
	bool						   m_AmazingHit;
	bool						   m_FantasticHit;

	int							    m_GoodExplosionSound;
	int							    m_AmazingAndFantasticExplosionSound;
	int							    m_DamageVoiceType01;
	int							    m_DamageVoiceType02;
	int							    m_DamageVoiceType03;
	int								m_ThrowSound;
	
	int								m_Random1;
	int								m_Random2;
	int								m_Random3;
};

#endif // !ENEMY_H