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
m_pWaitUvController(_pUvController),
m_pAttackUvController(_pUvController),
m_TextureIndex(_textureIndex),
m_LeftEnemyCount(13),
m_CenterEnemyCount(13),
m_RightEnemyCount(13),
m_LeftEnemyHits(false),
m_CenterEnemyHits(false),
m_RightEnemyHits(false),
m_FirstAttack(false),
m_SecondAttack(false),
m_ThirdAttack(false),
m_HitInterval(0.f),
m_AttackInterval(0.f),
m_AttackTime(0.f),
m_Action(WAIT),
m_AttackEnemy(NOT_ENEMY_ATTACK),
m_LeftEnemyCrowdAlfa(0.f),
m_CenterEnemyCrowdAlfa(0.f),
m_RightEnemyCrowdAlfa(0.f),
m_PosLeft{ (760), (576) },			//“G‚ÌoŒ»ˆÊ’u(‰¼)
m_PosCenter{ (960), (576) },		//“G‚ÌoŒ»ˆÊ’u(‰¼)
m_PosRight{ (1160), (576) }			//“G‚ÌoŒ»ˆÊ’u(‰¼)
{
	EnemyLoad("Resource/EnemyPos1.csv");

	SINGLETON_INSTANCE(GameDataManager).SetLeftEnemyCrowdAlfa(m_LeftEnemyCrowdAlfa);
	SINGLETON_INSTANCE(GameDataManager).SetCenterEnemyCrowdAlfa(m_CenterEnemyCrowdAlfa);
	SINGLETON_INSTANCE(GameDataManager).SetRightEnemyCrowdAlfa(m_RightEnemyCrowdAlfa);

	m_pEnemyExplosionUvController = new Lib::AnimUvController();
	m_pEnemyExplosionUvController->LoadAnimation("Resource/test_001.anim", "e_bom_a");

	m_pEnemyExplosionVertex = new Lib::Vertex2D(
		SINGLETON_INSTANCE(Lib::DX11Manager).GetDevice(),
		SINGLETON_INSTANCE(Lib::DX11Manager).GetDeviceContext(),
		SINGLETON_INSTANCE(Lib::Window).GetWindowSize());
	m_pEnemyExplosionVertex->Init(&m_Rect, m_pEnemyExplosionUvController->GetUV());
	m_pEnemyExplosionVertex->SetTexture(
		SINGLETON_INSTANCE(Lib::TextureManager).GetTexture(m_TextureIndex));

	m_pAttackUvController = new Lib::AnimUvController();
	m_pAttackUvController->LoadAnimation("Resource/test_001.anim", "e_attack");
	m_pWaitUvController = new Lib::AnimUvController();
	m_pWaitUvController->LoadAnimation("Resource/test_001.anim", "e_wait");

	if (m_EnemyLoad[m_LeftEnemyCount][0] >= 0)
	{
		//m_pLeftEnemyUvController = _pUvController;

		m_pLeftEnemyCollisionData = new CollisionData();
		m_pLeftEnemyCollisionData->SetEnable(false);
		m_pLeftEnemyCollisionData->SetCollision(&D3DXVECTOR3(m_PosLeft), &m_Rect, CollisionData::ENEMY_TYPE);
		SINGLETON_INSTANCE(CollisionManager).AddCollision(m_pLeftEnemyCollisionData);

		m_pLeftEnemyVertex = new Lib::Vertex2D(
			SINGLETON_INSTANCE(Lib::DX11Manager).GetDevice(),
			SINGLETON_INSTANCE(Lib::DX11Manager).GetDeviceContext(),
			SINGLETON_INSTANCE(Lib::Window).GetWindowSize());
		m_pLeftEnemyVertex->Init(&m_Rect, m_pWaitUvController->GetUV());
		m_pLeftEnemyVertex->SetTexture(
			SINGLETON_INSTANCE(Lib::TextureManager).GetTexture(m_TextureIndex));

		m_LeftEnemyHitState = m_pLeftEnemyCollisionData->GetCollisionState().HitState;

		m_LeftEnemyCrowdAlfa = 1.0f;
		SINGLETON_INSTANCE(GameDataManager).SetLeftEnemyCrowdAlfa(m_LeftEnemyCrowdAlfa);

		//EnemyPosInit(m_pLeftEnemyCollisionData, m_PosLeft, m_pLeftEnemyVertex, m_LeftEnemyHitState);
	}
	
	if (m_EnemyLoad[m_CenterEnemyCount][1] >= 0)
	{
		//m_pCenterEnemyUvController = _pUvController;

		m_pCenterEnemyCollisionData = new CollisionData();
		m_pCenterEnemyCollisionData->SetEnable(false);
		m_pCenterEnemyCollisionData->SetCollision(&D3DXVECTOR3(m_PosCenter), &m_Rect, CollisionData::ENEMY_TYPE);
		SINGLETON_INSTANCE(CollisionManager).AddCollision(m_pCenterEnemyCollisionData);

		m_pCenterEnemyVertex = new Lib::Vertex2D(
			SINGLETON_INSTANCE(Lib::DX11Manager).GetDevice(),
			SINGLETON_INSTANCE(Lib::DX11Manager).GetDeviceContext(),
			SINGLETON_INSTANCE(Lib::Window).GetWindowSize());
		//m_pCenterEnemyVertex->Init(&m_Rect, m_pCenterEnemyWaitUvController->GetUV());
		m_pCenterEnemyVertex->Init(&m_Rect, m_pWaitUvController->GetUV());
		m_pCenterEnemyVertex->SetTexture(
			SINGLETON_INSTANCE(Lib::TextureManager).GetTexture(m_TextureIndex));

		m_CenterEnemyHitState = m_pCenterEnemyCollisionData->GetCollisionState().HitState;
		
		m_CenterEnemyCrowdAlfa = 1.0f;
		SINGLETON_INSTANCE(GameDataManager).SetCenterEnemyCrowdAlfa(m_CenterEnemyCrowdAlfa);

		//EnemyPosInit(m_pCenterEnemyCollisionData, m_PosCenter, m_pCenterEnemyVertex, m_CenterEnemyHitState);
	}
	
	if (m_EnemyLoad[m_RightEnemyCount][2] >= 0)
	{
		//m_pRightEnemyUvController = _pUvController;

		m_pRightEnemyCollisionData = new CollisionData();
		m_pRightEnemyCollisionData->SetEnable(false);
		m_pRightEnemyCollisionData->SetCollision(&D3DXVECTOR3(m_PosRight), &m_Rect, CollisionData::ENEMY_TYPE);
		SINGLETON_INSTANCE(CollisionManager).AddCollision(m_pRightEnemyCollisionData);

		m_pRightEnemyVertex = new Lib::Vertex2D(
			SINGLETON_INSTANCE(Lib::DX11Manager).GetDevice(),
			SINGLETON_INSTANCE(Lib::DX11Manager).GetDeviceContext(),
			SINGLETON_INSTANCE(Lib::Window).GetWindowSize());
		//m_pRightEnemyVertex->Init(&m_Rect, m_pRightEnemyWaitUvController->GetUV());
		m_pRightEnemyVertex->Init(&m_Rect, m_pWaitUvController->GetUV());
		m_pRightEnemyVertex->SetTexture(
			SINGLETON_INSTANCE(Lib::TextureManager).GetTexture(m_TextureIndex));

		m_RightEnemyHitState = m_pRightEnemyCollisionData->GetCollisionState().HitState;
	
		m_RightEnemyCrowdAlfa = 1.0f;
		SINGLETON_INSTANCE(GameDataManager).SetRightEnemyCrowdAlfa(m_RightEnemyCrowdAlfa);

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

	delete m_pAttackUvController;
	m_pAttackUvController = NULL;
	
	delete m_pWaitUvController;
	m_pWaitUvController = NULL;
	
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

	if (m_pEnemyExplosionVertex != NULL)
	{
		m_pEnemyExplosionVertex->Release();
		delete m_pEnemyExplosionVertex;
		m_pEnemyExplosionVertex = NULL;
	}
}

void Enemy::Update()
{
	Hit();

	if ((m_EnemyLoad[m_LeftEnemyCount][0] == 0) && 
		(m_EnemyLoad[m_CenterEnemyCount][1] == 0) && 
		(m_EnemyLoad[m_RightEnemyCount][2] == 0) )
	{
		if (m_LeftEnemyCount > 0)
		{
			m_LeftEnemyCount -= 1;
		}
		if (m_CenterEnemyCount > 0)
		{
			m_CenterEnemyCount -= 1;
		}
		if (m_RightEnemyCount > 0)
		{
			m_RightEnemyCount -= 1;
		}

		if (m_EnemyLoad[m_LeftEnemyCount][0] > 0)
		{
			//m_LeftEnemyHits = false;
			m_pLeftEnemyCollisionData->SetEnable(true);

			m_LeftEnemyCrowdAlfa = 1.f;
			SINGLETON_INSTANCE(GameDataManager).SetLeftEnemyCrowdAlfa(m_LeftEnemyCrowdAlfa);
		}

		if (m_EnemyLoad[m_CenterEnemyCount][1] > 0)
		{
			//m_CenterEnemyHits = false;
			m_pCenterEnemyCollisionData->SetEnable(true);

			m_CenterEnemyCrowdAlfa = 1.f;
			SINGLETON_INSTANCE(GameDataManager).SetCenterEnemyCrowdAlfa(m_CenterEnemyCrowdAlfa);
		}

		if (m_EnemyLoad[m_RightEnemyCount][2] > 0)
		{
			//m_RightEnemyHits = false;
			m_pRightEnemyCollisionData->SetEnable(true);

			m_RightEnemyCrowdAlfa = 1.f;
			SINGLETON_INSTANCE(GameDataManager).SetRightEnemyCrowdAlfa(m_RightEnemyCrowdAlfa);
		}
	}

	Attack();

	if ( m_CenterEnemyHits == true || m_LeftEnemyHits == true || m_RightEnemyHits == true)
	{
		m_HitInterval += 1.0f;
	}

	if (m_LeftEnemyCount == 0 && m_CenterEnemyCount == 0 && m_RightEnemyCount == 0)
	{
		SINGLETON_INSTANCE(GameDataManager).SetIsGameOver(true);
	}

	CollisionControl();

}

void Enemy::Draw()
{
	if (m_EnemyLoad[m_LeftEnemyCount][0] > 0)
	{
		if (m_LeftEnemyHits == false)
		{
			if (m_AttackEnemy == NOT_ENEMY_ATTACK || m_Action == WAIT ||m_AttackEnemy != LEFT_ENEMY_ATTACK)
			{
				m_pLeftEnemyVertex->Draw(&m_PosLeft, m_pWaitUvController->GetUV());
			}
			if (m_AttackEnemy == LEFT_ENEMY_ATTACK)
			{
				m_pLeftEnemyVertex->Draw(&m_PosLeft, m_pAttackUvController->GetUV());
			}

			SINGLETON_INSTANCE(GameDataManager).SetLeftEnemyCrowdAlfa(m_LeftEnemyCrowdAlfa);
			EnemyExplosion(m_PosLeft, 0.f);
		}
		else if (m_LeftEnemyHits == true)
		{
			EnemyExplosion(m_PosLeft, 1.f);
		}
	}
	else if (m_EnemyLoad[m_LeftEnemyCount][0] == 0)
	{
		m_LeftEnemyCrowdAlfa = 0.f;
		SINGLETON_INSTANCE(GameDataManager).SetLeftEnemyCrowdAlfa(m_LeftEnemyCrowdAlfa);
	}
	
	if (m_EnemyLoad[m_CenterEnemyCount][1] > 0)
	{
	
		if (m_CenterEnemyHits == false)
		{
			if (m_AttackEnemy == NOT_ENEMY_ATTACK || m_Action == WAIT || m_AttackEnemy != CENTER_ENEMY_ATTACK)
			{
				m_pCenterEnemyVertex->Draw(&m_PosCenter, m_pWaitUvController->GetUV());
			}
			if (m_AttackEnemy == CENTER_ENEMY_ATTACK)
			{
				m_pCenterEnemyVertex->Draw(&m_PosCenter, m_pAttackUvController->GetUV());
			}
			
			SINGLETON_INSTANCE(GameDataManager).SetCenterEnemyCrowdAlfa(m_CenterEnemyCrowdAlfa);
			EnemyExplosion(m_PosCenter, 0.f);
		}
		else if (m_CenterEnemyHits == true)
		{
			EnemyExplosion(m_PosCenter, 1.f);
		}
	}
	else if (m_EnemyLoad[m_CenterEnemyCount][1] == 0)
	{
		m_CenterEnemyCrowdAlfa = 0.f;
		SINGLETON_INSTANCE(GameDataManager).SetCenterEnemyCrowdAlfa(m_CenterEnemyCrowdAlfa);
	}

	if (m_EnemyLoad[m_RightEnemyCount][2] > 0)
	{
	
		if (m_RightEnemyHits == false)
		{
			if (m_AttackEnemy == NOT_ENEMY_ATTACK || m_Action == WAIT || m_AttackEnemy != RIGHT_ENEMY_ATTACK)
			{
				m_pRightEnemyVertex->Draw(&m_PosRight, m_pWaitUvController->GetUV());
			}
			if (m_AttackEnemy == RIGHT_ENEMY_ATTACK)
			{
				m_pRightEnemyVertex->Draw(&m_PosRight, m_pAttackUvController->GetUV());
			}
			
			SINGLETON_INSTANCE(GameDataManager).SetRightEnemyCrowdAlfa(m_RightEnemyCrowdAlfa);
			EnemyExplosion(m_PosRight, 0.f);
		}
		else if (m_RightEnemyHits == true)
		{
			EnemyExplosion(m_PosRight, 1.f);
		}
	}
	else if (m_EnemyLoad[m_RightEnemyCount][0] == 0)
	{
		m_RightEnemyCrowdAlfa = 0.f;
		SINGLETON_INSTANCE(GameDataManager).SetRightEnemyCrowdAlfa(m_RightEnemyCrowdAlfa);
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

	if (m_LeftEnemyHits == true && m_HitInterval == HITINTERVAL)
	{
		m_HitInterval = 0;
		m_LeftEnemyHits = false;
		m_EnemyLoad[m_LeftEnemyCount][0] = 0;
		EnemyExplosion(m_PosLeft, 0.f);

		m_LeftEnemyCrowdAlfa = 0.f;
		SINGLETON_INSTANCE(GameDataManager).SetLeftEnemyCrowdAlfa(m_LeftEnemyCrowdAlfa);
	}
	if (m_CenterEnemyHits == true && m_HitInterval == HITINTERVAL)
	{
		m_HitInterval = 0;
		m_CenterEnemyHits = false;
		m_EnemyLoad[m_CenterEnemyCount][1] = 0;
		EnemyExplosion(m_PosCenter, 0.f);

		m_CenterEnemyCrowdAlfa = 0.f;
		SINGLETON_INSTANCE(GameDataManager).SetCenterEnemyCrowdAlfa(m_CenterEnemyCrowdAlfa);
	}
	if (m_RightEnemyHits == true && m_HitInterval == HITINTERVAL)
	{
		m_HitInterval = 0;
		m_RightEnemyHits = false;
		m_EnemyLoad[m_RightEnemyCount][2] = 0;
		EnemyExplosion(m_PosRight, 0.f);

		m_RightEnemyCrowdAlfa = 0.f;
		SINGLETON_INSTANCE(GameDataManager).SetRightEnemyCrowdAlfa(m_RightEnemyCrowdAlfa);
	}

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
		SINGLETON_INSTANCE(Lib::Window).GetWindowSize());
	_vertex->Init(&m_Rect, m_pWaitUvController->GetUV());
	_vertex->SetTexture(
		SINGLETON_INSTANCE(Lib::TextureManager).GetTexture(m_TextureIndex));

	_hitstate = _pcollisiondata->GetCollisionState().HitState;

}

void Enemy::CollisionControl()
{
	if (m_EnemyLoad[m_LeftEnemyCount][0] > 0)
	{
		m_pLeftEnemyCollisionData->SetEnable(true);

		CollisionData::HIT_STATE m_LeftEnemyHitState = m_pLeftEnemyCollisionData->GetCollisionState().HitState;
	
		if (m_LeftEnemyHitState == CollisionData::KNIFE_HIT)
		{
			m_pLeftEnemyCollisionData->SetEnable(false);
			m_LeftEnemyHits = true;
		}
	}
	if (m_EnemyLoad[m_CenterEnemyCount][1] > 0)
	{
		m_pCenterEnemyCollisionData->SetEnable(true);

		CollisionData::HIT_STATE m_CenterEnemyHitState = m_pCenterEnemyCollisionData->GetCollisionState().HitState;
		
		if (m_CenterEnemyHitState == CollisionData::KNIFE_HIT)
		{
			m_pCenterEnemyCollisionData->SetEnable(false);
			m_CenterEnemyHits = true;
		}
	}
	if (m_EnemyLoad[m_RightEnemyCount][2] > 0)
	{
		m_pRightEnemyCollisionData->SetEnable(true);

		CollisionData::HIT_STATE m_RightEnemyHitState = m_pRightEnemyCollisionData->GetCollisionState().HitState;
		if (m_RightEnemyHitState == CollisionData::KNIFE_HIT)
		{
			m_pRightEnemyCollisionData->SetEnable(false);
			m_RightEnemyHits = true;
		}
	}	
}

void Enemy::EnemyExplosion(D3DXVECTOR2 _pos, float _alpha)
{
	m_pEnemyExplosionVertex->Draw(&_pos, m_pEnemyExplosionUvController->GetUV(), _alpha);
}

void Enemy::Attack()
{
	srand((unsigned int)time(NULL));

	int Random = rand() % 3;

	m_AttackInterval += 1.0f;

	//if (m_AttackInterval > ATTACKINTERVAL)
	//{	
		m_Action = THROW;
		m_AttackTime += 1.0f;

		if (m_EnemyLoad[m_LeftEnemyCount][0] > 0 && m_LeftEnemyHits == false)
		{
			if (AttackTurn(m_LeftEnemyCount, 0) == FIRST_ATTACK && m_AttackTime == 1)
			{
				m_AttackEnemy = LEFT_ENEMY_ATTACK;
			}
			else if (AttackTurn(m_LeftEnemyCount, 0) == SECOND_ATTACK && m_AttackTime == 120)
			{
				m_AttackEnemy = LEFT_ENEMY_ATTACK;
			}
			else if (AttackTurn(m_LeftEnemyCount, 0) == THIRD_ATTACK && m_AttackTime == 240)
			{
				m_AttackEnemy = LEFT_ENEMY_ATTACK;
			}

			if (m_Action == THROW && m_AttackEnemy == LEFT_ENEMY_ATTACK)
			{
				SINGLETON_INSTANCE(KnifeManager).
					ThrowKnife(&D3DXVECTOR2(*m_PosLeft, 576), GameDataManager::LEFT_ENEMY_TARGET, GameDataManager::PLAYER_TARGET, ThrowSpeed(m_LeftEnemyCount, 0));
				m_AttackEnemy = NOT_ENEMY_ATTACK;
				m_Action = WAIT;
			}
		}
		else if (m_EnemyLoad[m_LeftEnemyCount][0] == 0 && m_LeftEnemyHits == true)
		{
			m_AttackTime += 120;
		}
		
		if (m_EnemyLoad[m_CenterEnemyCount][1] > 0 && m_CenterEnemyHits == false)
		{
			if (AttackTurn(m_CenterEnemyCount, 1) == FIRST_ATTACK && m_AttackTime == 1)
			{
				m_AttackEnemy = CENTER_ENEMY_ATTACK;
			}
			else if (AttackTurn(m_CenterEnemyCount, 1) == SECOND_ATTACK && m_AttackTime == 120)
			{
				m_AttackEnemy = CENTER_ENEMY_ATTACK;
			}
			else if (AttackTurn(m_CenterEnemyCount, 1) == THIRD_ATTACK && m_AttackTime == 240)
			{
				m_AttackEnemy = CENTER_ENEMY_ATTACK;
			}

			if (m_Action == THROW && m_AttackEnemy == CENTER_ENEMY_ATTACK)
			{
				SINGLETON_INSTANCE(KnifeManager).
					ThrowKnife(&D3DXVECTOR2(*m_PosCenter, 576), GameDataManager::FRONT_ENEMY_TARGET, GameDataManager::PLAYER_TARGET, ThrowSpeed(m_CenterEnemyCount, 1));
				m_AttackEnemy = NOT_ENEMY_ATTACK;
				m_Action = WAIT;
			}
		}
		else if (m_EnemyLoad[m_CenterEnemyCount][1] == 0 && m_CenterEnemyHits == true)
		{
			m_AttackTime += 120.f;
		}
		
		if (m_EnemyLoad[m_RightEnemyCount][2] > 0 && m_RightEnemyHits == false)
		{
			if (AttackTurn(m_RightEnemyCount, 2) == FIRST_ATTACK && m_AttackTime == 1)
			{
				m_AttackEnemy = RIGHT_ENEMY_ATTACK;
			}
			else if (AttackTurn(m_RightEnemyCount, 2) == SECOND_ATTACK && m_AttackTime == 120)
			{
				m_AttackEnemy = RIGHT_ENEMY_ATTACK;
			}
			else if (AttackTurn(m_RightEnemyCount, 2) == THIRD_ATTACK && m_AttackTime == 240)
			{
				m_AttackEnemy = RIGHT_ENEMY_ATTACK;
			}

			if (m_Action == THROW && m_AttackEnemy == RIGHT_ENEMY_ATTACK)
			{
				SINGLETON_INSTANCE(KnifeManager).
					ThrowKnife(&D3DXVECTOR2(*m_PosRight, 576), GameDataManager::RIGHT_ENEMY_TARGET, GameDataManager::PLAYER_TARGET, ThrowSpeed(m_RightEnemyCount, 2));
				m_AttackEnemy = NOT_ENEMY_ATTACK;
				m_Action = WAIT;
			}
		}
		else if (m_EnemyLoad[m_RightEnemyCount][2] == 0 && m_RightEnemyHits == true)
		{
			m_AttackTime += 120.f;
		}
		
		//m_AttackInterval = 0;
		//m_AttackEnemy = NOT_ENEMY_ATTACK;
		if (m_AttackTime > 360)
		{
			m_AttackTime = 0;
		}
	//}
	//if (m_AttackInterval > ATTACKINTERVAL)
	//{
	//	m_Action = THROW;
	//	switch (Random)
	//	{			
	//		case 0:
	//		if (m_Action == THROW)
	//		{
	//			m_AttackTime += 1.f;
	//			m_AttackEnemy = LEFT_ENEMY_ATTACK;
	//			if (m_EnemyLoad[m_LeftEnemyCount][0] > 0 && m_LeftEnemyHits == false)
	//			{
	//				SINGLETON_INSTANCE(KnifeManager).
	//					ThrowKnife(&D3DXVECTOR2(*m_PosLeft, 576), GameDataManager::LEFT_ENEMY_TARGET, GameDataManager::PLAYER_TARGET, 1);
	//			}
	//			if (m_AttackTime == ATTACKTIME)
	//			{
	//				m_AttackEnemy = NOT_ENEMY_ATTACK;
	//				m_Action = WAIT;
	//				m_AttackTime = 0.f;
	//			}
	//		}
	//		break;
	//	case 1:
	//		if (m_Action == THROW)
	//		{
	//			m_AttackTime += 1.f;
	//			m_AttackEnemy = CENTER_ENEMY_ATTACK;
	//			if (m_EnemyLoad[m_CenterEnemyCount][1] > 0 && m_CenterEnemyHits == false)
	//			{
	//				SINGLETON_INSTANCE(KnifeManager).
	//					ThrowKnife(&D3DXVECTOR2(*m_PosCenter, 576), GameDataManager::FRONT_ENEMY_TARGET, GameDataManager::PLAYER_TARGET, 1);
	//				//m_Action = WAIT;
	//			}				
	//			if (m_AttackTime == ATTACKTIME)
	//			{
	//				m_AttackEnemy = NOT_ENEMY_ATTACK;
	//				m_Action = WAIT;
	//				m_AttackTime = 0.f;
	//			}
	//		}
	//		break;
	//	case 2:
	//		if (m_Action == THROW)
	//		{
	//			m_AttackTime += 1.f;
	//			m_AttackEnemy = RIGHT_ENEMY_ATTACK;
	//			if (m_EnemyLoad[m_RightEnemyCount][2] > 0 && m_RightEnemyHits == false)
	//			{
	//				SINGLETON_INSTANCE(KnifeManager).
	//					ThrowKnife(&D3DXVECTOR2(*m_PosRight, 576), GameDataManager::RIGHT_ENEMY_TARGET, GameDataManager::PLAYER_TARGET, 1);
	//				//m_Action = WAIT;
	//			}
	//			if (m_AttackTime == ATTACKTIME)
	//			{
	//				m_AttackEnemy = NOT_ENEMY_ATTACK;
	//				m_Action = WAIT;
	//				m_AttackTime = 0.f;
	//			}
	//		}
	//		break;
	//	}
	//		m_AttackInterval = 0;
	//		//m_AttackEnemy = NOT_ENEMY_ATTACK;
	//}
}

Enemy::ATTACK_TURN Enemy::AttackTurn(int _column, int _row)
{
	int pos = m_EnemyLoad[_column][_row] % 10;

	switch (pos)
	{
	case 1:
		return FIRST_ATTACK;
		break;
	case 2:
		return SECOND_ATTACK;
		break;
	case 3:
		return THIRD_ATTACK;
		break;
	}
}

float Enemy::ThrowSpeed(int _column, int _row)
{
	int number = m_EnemyLoad[_column][_row] / 10;

	switch (number)
	{
	case 1:
		return 1.f;
		break;
	case 2:
		return 0.5f;
		break;
	case 3:
		return 1.65f;
		break;
	case 4:
		return 1.45f;
		break;
	}
}