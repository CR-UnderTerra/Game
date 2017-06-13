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
	* ����������
	* @param[in] _textureIndex �g�p����e�N�X�`���̃C���f�b�N�X
	*/
	void Init(int _textureIndex);

	/**
	* �G�̔z�u�pcsv��ǂݍ��ފ֐�
	*/
	void EnemyLoad(const char*);

	/**
	* ����֐�
	*/
	void Update() override;

	/**
	* �`��֐�
	*/
	void Draw() override;

	static const int		m_EnemyMax; //!< �G�̍ő�o����.

private:
	/**
	* �R���X�g���N�^
	*/
	EnemyManager() = default;

	/**
	* �f�X�g���N�^
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