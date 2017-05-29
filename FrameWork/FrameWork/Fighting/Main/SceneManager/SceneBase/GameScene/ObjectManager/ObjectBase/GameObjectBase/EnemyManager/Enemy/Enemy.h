#ifndef ENEMY_H
#define ENEMY_H
#include "../../GameObjectBase.h"
#include "Animation/AnimUvController.h"
#include "Vertex2D/Vertex2D.h"
#include "../../../../../CollisionManager/CollisionData/CollisionData.h"
#include "../../../../../GameDataManager/GameDataManager.h"
//#include "../EnemyManager.h"

#define ENEMYROW		3		//�G�o���p�^�[������
#define ENEMYCOLUMN		13		//�G�o���p�^�[���c��
#define FLASHTIME		6
#define CLEARINTERVAL	50

class Enemy : public GameObjectBase
{
public:
	/**
	* �R���X�g���N�^
	*/
	Enemy(int _textureIndex, Lib::AnimUvController* _pUvController);

	/**
	* �f�X�g���N�^
	*/
	~Enemy();

	/**
	* ����֐�
	*/
	void Update() override;

	/**
	* �`��֐�
	*/
	void Draw() override;

	//Test
	void EnemyLoad(const char*);

	void Hit();

private:
	/**
	* �����蔻�菈��
	*/
	void CollisionControl();

	/**
	* �����蔻��X�V
	*/
	void CollisionUpdate();

	static const D3DXVECTOR2	   m_Rect;
	static int					   m_IndexMax;
	int							   m_TextureIndex;		 //!< �e�N�X�`���̃C���f�b�N�X
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
	CollisionData*				   m_pCenterEnemyCollisionData;	 //!< ���Ԃ̃C���f�b�N�X�ɃZ�b�g����Ă��邩
	CollisionData*				   m_pRightEnemyCollisionData;	 //!< ���Ԃ̃C���f�b�N�X�ɃZ�b�g����Ă��邩
	CollisionData*				   m_pLeftEnemyCollisionData;	 //!< ���Ԃ̃C���f�b�N�X�ɃZ�b�g����Ă��邩
	Lib::Vertex2D*				   m_pVertex;
	Lib::AnimUvController*		   m_pUvController;
	D3DXVECTOR2					   m_PosCenter;
	D3DXVECTOR2					   m_PosRight;
	D3DXVECTOR2					   m_PosLeft;
	int							   m_EnemyLoad[ENEMYCOLUMN][ENEMYROW];

};

#endif // !ENEMY_H