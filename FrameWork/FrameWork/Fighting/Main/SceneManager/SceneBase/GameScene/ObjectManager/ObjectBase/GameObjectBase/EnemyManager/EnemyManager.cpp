#include "EnemyManager.h"
#include "Texture/TextureManager.h"
#include "Window/Window.h"
#include "Dx11/DX11Manager.h"
#include "Enemy/Enemy.h"

const int EnemyManager::m_EnemyMax = 1/*8*/;
const D3DXVECTOR2 EnemyManager::m_Rect = D3DXVECTOR2(256, 256);

EnemyManager::~EnemyManager()
{
	for (int i = m_pEnemy.size() - 1; i >= 0; i--)
	{
		delete m_pEnemy[i];
		m_pEnemy[i] = NULL;
	}

	if (m_pVertex != NULL)
	{
		m_pVertex->Release();
		delete m_pVertex;
		m_pVertex = NULL;
	}

	delete m_pUvController;
	m_pUvController = NULL;

	delete m_pAnimUvController;
	m_pAnimUvController = NULL;

}

void EnemyManager::Init(int _textureIndex)
{
	m_PosCenter = { (960), (576) };
	m_PosRight = { (1160), (576) };
	m_PosLeft = { (760), (576) };

	m_pUvController = new Lib::AnimUvController();
	m_pUvController->LoadAnimation("Resource/test_001.anim", "e_crowd");

	m_pVertex = new Lib::Vertex2D(
		SINGLETON_INSTANCE(Lib::DX11Manager).GetDevice(),
		SINGLETON_INSTANCE(Lib::DX11Manager).GetDeviceContext(),
		SINGLETON_INSTANCE(Lib::Window).GetWindowHandle());
	m_pVertex->Init(&m_Rect, m_pUvController->GetUV());
	m_pVertex->SetTexture(
		SINGLETON_INSTANCE(Lib::TextureManager).GetTexture(m_TextureIndex));

	m_TextureIndex = _textureIndex;
	m_pAnimUvController = new Lib::AnimUvController();
	m_pAnimUvController->LoadAnimation("Resource/test_001.anim", "e_wait");
	//EnemyLoad("Resource/EnemyPos.csv");
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
	m_pVertex->Draw(&m_PosCenter, m_pUvController->GetUV(), 1, &D3DXVECTOR2(0.9f, 0.9f));
	m_pVertex->Draw(&m_PosLeft, m_pUvController->GetUV(), 1, &D3DXVECTOR2(0.9f, 0.9f));
	m_pVertex->Draw(&m_PosRight, m_pUvController->GetUV(), 1, &D3DXVECTOR2(0.9f, 0.9f));

	for (int i = 0; i < m_EnemyMax; i++)
	{
		m_pEnemy[i]->Draw();
	}
}