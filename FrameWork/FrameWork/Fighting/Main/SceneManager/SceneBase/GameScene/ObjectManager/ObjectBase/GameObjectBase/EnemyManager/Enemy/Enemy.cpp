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
m_HitInterval(0.0f),
m_FlashingCount(0.0f),
m_AttackInterval(0.0f),
m_PosLeft{ (760), (576) },			//敵の出現位置(仮)
m_PosCenter{ (960), (576) },		//敵の出現位置(仮)
m_PosRight{ (1160), (576) }			//敵の出現位置(仮)
{
	EnemyLoad("Resource/EnemyPos.csv");

	m_pEnemyExplosionUvController = new Lib::AnimUvController();

	m_pEnemyExplosionVertex = new Lib::Vertex2D(
		SINGLETON_INSTANCE(Lib::DX11Manager).GetDevice(),
		SINGLETON_INSTANCE(Lib::DX11Manager).GetDeviceContext(),
		SINGLETON_INSTANCE(Lib::Window).GetWindowHandle());
	m_pEnemyExplosionVertex->Init(&m_Rect, m_pEnemyExplosionUvController->GetUV());
	m_pEnemyExplosionVertex->SetTexture(
		SINGLETON_INSTANCE(Lib::TextureManager).GetTexture(m_TextureIndex));

	if (m_EnemyLoad[m_LeftEnemyCount][0] == 1)
	{
		m_pLeftEnemyCollisionData = new CollisionData();
		m_pLeftEnemyCollisionData->SetEnable(true);
		m_pLeftEnemyCollisionData->SetCollision(&D3DXVECTOR3(m_PosLeft), &m_Rect, CollisionData::ENEMY_TYPE);
		SINGLETON_INSTANCE(CollisionManager).AddCollision(m_pLeftEnemyCollisionData);

		m_pLeftEnemyVertex = new Lib::Vertex2D(
			SINGLETON_INSTANCE(Lib::DX11Manager).GetDevice(),
			SINGLETON_INSTANCE(Lib::DX11Manager).GetDeviceContext(),
			SINGLETON_INSTANCE(Lib::Window).GetWindowHandle());
		m_pLeftEnemyVertex->Init(&m_Rect, m_pUvController->GetUV());
		m_pLeftEnemyVertex->SetTexture(
			SINGLETON_INSTANCE(Lib::TextureManager).GetTexture(m_TextureIndex));
		m_LeftEnemyHitState = m_pLeftEnemyCollisionData->GetCollisionState().HitState;

		//EnemyPosInit(m_pLeftEnemyCollisionData, m_PosLeft, m_pLeftEnemyVertex, m_LeftEnemyHitState);
	}
	
	if (m_EnemyLoad[m_CenterEnemyCount][1] == 1)
	{
		m_pCenterEnemyCollisionData = new CollisionData();
		m_pCenterEnemyCollisionData->SetEnable(true);
		m_pCenterEnemyCollisionData->SetCollision(&D3DXVECTOR3(m_PosCenter), &m_Rect, CollisionData::ENEMY_TYPE);
		SINGLETON_INSTANCE(CollisionManager).AddCollision(m_pCenterEnemyCollisionData);

		m_pCenterEnemyVertex = new Lib::Vertex2D(
			SINGLETON_INSTANCE(Lib::DX11Manager).GetDevice(),
			SINGLETON_INSTANCE(Lib::DX11Manager).GetDeviceContext(),
			SINGLETON_INSTANCE(Lib::Window).GetWindowHandle());
		m_pCenterEnemyVertex->Init(&m_Rect, m_pUvController->GetUV());
		m_pCenterEnemyVertex->SetTexture(
			SINGLETON_INSTANCE(Lib::TextureManager).GetTexture(m_TextureIndex));
		m_CenterEnemyHitState = m_pCenterEnemyCollisionData->GetCollisionState().HitState;
		
		//EnemyPosInit(m_pCenterEnemyCollisionData, m_PosCenter, m_pCenterEnemyVertex, m_CenterEnemyHitState);
	}
	
	if (m_EnemyLoad[m_RightEnemyCount][2] == 1)
	{
		m_pRightEnemyCollisionData = new CollisionData();
		m_pRightEnemyCollisionData->SetEnable(true);
		m_pRightEnemyCollisionData->SetCollision(&D3DXVECTOR3(m_PosRight), &m_Rect, CollisionData::ENEMY_TYPE);
		SINGLETON_INSTANCE(CollisionManager).AddCollision(m_pRightEnemyCollisionData);

		m_pRightEnemyVertex = new Lib::Vertex2D(
			SINGLETON_INSTANCE(Lib::DX11Manager).GetDevice(),
			SINGLETON_INSTANCE(Lib::DX11Manager).GetDeviceContext(),
			SINGLETON_INSTANCE(Lib::Window).GetWindowHandle());
		m_pRightEnemyVertex->Init(&m_Rect, m_pUvController->GetUV());
		m_pRightEnemyVertex->SetTexture(
			SINGLETON_INSTANCE(Lib::TextureManager).GetTexture(m_TextureIndex));
		m_RightEnemyHitState = m_pRightEnemyCollisionData->GetCollisionState().HitState;
	
		//EnemyPosInit(m_pRightEnemyCollisionData, m_PosRight, m_pRightEnemyVertex, m_RightEnemyHitState);
	}
	
}

