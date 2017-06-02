#include "Enemy.h"
#include<time.h>
#include "Window/Window.h"
#include "Dx11/DX11Manager.h"
#include "Animation/AnimUvController.h"
#include "Texture/TextureManager.h"
#include "../../../../../CollisionManager/CollisionManager.h"
#include "DxInput/KeyBoard/KeyDevice.h"
#include "../../KnifeManager/KnifeManager.h"

const D3DXVECTOR2 Enemy::m_Rect = D3DXVECTOR2(128, 256);

Enemy::Enemy(int _textureIndex, Lib::AnimUvController* _pUvController) :
m_pUvController(_pUvController),
m_TextureIndex(_textureIndex),
m_EnemyColumn(ENEMYCOLUMN),
m_EnemyRow(ENEMYROW),
m_LeftEnemyCount(12),
m_CenterEnemyCount(12),
m_RightEnemyCount(12),
m_LeftEnemyHits(false),
m_CenterEnemyHits(false),
m_RightEnemyHits(false),
m_ClearInterval(0.0f),
m_FlashingCount(0.0f),
m_AttackInterval(0.0f),
m_PosLeft{ (760), (576) },			//敵の出現位置(仮)
m_PosCenter{ (960), (576) },		//敵の出現位置(仮)
m_PosRight{ (1160), (576) }			//敵の出現位置(仮)
{
	EnemyLoad("Resource/EnemyPos.csv");

	m_pUvControllerCrush = new Lib::AnimUvController();

	m_pVertexCrush = new Lib::Vertex2D(
		SINGLETON_INSTANCE(Lib::DX11Manager).GetDevice(),
		SINGLETON_INSTANCE(Lib::DX11Manager).GetDeviceContext(),
		SINGLETON_INSTANCE(Lib::Window).GetWindowHandle());
	m_pVertexCrush->Init(&m_Rect, m_pUvControllerCrush->GetUV());
	m_pVertexCrush->SetTexture(
		SINGLETON_INSTANCE(Lib::TextureManager).GetTexture(m_TextureIndex));

	if (m_EnemyLoad[m_LeftEnemyCount][0] == 1)
	{
		EnemyPosInit(m_PosLeft);
	}
	else if (m_EnemyLoad[m_CenterEnemyCount][1] == 1)
	{
		EnemyPosInit(m_PosCenter);
	}
	else if (m_EnemyLoad[m_RightEnemyCount][2] == 1)
	{
		EnemyPosInit(m_PosRight);
	}
	
}

