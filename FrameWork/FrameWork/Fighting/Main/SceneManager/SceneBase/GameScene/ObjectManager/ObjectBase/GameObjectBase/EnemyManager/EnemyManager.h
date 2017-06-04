#ifndef ENEMYMANAGER_H
#define ENEMYMANAGER_H
#include <vector>
#include "../GameObjectBase.h"
#include "Animation/AnimUvController.h"
#include "Enemy/Enemy.h"
#include "Singleton.h"
#include "../../../../../GameDataManager/GameDataManager.h"

#define ENEMYROW		3		//�G�o���p�^�[������
#define ENEMYCOLUMN		1//6/*13*/		//�G�o���p�^�[���c��

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

	//void SetEnemyLoad(int _column, int _row);

	int GetEnemyLoad(int _column, int _row)
	{
		return m_EnemyLoad[_column][_row];
	}

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

};

#endif // !ENEMYMANAGER_H