Enemy::~Enemy()
{
	delete m_pLeftEnemyCollisionData;
	m_pLeftEnemyCollisionData = NULL;

	delete m_pCenterEnemyCollisionData;
	m_pCenterEnemyCollisionData = NULL;

	delete m_pRightEnemyCollisionData;
	m_pRightEnemyCollisionData = NULL;

	delete m_pEnemyExplosionUvController;
	m_pEnemyExplosionUvController = NULL;

	if (m_pLeftEnemyVertex != NULL)
	{
		m_pLeftEnemyVertex->Release();
		delete m_pLeftEnemyVertex;
		m_pLeftEnemyVertex = NULL;
	}

	if (m_pCenterEnemyVertex != NULL)
	{
		m_pCenterEnemyVertex->Release();
		delete m_pCenterEnemyVertex;
		m_pCenterEnemyVertex = NULL;
	}

	if (m_pRightEnemyVertex != NULL)
	{
		m_pRightEnemyVertex->Release();
		delete m_pRightEnemyVertex;
		m_pRightEnemyVertex = NULL;
	}

	/*if (m_pVertexCrush != NULL)
	{
		m_pVertexCrush->Release();
		delete m_pVertexCrush;
		m_pVertexCrush = NULL;
	}*/
}

void Enemy::Update()
{
	//CollisionUpdate();
	CollisionControl();

	if (m_CenterEnemyHits == true && m_LeftEnemyHits == true && m_RightEnemyHits == true && m_HitInterval == HITINTERVAL)
	{
		m_LeftEnemyCount -= 1;
		m_CenterEnemyCount -= 1;
		m_RightEnemyCount -= 1;

		if (m_EnemyLoad[m_LeftEnemyCount][0] == 1)
		{
			m_LeftEnemyHits = false;
			m_pLeftEnemyCollisionData->SetEnable(true);
		}
		else if (m_EnemyLoad[m_CenterEnemyCount][1] == 1)
		{
			m_CenterEnemyHits = false;
			m_pCenterEnemyCollisionData->SetEnable(true);
		}
		else if (m_EnemyLoad[m_RightEnemyCount][2] == 1)
		{
			m_RightEnemyHits = false;
			m_pRightEnemyCollisionData->SetEnable(true);
		}
		
	}

	Hit();

	Attack();

	if ( m_CenterEnemyHits == true || m_LeftEnemyHits == true || m_RightEnemyHits == true)
	{

		m_HitInterval += 1.0f;

		//点滅処理
		/*m_FlashingCount++;
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
		}*/		
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

		/*if (m_FlashingCount != 0)
		{
			if (m_HitFlashing == true)
			{
				if (m_EnemyLoad[m_CenterEnemyCount][1] == 1)
				{
					m_pCenterEnemyVertex->Draw(&m_PosCenter, m_pUvController->GetUV());
				}
			}
			else if (m_HitFlashing == false)
			{
				if (m_EnemyLoad[m_CenterEnemyCount][1] == 1)
				{
					m_pCenterEnemyVertex->Draw(&m_PosCenter, m_pUvController->GetUV(), 0);
				}
			}
		}*/
		EnemyExplosion(m_PosCenter, 1.f);
	}
	else
	{
		if (m_EnemyLoad[m_CenterEnemyCount][1] == 1)
		{
			m_pCenterEnemyVertex->Draw(&m_PosCenter, m_pUvController->GetUV());
			EnemyExplosion(m_PosCenter, 0.f);
		}
	}

	if (m_LeftEnemyHits == true)
	{

		/*if (m_FlashingCount != 0)
		{
			if (m_HitFlashing == true)
			{
				if (m_EnemyLoad[m_LeftEnemyCount][0] == 1)
				{
					m_pLeftEnemyVertex->Draw(&m_PosLeft, m_pUvController->GetUV());
				}
			}
			else if (m_HitFlashing == false)
			{
				if (m_EnemyLoad[m_LeftEnemyCount][0] == 1)
				{
					m_pLeftEnemyVertex->Draw(&m_PosLeft, m_pUvController->GetUV(), 0);
				}
			}
		}*/
		EnemyExplosion(m_PosLeft, 1);
	}
	else
	{
		if (m_EnemyLoad[m_LeftEnemyCount][0] == 1)
		{
			m_pLeftEnemyVertex->Draw(&m_PosLeft, m_pUvController->GetUV());
			EnemyExplosion(m_PosCenter, 0.f);
		}
	}

	if (m_RightEnemyHits == true)
	{

		/*if (m_FlashingCount != 0)
		{
			if (m_HitFlashing == true)
			{
				if (m_EnemyLoad[m_RightEnemyCount][2] == 1)
				{
					m_pRightEnemyVertex->Draw(&m_PosRight, m_pUvController->GetUV());
				}
			}
			else if (m_HitFlashing == false)
			{
				if (m_EnemyLoad[m_RightEnemyCount][2] == 1)
				{
					m_pRightEnemyVertex->Draw(&m_PosRight, m_pUvController->GetUV(), 0);
				}
			}
		}*/
		EnemyExplosion(m_PosRight, 1.f);
	}
	else
	{
		if (m_EnemyLoad[m_RightEnemyCount][2] == 1)
		{
			m_pRightEnemyVertex->Draw(&m_PosRight, m_pUvController->GetUV());
			EnemyExplosion(m_PosRight, 0.f);
		}
	}
	
	/*if (m_EnemyLoad[m_CenterEnemyCount][1] == 1)
	{
		m_pCenterEnemyVertex->Draw(&m_PosCenter, m_pUvController->GetUV());
	}

	if (m_EnemyLoad[m_LeftEnemyCount][0] == 1)
	{
		m_pLeftEnemyVertex->Draw(&m_PosLeft, m_pUvController->GetUV());
	}

	if (m_EnemyLoad[m_RightEnemyCount][2] == 1)
	{
		m_pRightEnemyVertex->Draw(&m_PosRight, m_pUvController->GetUV());
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

	if (m_CenterEnemyHits == true && m_HitInterval == HITINTERVAL)
	{
		m_HitInterval = 0;
		m_EnemyLoad[m_CenterEnemyCount][1] = 0;
		EnemyExplosion(m_PosCenter, 0.f);
	}
	if (m_LeftEnemyHits == true && m_HitInterval == HITINTERVAL)
	{
		m_HitInterval = 0;
		m_EnemyLoad[m_LeftEnemyCount][0] = 0;
		EnemyExplosion(m_PosLeft, 0.f);
	}
	if (m_RightEnemyHits == true && m_HitInterval == HITINTERVAL)
	{
		m_HitInterval = 0;
		m_EnemyLoad[m_RightEnemyCount][2] = 0;
		EnemyExplosion(m_PosRight, 0.f);
	}

}

void Enemy::CollisionUpdate()
{
}

void Enemy::EnemyPosInit(CollisionData* _pcollisiondata, D3DXVECTOR2 _pos, Lib::Vertex2D* _vertex, CollisionData::HIT_STATE _hitstate)
{
	_pcollisiondata = new CollisionData();
	_pcollisiondata->SetEnable(false);
	_pcollisiondata->SetCollision(&D3DXVECTOR3(_pos), &m_Rect, CollisionData::ENEMY_TYPE);
	SINGLETON_INSTANCE(CollisionManager).AddCollision(_pcollisiondata);

	_vertex = new Lib::Vertex2D(
		SINGLETON_INSTANCE(Lib::DX11Manager).GetDevice(),
		SINGLETON_INSTANCE(Lib::DX11Manager).GetDeviceContext(),
		SINGLETON_INSTANCE(Lib::Window).GetWindowHandle());
	_vertex->Init(&m_Rect, m_pUvController->GetUV());
	_vertex->SetTexture(
		SINGLETON_INSTANCE(Lib::TextureManager).GetTexture(m_TextureIndex));

	_hitstate = _pcollisiondata->GetCollisionState().HitState;

}

void Enemy::CollisionControl()
{
	CollisionData::HIT_STATE m_LeftEnemyHitState = m_pLeftEnemyCollisionData->GetCollisionState().HitState;
	CollisionData::HIT_STATE m_CenterEnemyHitState = m_pCenterEnemyCollisionData->GetCollisionState().HitState;
	CollisionData::HIT_STATE m_RightEnemyHitState = m_pRightEnemyCollisionData->GetCollisionState().HitState;
	
	if (m_LeftEnemyHitState == CollisionData::KNIFE_HIT)
	{
		m_pLeftEnemyCollisionData->SetEnable(false);
		m_LeftEnemyHits = true;
	}
	
	if (m_CenterEnemyHitState == CollisionData::KNIFE_HIT)
	{
		m_pCenterEnemyCollisionData->SetEnable(false);
		m_CenterEnemyHits = true;
	}
	
	if (m_RightEnemyHitState == CollisionData::KNIFE_HIT)
	{
		m_pRightEnemyCollisionData->SetEnable(false);
		m_RightEnemyHits = true;
	}
}

void Enemy::EnemyExplosion(D3DXVECTOR2 _pos, float _alpha)
{
	m_pEnemyExplosionUvController->LoadAnimation("Resource/test_001.anim", "e_bom_a");
	m_pEnemyExplosionVertex->Draw(&_pos, m_pEnemyExplosionUvController->GetUV(), _alpha);
}

void Enemy::Attack()
{
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
				if (m_EnemyLoad[m_LeftEnemyCount][0] == 1)
				{
					SINGLETON_INSTANCE(KnifeManager).
						ThrowKnife(&D3DXVECTOR2(*m_PosLeft, 576), GameDataManager::LEFT_ENEMY_TARGET, GameDataManager::PLAYER_TARGET, 1);
					m_Action = WAIT;
				}
			}
			break;
		case 2:
			if (m_Action == THROW)
			{
				if (m_EnemyLoad[m_CenterEnemyCount][1] == 1)
				{
					SINGLETON_INSTANCE(KnifeManager).
						ThrowKnife(&D3DXVECTOR2(*m_PosCenter, 576), GameDataManager::FRONT_ENEMY_TARGET, GameDataManager::PLAYER_TARGET, 1);
					m_Action = WAIT;
				}				
			}
			break;
		case 3:
			if (m_Action == THROW)
			{
				if (m_EnemyLoad[m_RightEnemyCount][2] == 1)
				{
					SINGLETON_INSTANCE(KnifeManager).
						ThrowKnife(&D3DXVECTOR2(*m_PosRight, 576), GameDataManager::RIGHT_ENEMY_TARGET, GameDataManager::PLAYER_TARGET, 1);
					m_Action = WAIT;
				}
			}
			break;
		}
			m_AttackInterval = 0;
	}
}