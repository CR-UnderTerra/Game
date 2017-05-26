#include "EnemyManager.h"
#include "Enemy/Enemy.h"

const int EnemyManager::m_EnemyMax = 1;

EnemyManager::~EnemyManager()
{
	for (int i = m_pEnemy.size() - 1; i >= 0; i--)
	{
		delete m_pEnemy[i];
		m_pEnemy[i] = NULL;
	}

	delete m_pAnimUvController;
	m_pAnimUvController = NULL;

}

void EnemyManager::Init(int _textureIndex)
{
	m_TextureIndex = _textureIndex;
	m_pAnimUvController = new Lib::AnimUvController();
	m_pAnimUvController->LoadAnimation("Resource/test_001.anim", "e_wait");
	//EnemyLoad("Resource/EnemyPos111.csv");
	for (int i = 0; i < m_EnemyMax; i++)
	{
		m_pEnemy.push_back(new Enemy(_textureIndex, m_pAnimUvController));
	}
}

//void EnemyManager::EnemyLoad(const char* _enemycsv)
//{
//	FILE*  fp;
//	fopen_s(&fp, _enemycsv, "r");
//
//	for (int i = 0; i < ENEMYCOLUMN; i++)
//	{
//		for (int j = 0; j < ENEMYROW; j++)
//		{
//			fscanf_s(fp, "%d,", &m_EnemyLoad[i][j], _countof(m_EnemyLoad));
//			switch (m_EnemyLoad[i][j])
//			{
//			case 1:
//			{
//				for (int i = 0; i < m_EnemyMax; i++)
//				{
//					m_pEnemy.push_back(new Enemy(m_TextureIndex, m_pAnimUvController));
//				}
//			}
//			break;
//			}
//		}
//	}
//}

void EnemyManager::Update()
{
	for (int i = 0; i < m_EnemyMax; i++)
	{
		m_pEnemy[i]->Update();
	}
}

void EnemyManager::Draw()
{
	for (int i = 0; i < m_EnemyMax; i++)
	{
		m_pEnemy[i]->Draw();
	}
}