Enemy::~Enemy()
{
	delete m_pCollisionData;
	m_pCollisionData = NULL;

	delete m_pUvControllerCrush;
	m_pUvControllerCrush = NULL;

	if (m_pVertex != NULL)
	{
		m_pVertex->Release();
		delete m_pVertex;
		m_pVertex = NULL;
	}

	if (m_pVertexCrush != NULL)
	{
		m_pVertexCrush->Release();
		delete m_pVertexCrush;
		m_pVertexCrush = NULL;
	}
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

		if (m_EnemyLoad[m_LeftEnemyCount][0] == 1)
		{
			m_LeftEnemyHits = false;
		}
		else if (m_EnemyLoad[m_CenterEnemyCount][1] == 1)
		{
			m_CenterEnemyHits = false;
		}
		else if (m_EnemyLoad[m_RightEnemyCount][2] == 1)
		{
			m_RightEnemyHits = false;
		}
		
	}

	Hit();

	Attack();

	if ( m_CenterEnemyHits == true || m_LeftEnemyHits == true || m_RightEnemyHits == true)
	{

		m_ClearInterval += 1.0f;

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
			if (m_HitFlashing == true)
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
		EnemyCrush(m_PosCenter, 1);
	}
	else
	{
		if (m_EnemyLoad[m_CenterEnemyCount][1] == 1)
		{
			m_pVertex->Draw(&m_PosCenter, m_pUvController->GetUV());
			EnemyCrush(m_PosCenter, 0.f);
		}
	}

	if (m_LeftEnemyHits == true)
	{

		if (m_FlashingCount != 0)
		{
			if (m_HitFlashing == true)
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
		EnemyCrush(m_PosLeft, 1);
	}
	else
	{
		if (m_EnemyLoad[m_LeftEnemyCount][0] == 1)
		{
			m_pVertex->Draw(&m_PosLeft, m_pUvController->GetUV());
			EnemyCrush(m_PosCenter, 0.f);
		}
	}

	if (m_RightEnemyHits == true)
	{

		if (m_FlashingCount != 0)
		{
			if (m_HitFlashing == true)
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
		EnemyCrush(m_PosRight, 1);
	}
	else
	{
		if (m_EnemyLoad[m_RightEnemyCount][2] == 1)
		{
			m_pVertex->Draw(&m_PosRight, m_pUvController->GetUV());
			EnemyCrush(m_PosRight, 0.f);
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

	if (SINGLETON_INSTANCE(Lib::KeyDevice).GetKeyState()[DIK_1] == Lib::KEY_ON)
	{
		m_LeftEnemyHits = true;
	}
	if (SINGLETON_INSTANCE(Lib::KeyDevice).GetKeyState()[DIK_2] == Lib::KEY_ON)
	{
		m_CenterEnemyHits = true;
	}
	if (SINGLETON_INSTANCE(Lib::KeyDevice).GetKeyState()[DIK_3] == Lib::KEY_ON )
	{
		m_RightEnemyHits = true;
	}

	if (m_CenterEnemyHits == true && m_ClearInterval == CLEARINTERVAL)
	{
		m_ClearInterval = 0;
		m_EnemyLoad[m_CenterEnemyCount][1] = 0;
		EnemyCrush(m_PosCenter, 100.f);
	}
	if (m_LeftEnemyHits == true && m_ClearInterval == CLEARINTERVAL)
	{
		m_ClearInterval = 0;
		m_EnemyLoad[m_LeftEnemyCount][0] = 0;
		EnemyCrush(m_PosLeft, 0.f);
	}
	if (m_RightEnemyHits == true && m_ClearInterval == CLEARINTERVAL)
	{
		m_ClearInterval = 0;
		m_EnemyLoad[m_RightEnemyCount][2] = 0;
		EnemyCrush(m_PosRight, 0.f);
	}

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
	}
}

void Enemy::EnemyPosInit(D3DXVECTOR2 _pos)
{
	m_pCollisionData = new CollisionData();
	m_pCollisionData->SetEnable(false);
	m_pCollisionData->SetCollision(&D3DXVECTOR3(_pos), &m_Rect, CollisionData::ENEMY_TYPE);
	SINGLETON_INSTANCE(CollisionManager).AddCollision(m_pCollisionData);

	m_pVertex = new Lib::Vertex2D(
		SINGLETON_INSTANCE(Lib::DX11Manager).GetDevice(),
		SINGLETON_INSTANCE(Lib::DX11Manager).GetDeviceContext(),
		SINGLETON_INSTANCE(Lib::Window).GetWindowHandle());
	m_pVertex->Init(&m_Rect, m_pUvController->GetUV());
	m_pVertex->SetTexture(
		SINGLETON_INSTANCE(Lib::TextureManager).GetTexture(m_TextureIndex));
}

void Enemy::EnemyCrush(D3DXVECTOR2 _pos, float _alpha)
{
	m_pUvControllerCrush->LoadAnimation("Resource/test_001.anim", "e_bom_a");
	m_pVertexCrush->Draw(&_pos, m_pUvControllerCrush->GetUV(), _alpha);
}

void Enemy::Attack()
{
	SINGLETON_INSTANCE(Lib::KeyDevice).KeyCheck(DIK_A);
	SINGLETON_INSTANCE(Lib::KeyDevice).KeyCheck(DIK_S);
	SINGLETON_INSTANCE(Lib::KeyDevice).KeyCheck(DIK_D);

	srand((unsigned int)time(NULL));

	int Random = rand() % 3 + 1;

	m_AttackInterval += 1.0f;

	if (m_AttackInterval > ATTACKINTERVAL)
	{
		m_Action = THROW;
		switch (Random)
		{			
		case 1:
			if (m_Action == THROW)
			{
				SINGLETON_INSTANCE(KnifeManager).
					ThrowKnife(&D3DXVECTOR2(*m_PosLeft, 576), GameDataManager::PLAYER_TARGET, 1);
				m_Action = WAIT;
			}
			break;
		case 2:
			if (m_Action == THROW)
			{
				SINGLETON_INSTANCE(KnifeManager).
					ThrowKnife(&D3DXVECTOR2(*m_PosCenter, 576), GameDataManager::PLAYER_TARGET, 1);
				m_Action = WAIT;
			}
			break;
		case 3:
			if (m_Action == THROW)
			{
				SINGLETON_INSTANCE(KnifeManager).
					ThrowKnife(&D3DXVECTOR2(*m_PosRight, 576), GameDataManager::PLAYER_TARGET, 1);
				m_Action = WAIT;
			}
			break;
		}
			m_AttackInterval = 0;
	}

	/*if (SINGLETON_INSTANCE(Lib::KeyDevice).GetKeyState()[DIK_A] == Lib::KEY_PUSH)
	{
		SINGLETON_INSTANCE(KnifeManager).
			ThrowKnife(&D3DXVECTOR2(*m_PosLeft, 440), GameDataManager::PLAYER_TARGET, 1);
	}
	else if (SINGLETON_INSTANCE(Lib::KeyDevice).GetKeyState()[DIK_S] == Lib::KEY_PUSH)
	{
		SINGLETON_INSTANCE(KnifeManager).
			ThrowKnife(&D3DXVECTOR2(*m_PosCenter, 440), GameDataManager::PLAYER_TARGET, 1);
	}
	else if (SINGLETON_INSTANCE(Lib::KeyDevice).GetKeyState()[DIK_D] == Lib::KEY_PUSH)
	{
		SINGLETON_INSTANCE(KnifeManager).
			ThrowKnife(&D3DXVECTOR2(*m_PosRight, 440), GameDataManager::PLAYER_TARGET, 1);
	}*/
}