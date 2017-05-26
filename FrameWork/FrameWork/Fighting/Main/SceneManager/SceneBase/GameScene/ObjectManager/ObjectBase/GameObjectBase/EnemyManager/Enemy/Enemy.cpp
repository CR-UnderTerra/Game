#include "Enemy.h"
#include "Window/Window.h"
#include "Dx11/DX11Manager.h"
#include "Animation/AnimUvController.h"
#include "Texture/TextureManager.h"
#include "../../../../../CollisionManager/CollisionManager.h"
#include "DxInput/KeyBoard/KeyDevice.h"
//#include "../EnemyManager.h"

const D3DXVECTOR2 Enemy::m_Rect = D3DXVECTOR2(128, 256);

Enemy::Enemy(int _textureIndex, Lib::AnimUvController* _pUvController) :
m_pUvController(_pUvController),
m_TextureIndex(_textureIndex),
m_Hits(false),
m_IsDeath(false),
m_PosCenter{ (640), (128) },			//敵の出現位置(仮)
m_PosRight{ (840), (128) },			//敵の出現位置(仮)
m_PosLeft{ (440), (128) }			//敵の出現位置(仮)
{
	/*for (int i = 0; i < ENEMYCOLUMN; i++)
	{
	for (int j = 0; j < ENEMYROW; j++)
	{
	m_EnemyLoad[i][j] = SINGLETON_INSTANCE(EnemyManager).GetEnemyLoad(i, j);
	}
	}*/

	EnemyLoad("Resource/EnemyPos.csv");

	if (m_EnemyLoad[0][1] == 1)
	{
		m_pCollisionData = new CollisionData();
		m_pCollisionData->SetEnable(false);
		m_pCollisionData->SetCollision(&D3DXVECTOR3(m_PosCenter), &m_Rect, CollisionData::ENEMY_TYPE);
		SINGLETON_INSTANCE(CollisionManager).AddCollision(m_pCollisionData);

		m_pVertex = new Lib::Vertex2D(
			SINGLETON_INSTANCE(Lib::DX11Manager).GetDevice(),
			SINGLETON_INSTANCE(Lib::DX11Manager).GetDeviceContext(),
			SINGLETON_INSTANCE(Lib::Window).GetWindowHandle());
		m_pVertex->Init(&m_Rect, m_pUvController->GetUV());
		m_pVertex->SetTexture(
			SINGLETON_INSTANCE(Lib::TextureManager).GetTexture(m_TextureIndex));
	}
	else if (m_EnemyLoad[0][0] == 1)
	{
		m_pCollisionData = new CollisionData();
		m_pCollisionData->SetEnable(false);
		m_pCollisionData->SetCollision(&D3DXVECTOR3(m_PosLeft), &m_Rect, CollisionData::ENEMY_TYPE);
		SINGLETON_INSTANCE(CollisionManager).AddCollision(m_pCollisionData);

		m_pVertex = new Lib::Vertex2D(
			SINGLETON_INSTANCE(Lib::DX11Manager).GetDevice(),
			SINGLETON_INSTANCE(Lib::DX11Manager).GetDeviceContext(),
			SINGLETON_INSTANCE(Lib::Window).GetWindowHandle());
		m_pVertex->Init(&m_Rect, m_pUvController->GetUV());
		m_pVertex->SetTexture(
			SINGLETON_INSTANCE(Lib::TextureManager).GetTexture(m_TextureIndex));
	}
	else if (m_EnemyLoad[0][2] == 1)
	{
		m_pCollisionData = new CollisionData();
		m_pCollisionData->SetEnable(false);
		m_pCollisionData->SetCollision(&D3DXVECTOR3(m_PosRight), &m_Rect, CollisionData::ENEMY_TYPE);
		SINGLETON_INSTANCE(CollisionManager).AddCollision(m_pCollisionData);

		m_pVertex = new Lib::Vertex2D(
			SINGLETON_INSTANCE(Lib::DX11Manager).GetDevice(),
			SINGLETON_INSTANCE(Lib::DX11Manager).GetDeviceContext(),
			SINGLETON_INSTANCE(Lib::Window).GetWindowHandle());
		m_pVertex->Init(&m_Rect, m_pUvController->GetUV());
		m_pVertex->SetTexture(
			SINGLETON_INSTANCE(Lib::TextureManager).GetTexture(m_TextureIndex));
	}

}

Enemy::~Enemy()
{
	delete m_pCollisionData;
	m_pCollisionData = NULL;

	if (m_pVertex != NULL)
	{
		m_pVertex->Release();
		delete m_pVertex;
		m_pVertex = NULL;
	}

	//SINGLETON_DELETE(EnemyManager);

}

void Enemy::Update()
{
	CollisionUpdate();
	CollisionControl();
}

void Enemy::Draw()
{
	//m_pVertex->Draw(&m_PosCenter, m_pUvController->GetUV());

	//SINGLETON_INSTANCE(Lib::KeyDevice).KeyCheck(DIK_W);

	/*if (SINGLETON_INSTANCE(Lib::KeyDevice).GetKeyState()[DIK_W] == Lib::KEY_ON)
	{
	m_pUvController->LoadAnimation("Resource/test_001/test_001.anim", "e_attack");
	}
	else
	{
	m_pUvController->LoadAnimation("Resource/test_001/test_001.anim", "e_wait");
	}*/

	if (m_EnemyLoad[0][1] == 1)
	{
		m_pVertex->Draw(&m_PosCenter, m_pUvController->GetUV());
	}

	if (m_EnemyLoad[0][0] == 1)
	{
		m_pVertex->Draw(&m_PosLeft, m_pUvController->GetUV());
	}

	if (m_EnemyLoad[0][2] == 1)
	{
		m_pVertex->Draw(&m_PosRight, m_pUvController->GetUV());
	}
}

void Enemy::EnemyLoad(const char* _enemycsv)
{
	FILE*  fp;
	fopen_s(&fp, _enemycsv, "r");

	for (int i = 0; i < ENEMYCOLUMN; i++)
	{
		for (int j = 0; j < ENEMYROW; j++)
		{
			fscanf_s(fp, "%d,", &m_EnemyLoad[i][j], _countof(m_EnemyLoad));
		}
	}
}

void Enemy::Hit()
{
	m_pCollisionData->SetEnable(true);

	m_Target = GameDataManager::FRONT_ENEMY_TARGET;

	D3DXVECTOR2 pos = SINGLETON_INSTANCE(GameDataManager).GetPos(m_Target);

}

void Enemy::CollisionUpdate()
{
}

void Enemy::CollisionControl()
{
	CollisionData::HIT_STATE hitState = m_pCollisionData->GetCollisionState().HitState;
	if (hitState == CollisionData::KNIFE_HIT)
	{
		m_pCollisionData->SetEnable(false);
		m_IsDeath = true;
	}
}
