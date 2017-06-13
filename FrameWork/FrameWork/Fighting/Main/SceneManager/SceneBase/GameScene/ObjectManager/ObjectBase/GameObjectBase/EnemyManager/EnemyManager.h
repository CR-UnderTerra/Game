#ifndef ENEMYMANAGER_H
#define ENEMYMANAGER_H
#include <vector>
#include "../GameObjectBase.h"
#include "Animation/AnimUvController.h"
#include "Enemy/Enemy.h"
#include "Singleton.h"
#include "../../../../../GameDataManager/GameDataManager.h"

class EnemyManager : public ObjectBase
{
	friend Lib::Singleton<EnemyManager>;
public:
	/**
	* 初期化処理
	* @param[in] _textureIndex 使用するテクスチャのインデックス
	*/
	void Init(int _textureIndex);

	/**
	* 敵の配置用csvを読み込む関数
	*/
	void EnemyLoad(const char*);

	/**
	* 制御関数
	*/
	void Update() override;

	/**
	* 描画関数
	*/
	void Draw() override;

	static const int		m_EnemyMax; //!< 敵の最大出現数.

private:
	/**
	* コンストラクタ
	*/
	EnemyManager() = default;

	/**
	* デストラクタ
	*/
	~EnemyManager();


	int							   m_TextureIndex;
	std::vector<Enemy*>			   m_pEnemy;
	Lib::Vertex2D*				   m_pVertex;
	Lib::AnimUvController*		   m_pUvController;
	Lib::AnimUvController*		   m_pAnimUvController;
								   
	int 						   m_EnemyLoad[ENEMYCOLUMN][ENEMYROW];
	int							   m_SetEnemyLoad[ENEMYCOLUMN][ENEMYROW];

	static const D3DXVECTOR2 m_Rect;

	D3DXVECTOR2					   m_PosCenter;
	D3DXVECTOR2					   m_PosRight;
	D3DXVECTOR2					   m_PosLeft;

	float						   m_LeftEnemyCrowdAlfa;
	float						   m_CenterEnemyCrowdAlfa;
	float						   m_RightEnemyCrowdAlfa;
};

#endif // !ENEMYMANAGER_H