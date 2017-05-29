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
m_EnemyColumn(ENEMYCOLUMN),
m_EnemyRow(ENEMYROW),
m_CenterEnemyCount(12),
m_RightEnemyCount(12),
m_LeftEnemyCount(12),
m_CenterEnemyHits(false),
m_RightEnemyHits(false),
m_LeftEnemyHits(false),
m_CenterCollisionSwitch(false),
m_RightCollisionSwitch(false),
m_LeftCollisionSwitch(false),
m_ClearInterval(0.0f),
m_FlashingCount(0.0f),
m_PosCenter{ (960), (576) }, /*128*/			//敵の出現位置(仮)
m_PosRight{ (1260), (576) },			//敵の出現位置(仮)
m_PosLeft{ (660), (576) }			//敵の出現位置(仮)
{
	/*for (int i = 0; i < ENEMYCOLUMN; i++)
	{
	for (int j = 0; j < ENEMYROW; j++)
	{
	m_EnemyLoad[i][j] = SINGLETON_INSTANCE(EnemyManager).GetEnemyLoad(i, j);
	}
	}*/

	EnemyLoad("Resource/EnemyPos.csv");

	if (m_EnemyLoad[m_LeftEnemyCount][0] == 1)
	{
		m_pLeftEnemyCollisionData = new CollisionData();
		m_pLeftEnemyCollisionData->SetEnable(false);
		m_pLeftEnemyCollisionData->SetCollision(&D3DXVECTOR3(m_PosLeft), &m_Rect, CollisionData::ENEMY_TYPE);
		SINGLETON_INSTANCE(CollisionManager).AddCollision(m_pLeftEnemyCollisionData);

		m_pVertex = new Lib::Vertex2D(
			SINGLETON_INSTANCE(Lib::DX11Manager).GetDevice(),
			SINGLETON_INSTANCE(Lib::DX11Manager).GetDeviceContext(),
			SINGLETON_INSTANCE(Lib::Window).GetWindowHandle());
		m_pVertex->Init(&m_Rect, m_pUvController->GetUV());
		m_pVertex->SetTexture(
			SINGLETON_INSTANCE(Lib::TextureManager).GetTexture(m_TextureIndex));
	}
	else if (m_EnemyLoad[m_CenterEnemyCount][1] == 1)
	{
		m_pCenterEnemyCollisionData = new CollisionData();
		m_pCenterEnemyCollisionData->SetEnable(false);
		m_pCenterEnemyCollisionData->SetCollision(&D3DXVECTOR3(m_PosCenter), &m_Rect, CollisionData::ENEMY_TYPE);
		SINGLETON_INSTANCE(CollisionManager).AddCollision(m_pCenterEnemyCollisionData);

		m_pVertex = new Lib::Vertex2D(
			SINGLETON_INSTANCE(Lib::DX11Manager).GetDevice(),
			SINGLETON_INSTANCE(Lib::DX11Manager).GetDeviceContext(),
			SINGLETON_INSTANCE(Lib::Window).GetWindowHandle());
		m_pVertex->Init(&m_Rect, m_pUvController->GetUV());
		m_pVertex->SetTexture(
			SINGLETON_INSTANCE(Lib::TextureManager).GetTexture(m_TextureIndex));
	}
	else if (m_EnemyLoad[m_RightEnemyCount][2] == 1)
	{
		m_pRightEnemyCollisionData = new CollisionData();
		m_pRightEnemyCollisionData->SetEnable(false);
		m_pRightEnemyCollisionData->SetCollision(&D3DXVECTOR3(m_PosRight), &m_Rect, CollisionData::ENEMY_TYPE);
		SINGLETON_INSTANCE(CollisionManager).AddCollision(m_pRightEnemyCollisionData);

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
	delete m_pCenterEnemyCollisionData;
	m_pCenterEnemyCollisionData = NULL;

	delete m_pLeftEnemyCollisionData;
	m_pLeftEnemyCollisionData = NULL;

	delete m_pRightEnemyCollisionData;
	m_pRightEnemyCollisionData = NULL;

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
	//CollisionUpdate();
	//CollisionControl();

	if (m_CenterEnemyHits == true && m_LeftEnemyHits == true && m_RightEnemyHits == true && m_ClearInterval == CLEARINTERVAL)
	{
		m_CenterEnemyCount -= 1;
		m_LeftEnemyCount -= 1;
		m_RightEnemyCount -= 1;

		m_CenterEnemyHits = false;
		m_LeftEnemyHits = false;
		m_RightEnemyHits = false;
	
	}

	Hit();

	if ( m_CenterEnemyHits == true || m_LeftEnemyHits == true || m_RightEnemyHits == true)
	{

		m_ClearInterval += 1;

		//点滅処理
		m_FlashingCount++;
		if (m_FlashingCount > FLASHTIME)
		{
			if (m_HitFlashing == false)
			{
				m_HitFlashing = true;
			}
			else if (m_HitFlashing == true)
			{
				m_HitFlashing = false;
			}
			m_FlashingCount = 0;
		}		
	}

	/*if (m_ClearInterval == CLEARINTERVAL)
	{
		m_ClearInterval = 0;
	}*/

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

	if (m_CenterEnemyHits == true)
	{
		if (m_FlashingCount != 0)
		{
			if (m_HitFlashing)
			{
				if (m_EnemyLoad[m_CenterEnemyCount][1] == 1)
				{
					m_pVertex->Draw(&m_PosCenter, m_pUvController->GetUV());
				}
			}
			else if (m_HitFlashing == false)
			{
				if (m_EnemyLoad[m_CenterEnemyCount][1] == 1)
				{
					m_pVertex->Draw(&m_PosCenter, m_pUvController->GetUV(), 0);
				}
			}
		}
	}
	else
	{
		if (m_EnemyLoad[m_CenterEnemyCount][1] == 1)
		{
			m_pVertex->Draw(&m_PosCenter, m_pUvController->GetUV());
		}
	}

	if (m_LeftEnemyHits == true)
	{
		if (m_FlashingCount != 0)
		{
			if (m_HitFlashing)
			{
				if (m_EnemyLoad[m_LeftEnemyCount][0] == 1)
				{
					m_pVertex->Draw(&m_PosLeft, m_pUvController->GetUV());
				}
			}
			else if (m_HitFlashing == false)
			{
				if (m_EnemyLoad[m_LeftEnemyCount][0] == 1)
				{
					m_pVertex->Draw(&m_PosLeft, m_pUvController->GetUV(), 0);
				}
			}
		}
	}
	else
	{
		if (m_EnemyLoad[m_LeftEnemyCount][0] == 1)
		{
			m_pVertex->Draw(&m_PosLeft, m_pUvController->GetUV());
		}
	}

	if (m_RightEnemyHits == true)
	{
		if (m_FlashingCount != 0)
		{
			if (m_HitFlashing)
			{
				if (m_EnemyLoad[m_RightEnemyCount][2] == 1)
				{
					m_pVertex->Draw(&m_PosRight, m_pUvController->GetUV());
				}
			}
			else if (m_HitFlashing == false)
			{
				if (m_EnemyLoad[m_RightEnemyCount][2] == 1)
				{
					m_pVertex->Draw(&m_PosRight, m_pUvController->GetUV(), 0);
				}
			}
		}
	}
	else
	{
		if (m_EnemyLoad[m_RightEnemyCount][2] == 1)
		{
			m_pVertex->Draw(&m_PosRight, m_pUvController->GetUV());
		}
	}
	
	/*if (m_EnemyLoad[m_CenterEnemyCount][1] == 1)
	{
		m_pVertex->Draw(&m_PosCenter, m_pUvController->GetUV());
	}

	if (m_EnemyLoad[m_LeftEnemyCount][0] == 1)
	{
		m_pVertex->Draw(&m_PosLeft, m_pUvController->GetUV());
	}

	if (m_EnemyLoad[m_RightEnemyCount][2] == 1)
	{
		m_pVertex->Draw(&m_PosRight, m_pUvController->GetUV());
	}*/
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
	//m_pCenterEnemyCollisionData->SetEnable(true);

	m_Target = GameDataManager::FRONT_ENEMY_TARGET;

	D3DXVECTOR2 pos = SINGLETON_INSTANCE(GameDataManager).GetPos(m_Target);

	SINGLETON_INSTANCE(Lib::KeyDevice).KeyCheck(DIK_1);
	SINGLETON_INSTANCE(Lib::KeyDevice).KeyCheck(DIK_2);
	SINGLETON_INSTANCE(Lib::KeyDevice).KeyCheck(DIK_3);

	if (SINGLETON_INSTANCE(Lib::KeyDevice).GetKeyState()[DIK_1] == Lib::KEY_ON /*&& m_EnemyLoad[m_LeftEnemyCount][1] == 1*/)
	{
		m_LeftEnemyHits = true;
	}
	if (SINGLETON_INSTANCE(Lib::KeyDevice).GetKeyState()[DIK_2] == Lib::KEY_ON /*&& m_EnemyLoad[m_CenterEnemyCount][1] == 1*/)
	{
		m_CenterEnemyHits = true;
	}
	if (SINGLETON_INSTANCE(Lib::KeyDevice).GetKeyState()[DIK_3] == Lib::KEY_ON /*&& m_EnemyLoad[m_RightEnemyCount][1] == 1*/)
	{
		m_RightEnemyHits = true;
	}

	if (m_CenterEnemyHits == true && m_ClearInterval == CLEARINTERVAL)
	{
		m_ClearInterval = 0;
		m_EnemyLoad[m_CenterEnemyCount][1] = 0;
	}
	if (m_LeftEnemyHits == true && m_ClearInterval == CLEARINTERVAL)
	{
		m_ClearInterval = 0;
		m_EnemyLoad[m_LeftEnemyCount][0] = 0;
	}
	if (m_RightEnemyHits == true && m_ClearInterval == CLEARINTERVAL)
	{
		m_ClearInterval = 0;
		m_EnemyLoad[m_RightEnemyCount][2] = 0;
	}

}

void Enemy::CollisionUpdate()
{
}

void Enemy::CollisionControl()
{
	CollisionData::HIT_STATE hitState = m_pCenterEnemyCollisionData->GetCollisionState().HitState;
	if (hitState == CollisionData::KNIFE_HIT)
	{
		m_pCenterEnemyCollisionData->SetEnable(false);
	}
}
