#include "EnemyManager.h"
#include "Texture/TextureManager.h"
#include "Window/Window.h"
#include "Dx11/DX11Manager.h"
#include "Enemy/Enemy.h"
#include "Event/EventManager.h"
const int EnemyManager::m_EnemyMax = 1/*18*/;
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
	m_PosLeft = { (760), (576) };
	m_PosCenter = { (960), (576) };
	m_PosRight = { (1160), (576) };

	SINGLETON_INSTANCE(Lib::EventManager).AddEvent("EnemyDamage", [this]()
	{
		m_WidthTime = 30;
	});

	m_LeftEnemyCrowdAlfa = SINGLETON_INSTANCE(GameDataManager).GetLeftEnemyCrowdAlfa();
	m_CenterEnemyCrowdAlfa = SINGLETON_INSTANCE(GameDataManager).GetCenterEnemyCrowdAlfa();
	m_LeftEnemyCrowdAlfa = SINGLETON_INSTANCE(GameDataManager).GetRightEnemyCrowdAlfa();

	m_pUvController = new Lib::AnimUvController();
	m_pUvController->LoadAnimation("Resource/test_001.anim", "e_crowd");

	m_pVertex = new Lib::Vertex2D(
		SINGLETON_INSTANCE(Lib::DX11Manager).GetDevice(),
		SINGLETON_INSTANCE(Lib::DX11Manager).GetDeviceContext(),
		SINGLETON_INSTANCE(Lib::Window).GetWindowSize());
	m_pVertex->Init(&m_Rect, m_pUvController->GetUV());
	m_pVertex->SetTexture(
		SINGLETON_INSTANCE(Lib::TextureManager).GetTexture(m_TextureIndex));

	m_TextureIndex = _textureIndex;
	for (int i = 0; i < m_EnemyMax; i++)
	{
		m_pEnemy.push_back(new Enemy(_textureIndex, m_pAnimUvController));
	}
}

void EnemyManager::Update()
{
	for (int i = 0; i < m_EnemyMax; i++)
	{
		m_pEnemy[i]->Update();
	}
}

void EnemyManager::Draw()
{
	Vibration();
	m_pVertex->Draw(&D3DXVECTOR2(m_PosLeft.x + m_WidthVibValue, m_PosLeft.y), m_pUvController->GetUV(), m_LeftEnemyCrowdAlfa, &D3DXVECTOR2(0.9, 0.9));
	m_pVertex->Draw(&D3DXVECTOR2(m_PosCenter.x + m_WidthVibValue, m_PosCenter.y), m_pUvController->GetUV(), m_CenterEnemyCrowdAlfa, &D3DXVECTOR2(0.9, 0.9));
	m_pVertex->Draw(&D3DXVECTOR2(m_PosRight.x + m_WidthVibValue, m_PosRight.y), m_pUvController->GetUV(), m_RightEnemyCrowdAlfa, &D3DXVECTOR2(0.9, 0.9));
	m_LeftEnemyCrowdAlfa = SINGLETON_INSTANCE(GameDataManager).GetLeftEnemyCrowdAlfa();
	m_CenterEnemyCrowdAlfa = SINGLETON_INSTANCE(GameDataManager).GetCenterEnemyCrowdAlfa();
	m_RightEnemyCrowdAlfa = SINGLETON_INSTANCE(GameDataManager).GetRightEnemyCrowdAlfa();

	for (int i = 0; i < m_EnemyMax; i++)
	{
		m_pEnemy[i]->Draw();
	}
}