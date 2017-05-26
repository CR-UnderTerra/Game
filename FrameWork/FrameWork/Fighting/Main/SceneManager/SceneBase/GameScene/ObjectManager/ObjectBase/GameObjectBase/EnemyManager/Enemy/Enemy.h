#ifndef ENEMY_H
#define ENEMY_H
#include "../../GameObjectBase.h"
#include "Animation/AnimUvController.h"
#include "Vertex2D/Vertex2D.h"
#include "../../../../../CollisionManager/CollisionData/CollisionData.h"
#include "../../../../../GameDataManager/GameDataManager.h"
//#include "../EnemyManager.h"

#define ENEMYROW		3		//�G�o���p�^�[������
#define ENEMYCOLUMN		1/*13*/		//�G�o���p�^�[���c��

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
	bool						   m_Hits;
	bool						   m_IsDeath;
	GameDataManager::TARGET		   m_Target;
	CollisionData*				   m_pCollisionData;	 //!< ���Ԃ̃C���f�b�N�X�ɃZ�b�g����Ă��邩
	Lib::Vertex2D*				   m_pVertex;
	Lib::AnimUvController*		   m_pUvController;
	D3DXVECTOR2					   m_PosCenter;
	D3DXVECTOR2					   m_PosRight;
	D3DXVECTOR2					   m_PosLeft;
	int							   m_EnemyLoad[ENEMYCOLUMN][ENEMYROW];

};

#endif // !ENEMY_H