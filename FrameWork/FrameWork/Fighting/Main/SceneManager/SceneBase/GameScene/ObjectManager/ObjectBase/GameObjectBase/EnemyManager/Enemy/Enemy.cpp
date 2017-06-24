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
m_LeftEnemyAttack(false),
m_CenterEnemyAttack(false),
m_RightEnemyAttack(false),
m_IsLeftEnemyExplosion(false),
m_IsCenterEnemyExplosion(false),
m_IsRightEnemyExplosion(false),
m_GoodHit(false),
m_AmazingHit(false),
m_FantasticHit(false),
m_HitInterval(0.f),
m_AttackInterval(0.f),
m_AttackTime(0.f),
m_ExplosionTime(0.f),
m_AttackEnemy(NOT_ENEMY_ATTACK),
m_LeftEnemyCrowdAlfa(0.f),
m_CenterEnemyCrowdAlfa(0.f),
m_RightEnemyCrowdAlfa(0.f),
m_PosLeft{ (760), (576) },	
m_PosCenter{ (960), (576) },
m_PosRight{ (1160), (576) }	
{
	EnemyLoad("Resource/EnemyPos1.csv");

	SINGLETON_INSTANCE(GameDataManager).SetLeftEnemyCrowdAlfa(m_LeftEnemyCrowdAlfa);
	SINGLETON_INSTANCE(GameDataManager).SetCenterEnemyCrowdAlfa(m_CenterEnemyCrowdAlfa);
	SINGLETON_INSTANCE(GameDataManager).SetRightEnemyCrowdAlfa(m_RightEnemyCrowdAlfa);

	//�����`��֘A Start
	m_pEnemyGoodExplosionUvController = new Lib::AnimUvController();
	m_pEnemyGoodExplosionUvController->LoadAnimation("Resource/test_001.anim", "e_bom_g");
	m_pEnemyGoodExplosionVertex = new Lib::Vertex2D(
		SINGLETON_INSTANCE(Lib::DX11Manager).GetDevice(),
		SINGLETON_INSTANCE(Lib::DX11Manager).GetDeviceContext(),
		SINGLETON_INSTANCE(Lib::Window).GetWindowSize());
	m_pEnemyGoodExplosionVertex->Init(&m_Rect, m_pEnemyGoodExplosionUvController->GetUV());
	m_pEnemyGoodExplosionVertex->SetTexture(
		SINGLETON_INSTANCE(Lib::TextureManager).GetTexture(m_TextureIndex));

	m_pEnemyAmazingExplosionUvController = new Lib::AnimUvController();
	m_pEnemyAmazingExplosionUvController->LoadAnimation("Resource/test_001.anim", "e_bom_a");
	m_pEnemyAmazingExplosionVertex = new Lib::Vertex2D(
		SINGLETON_INSTANCE(Lib::DX11Manager).GetDevice(),
		SINGLETON_INSTANCE(Lib::DX11Manager).GetDeviceContext(),
		SINGLETON_INSTANCE(Lib::Window).GetWindowSize());
	m_pEnemyAmazingExplosionVertex->Init(&m_Rect, m_pEnemyAmazingExplosionUvController->GetUV());
	m_pEnemyAmazingExplosionVertex->SetTexture(
		SINGLETON_INSTANCE(Lib::TextureManager).GetTexture(m_TextureIndex));

	m_pEnemyFantasticExplosionUvController = new Lib::AnimUvController();
	m_pEnemyFantasticExplosionUvController->LoadAnimation("Resource/test_001.anim", "e_bom_f");
	m_pEnemyFantasticExplosionVertex = new Lib::Vertex2D(
		SINGLETON_INSTANCE(Lib::DX11Manager).GetDevice(),
		SINGLETON_INSTANCE(Lib::DX11Manager).GetDeviceContext(),
		SINGLETON_INSTANCE(Lib::Window).GetWindowSize());
	m_pEnemyFantasticExplosionVertex->Init(&m_Rect, m_pEnemyFantasticExplosionUvController->GetUV());
	m_pEnemyFantasticExplosionVertex->SetTexture(
		SINGLETON_INSTANCE(Lib::TextureManager).GetTexture(m_TextureIndex));

	//�����`��֘A End

	//�G�`�揈�� Start
	m_pAttackUvController = new Lib::AnimUvController();
	m_pWaitUvController = new Lib::AnimUvController();
	//m_pAttackUvController->LoadAnimation("Resource/test_001.anim", "e_attack01");
	//m_pWaitUvController->LoadAnimation("Resource/test_001.anim", "e_wait01");
	srand((unsigned int)time(NULL));

	int Random = rand() % 3;

	switch (Random)
		{
		case 0:
			m_pAttackUvController->LoadAnimation("Resource/test_001.anim", "e_attack01");
			m_pWaitUvController->LoadAnimation("Resource/test_001.anim", "e_wait01");
			break;
		case 1:
			m_pAttackUvController->LoadAnimation("Resource/test_001.anim", "e_attack02");
			m_pWaitUvController->LoadAnimation("Resource/test_001.anim", "e_wait02");
			break;
		case 2:
			m_pAttackUvController->LoadAnimation("Resource/test_001.anim", "e_attack03");
			m_pWaitUvController->LoadAnimation("Resource/test_001.anim", "e_wait03");
			break;
		}
	//�G�`�揈�� End

	if (m_EnemyLoad[m_LeftEnemyCount][0] >= 0)
	{
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
	}
	
	if (m_EnemyLoad[m_CenterEnemyCount][1] >= 0)
	{
		m_pCenterEnemyCollisionData = new CollisionData();
		m_pCenterEnemyCollisionData->SetEnable(false);
		m_pCenterEnemyCollisionData->SetCollision(&D3DXVECTOR3(m_PosCenter), &m_Rect, CollisionData::ENEMY_TYPE);
		SINGLETON_INSTANCE(CollisionManager).AddCollision(m_pCenterEnemyCollisionData);

		m_pCenterEnemyVertex = new Lib::Vertex2D(
			SINGLETON_INSTANCE(Lib::DX11Manager).GetDevice(),
			SINGLETON_INSTANCE(Lib::DX11Manager).GetDeviceContext(),
			SINGLETON_INSTANCE(Lib::Window).GetWindowSize());
		m_pCenterEnemyVertex->Init(&m_Rect, m_pWaitUvController->GetUV());
		m_pCenterEnemyVertex->SetTexture(
			SINGLETON_INSTANCE(Lib::TextureManager).GetTexture(m_TextureIndex));

		m_CenterEnemyHitState = m_pCenterEnemyCollisionData->GetCollisionState().HitState;
		
		m_CenterEnemyCrowdAlfa = 1.0f;
		SINGLETON_INSTANCE(GameDataManager).SetCenterEnemyCrowdAlfa(m_CenterEnemyCrowdAlfa);
	}
	
	if (m_EnemyLoad[m_RightEnemyCount][2] >= 0)
	{
		m_pRightEnemyCollisionData = new CollisionData();
		m_pRightEnemyCollisionData->SetEnable(false);
		m_pRightEnemyCollisionData->SetCollision(&D3DXVECTOR3(m_PosRight), &m_Rect, CollisionData::ENEMY_TYPE);
		SINGLETON_INSTANCE(CollisionManager).AddCollision(m_pRightEnemyCollisionData);

		m_pRightEnemyVertex = new Lib::Vertex2D(
			SINGLETON_INSTANCE(Lib::DX11Manager).GetDevice(),
			SINGLETON_INSTANCE(Lib::DX11Manager).GetDeviceContext(),
			SINGLETON_INSTANCE(Lib::Window).GetWindowSize());
		m_pRightEnemyVertex->Init(&m_Rect, m_pWaitUvController->GetUV());
		m_pRightEnemyVertex->SetTexture(
			SINGLETON_INSTANCE(Lib::TextureManager).GetTexture(m_TextureIndex));

		m_RightEnemyHitState = m_pRightEnemyCollisionData->GetCollisionState().HitState;
	
		m_RightEnemyCrowdAlfa = 1.0f;
		SINGLETON_INSTANCE(GameDataManager).SetRightEnemyCrowdAlfa(m_RightEnemyCrowdAlfa);
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

	delete m_pEnemyGoodExplosionUvController;
	m_pEnemyGoodExplosionUvController = NULL;

	delete m_pEnemyAmazingExplosionUvController;
	m_pEnemyAmazingExplosionUvController = NULL;

	delete m_pEnemyFantasticExplosionUvController;
	m_pEnemyFantasticExplosionUvController = NULL;

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

	if (m_pEnemyGoodExplosionVertex != NULL)
	{
		m_pEnemyGoodExplosionVertex->Release();
		delete m_pEnemyGoodExplosionVertex;
		m_pEnemyGoodExplosionVertex = NULL;
	}

	if (m_pEnemyAmazingExplosionVertex != NULL)
	{
		m_pEnemyAmazingExplosionVertex->Release();
		delete m_pEnemyAmazingExplosionVertex;
		m_pEnemyAmazingExplosionVertex = NULL;
	}

	if (m_pEnemyFantasticExplosionVertex != NULL)
	{
		m_pEnemyFantasticExplosionVertex->Release();
		delete m_pEnemyFantasticExplosionVertex;
		m_pEnemyFantasticExplosionVertex = NULL;
	}
}

void Enemy::Update()
{
	CollisionControl();

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
			m_pLeftEnemyCollisionData->SetEnable(true);

			m_LeftEnemyCrowdAlfa = 1.f;
			SINGLETON_INSTANCE(GameDataManager).SetLeftEnemyCrowdAlfa(m_LeftEnemyCrowdAlfa);
		}

		if (m_EnemyLoad[m_CenterEnemyCount][1] > 0)
		{
			m_pCenterEnemyCollisionData->SetEnable(true);

			m_CenterEnemyCrowdAlfa = 1.f;
			SINGLETON_INSTANCE(GameDataManager).SetCenterEnemyCrowdAlfa(m_CenterEnemyCrowdAlfa);
		}

		if (m_EnemyLoad[m_RightEnemyCount][2] > 0)
		{
			m_pRightEnemyCollisionData->SetEnable(true);

			m_RightEnemyCrowdAlfa = 1.f;
			SINGLETON_INSTANCE(GameDataManager).SetRightEnemyCrowdAlfa(m_RightEnemyCrowdAlfa);
		}

		m_AttackTime = 0.f;

		m_GoodHit = m_AmazingHit = m_FantasticHit = false;
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
}

void Enemy::Draw()
{
	if (m_EnemyLoad[m_LeftEnemyCount][0] > 0)
	{
		if (m_LeftEnemyHits == false)
		{
			if (m_LeftEnemyAttack == false)
			{
				m_pLeftEnemyVertex->Draw(&m_PosLeft, m_pWaitUvController->GetUV());
			}
			else if (m_LeftEnemyAttack == true)
			{
				m_pLeftEnemyVertex->Draw(&m_PosLeft, m_pAttackUvController->GetUV());
			}

			SINGLETON_INSTANCE(GameDataManager).SetLeftEnemyCrowdAlfa(m_LeftEnemyCrowdAlfa);
			EnemyExplosionDraw(m_PosLeft, 0.f, EXPLOSION_MAX);
		}
		if (m_LeftEnemyHits == true && m_GoodHit == true)
		{
			EnemyExplosionDraw(m_PosLeft, 1.f, GOOD_EXPLOSION);
		}
		else if (m_LeftEnemyHits == true && m_AmazingHit == true)
		{
			EnemyExplosionDraw(m_PosLeft, 1.f, AMAZING_EXPLOSION);
		}
		else if (m_LeftEnemyHits == true && m_FantasticHit == true)
		{
			EnemyExplosionDraw(m_PosLeft, 1.f, FANTASTIC_EXPLOSION);
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
			if (m_CenterEnemyAttack == false)
			{
				m_pCenterEnemyVertex->Draw(&m_PosCenter, m_pWaitUvController->GetUV());
			}
			else if (m_CenterEnemyAttack == true)
			{
				m_pCenterEnemyVertex->Draw(&m_PosCenter, m_pAttackUvController->GetUV());
			}
			
			SINGLETON_INSTANCE(GameDataManager).SetCenterEnemyCrowdAlfa(m_CenterEnemyCrowdAlfa);
			EnemyExplosionDraw(m_PosCenter, 0.f, EXPLOSION_MAX);
		}
		if (m_CenterEnemyHits == true && m_GoodHit == true)
		{
				EnemyExplosionDraw(m_PosCenter, 1.f, GOOD_EXPLOSION);
		}
		else if (m_CenterEnemyHits == true && m_AmazingHit == true)
		{
				EnemyExplosionDraw(m_PosCenter, 1.f, AMAZING_EXPLOSION);
		}
		else if (m_CenterEnemyHits == true && m_FantasticHit == true)
		{
				EnemyExplosionDraw(m_PosCenter, 1.f, FANTASTIC_EXPLOSION);
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
			if (m_RightEnemyAttack == false)
			{
				m_pRightEnemyVertex->Draw(&m_PosRight, m_pWaitUvController->GetUV());
			}
			else if (m_RightEnemyAttack == true)
			{
				m_pRightEnemyVertex->Draw(&m_PosRight, m_pAttackUvController->GetUV());
			}
			
			SINGLETON_INSTANCE(GameDataManager).SetRightEnemyCrowdAlfa(m_RightEnemyCrowdAlfa);
			EnemyExplosionDraw(m_PosRight, 0.f, EXPLOSION_MAX);
		}
		if (m_RightEnemyHits == true && m_GoodHit == true)
		{
			EnemyExplosionDraw(m_PosRight, 1.f, GOOD_EXPLOSION);
		}
		else if (m_RightEnemyHits == true && m_AmazingHit == true)
		{
			EnemyExplosionDraw(m_PosRight, 1.f, AMAZING_EXPLOSION);
		}
		else if (m_RightEnemyHits == true && m_FantasticHit == true)
		{
			EnemyExplosionDraw(m_PosRight, 1.f, FANTASTIC_EXPLOSION);
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
		EnemyExplosionDraw(m_PosLeft, 0.f, EXPLOSION_MAX);

		m_LeftEnemyCrowdAlfa = 0.f;
		SINGLETON_INSTANCE(GameDataManager).SetLeftEnemyCrowdAlfa(m_LeftEnemyCrowdAlfa);
	}
	if (m_CenterEnemyHits == true && m_HitInterval == HITINTERVAL)
	{
		m_HitInterval = 0;
		m_CenterEnemyHits = false;
		m_EnemyLoad[m_CenterEnemyCount][1] = 0;
		EnemyExplosionDraw(m_PosCenter, 0.f, EXPLOSION_MAX);

		m_CenterEnemyCrowdAlfa = 0.f;
		SINGLETON_INSTANCE(GameDataManager).SetCenterEnemyCrowdAlfa(m_CenterEnemyCrowdAlfa);
	}
	if (m_RightEnemyHits == true && m_HitInterval == HITINTERVAL)
	{
		m_HitInterval = 0;
		m_RightEnemyHits = false;
		m_EnemyLoad[m_RightEnemyCount][2] = 0;
		EnemyExplosionDraw(m_PosRight, 0.f, EXPLOSION_MAX);

		m_RightEnemyCrowdAlfa = 0.f;
		SINGLETON_INSTANCE(GameDataManager).SetRightEnemyCrowdAlfa(m_RightEnemyCrowdAlfa);
	}

}

//�G�Ǝ莆�̏Փ˔��菈��
void Enemy::CollisionControl()
{
	if (m_EnemyLoad[m_LeftEnemyCount][0] > 0)
	{
		m_pLeftEnemyCollisionData->SetEnable(true);

		CollisionData::HIT_STATE m_LeftEnemyHitState = m_pLeftEnemyCollisionData->GetCollisionState().HitState;
		if (m_LeftEnemyHitState == CollisionData::GOOD_HIT)
		{
			m_GoodHit = true;
		}
		if (m_LeftEnemyHitState == CollisionData::AMAZING_HIT)
		{
			m_AmazingHit = true;
		}
		if (m_LeftEnemyHitState == CollisionData::FANTASTIC_HIT)
		{
			m_FantasticHit = true;
		}
		if (m_LeftEnemyHitState == CollisionData::GOOD_HIT || m_LeftEnemyHitState == CollisionData::FANTASTIC_HIT || m_LeftEnemyHitState == CollisionData::AMAZING_HIT)
		{
			m_pLeftEnemyCollisionData->SetEnable(false);
			m_LeftEnemyHits = true;
		}
	}
	if (m_EnemyLoad[m_CenterEnemyCount][1] > 0)
	{
		m_pCenterEnemyCollisionData->SetEnable(true);

		CollisionData::HIT_STATE m_CenterEnemyHitState = m_pCenterEnemyCollisionData->GetCollisionState().HitState;
		if (m_CenterEnemyHitState == CollisionData::GOOD_HIT)
		{
			m_GoodHit = true;
		}
		if (m_CenterEnemyHitState == CollisionData::AMAZING_HIT)
		{
			m_AmazingHit = true;
		}
		if (m_CenterEnemyHitState == CollisionData::FANTASTIC_HIT)
		{
			m_FantasticHit = true;
		}
		if (m_CenterEnemyHitState == CollisionData::GOOD_HIT || m_CenterEnemyHitState == CollisionData::FANTASTIC_HIT || m_CenterEnemyHitState == CollisionData::AMAZING_HIT)
		{
			m_pCenterEnemyCollisionData->SetEnable(false);
			m_CenterEnemyHits = true;			
		}
	}
	if (m_EnemyLoad[m_RightEnemyCount][2] > 0)
	{
		m_pRightEnemyCollisionData->SetEnable(true);

		CollisionData::HIT_STATE m_RightEnemyHitState = m_pRightEnemyCollisionData->GetCollisionState().HitState;
		if (m_RightEnemyHitState == CollisionData::GOOD_HIT)
		{
			m_GoodHit = true;
		}
		if (m_RightEnemyHitState == CollisionData::AMAZING_HIT)
		{
			m_AmazingHit = true;
		}
		if (m_RightEnemyHitState == CollisionData::FANTASTIC_HIT)
		{
			m_FantasticHit = true;
		}
		if (m_RightEnemyHitState == CollisionData::GOOD_HIT || m_RightEnemyHitState == CollisionData::FANTASTIC_HIT || m_RightEnemyHitState == CollisionData::AMAZING_HIT)
		{
			m_pRightEnemyCollisionData->SetEnable(false);
			m_RightEnemyHits = true;
			
		}
	}	
}

void Enemy::EnemyExplosionDraw(D3DXVECTOR2 pos_, float alpha_, EXPLOSION_TYPE explosiontype_)
{
	switch (explosiontype_)
	{
	case GOOD_EXPLOSION:
		m_pEnemyGoodExplosionVertex->Draw(&pos_, m_pEnemyGoodExplosionUvController->GetUV(), alpha_, &D3DXVECTOR2(0.5f, 0.5f));
		break;
	case AMAZING_EXPLOSION:
		m_pEnemyAmazingExplosionVertex->Draw(&pos_, m_pEnemyAmazingExplosionUvController->GetUV(), alpha_, &D3DXVECTOR2(1.5f, 1.f));
		break;
	case FANTASTIC_EXPLOSION:
		m_pEnemyFantasticExplosionVertex->Draw(&pos_, m_pEnemyFantasticExplosionUvController->GetUV(), alpha_, &D3DXVECTOR2(1.5f, 1.5f));
		break;
	}
}

void Enemy::Attack()
{
	srand((unsigned int)time(NULL));

	int Random = rand() % 3;

	m_AttackTime += 1.0f;

	if (m_EnemyLoad[m_LeftEnemyCount][0] > 0 && m_LeftEnemyHits == false)
	{
		if (AttackTurn(m_LeftEnemyCount, 0) == FIRST_ATTACK && m_AttackTime == 30)
		{
			//m_AttackEnemy = LEFT_ENEMY_ATTACK;
			m_LeftEnemyAttack = true;
		}
		else if (AttackTurn(m_LeftEnemyCount, 0) == SECOND_ATTACK && m_AttackTime == 140)
		{
			//m_AttackEnemy = LEFT_ENEMY_ATTACK;
			m_LeftEnemyAttack = true;
		}
		else if (AttackTurn(m_LeftEnemyCount, 0) == THIRD_ATTACK && m_AttackTime == 260)
		{
			//m_AttackEnemy = LEFT_ENEMY_ATTACK;
			m_LeftEnemyAttack = true;
		}
		if (m_LeftEnemyAttack == true)
		{
			m_AttackInterval += 1.f;
			if (m_AttackInterval == 30.f)
			{
				m_AttackEnemy = LEFT_ENEMY_ATTACK;
				m_AttackInterval = 0;
			}
		}
		if (m_AttackEnemy == LEFT_ENEMY_ATTACK)
		{
			SINGLETON_INSTANCE(KnifeManager).
				ThrowKnife(&D3DXVECTOR2(*m_PosLeft, 576), GameDataManager::LEFT_ENEMY_TARGET, GameDataManager::PLAYER_TARGET, ThrowSpeed(m_LeftEnemyCount, 0));
			m_AttackEnemy = NOT_ENEMY_ATTACK;
			m_LeftEnemyAttack = false;
		}
	}
	else if (m_EnemyLoad[m_LeftEnemyCount][0] == 0 && m_LeftEnemyHits == true)
	{
		m_AttackEnemy = NOT_ENEMY_ATTACK;
		m_AttackTime += 120;
	}
	
	if (m_EnemyLoad[m_CenterEnemyCount][1] > 0 && m_CenterEnemyHits == false)
	{
		if (AttackTurn(m_CenterEnemyCount, 1) == FIRST_ATTACK && m_AttackTime == 30)
		{
			m_CenterEnemyAttack = true;			
		}
		else if (AttackTurn(m_CenterEnemyCount, 1) == SECOND_ATTACK && m_AttackTime == 140)
		{
			//m_AttackEnemy = CENTER_ENEMY_ATTACK;
			m_CenterEnemyAttack = true;
		}
		else if (AttackTurn(m_CenterEnemyCount, 1) == THIRD_ATTACK && m_AttackTime == 260)
		{
			//m_AttackEnemy = CENTER_ENEMY_ATTACK;
			m_CenterEnemyAttack = true;
		}
		if (m_CenterEnemyAttack == true)
		{
			m_AttackInterval += 1.f;
			if (m_AttackInterval == 30.f)
			{
				m_AttackEnemy = CENTER_ENEMY_ATTACK;
				m_AttackInterval = 0;
			}
		}
		if (m_AttackEnemy == CENTER_ENEMY_ATTACK)
		{
			SINGLETON_INSTANCE(KnifeManager).
				ThrowKnife(&D3DXVECTOR2(*m_PosCenter, 576), GameDataManager::FRONT_ENEMY_TARGET, GameDataManager::PLAYER_TARGET, ThrowSpeed(m_CenterEnemyCount, 1));
			m_AttackEnemy = NOT_ENEMY_ATTACK;
			m_CenterEnemyAttack = false;
		}
	}
	else if (m_EnemyLoad[m_CenterEnemyCount][1] == 0 && m_CenterEnemyHits == true)
	{
		m_AttackEnemy = NOT_ENEMY_ATTACK;
		m_AttackTime += 120.f;
	}
	
	if (m_EnemyLoad[m_RightEnemyCount][2] > 0 && m_RightEnemyHits == false)
	{
		if (AttackTurn(m_RightEnemyCount, 2) == FIRST_ATTACK && m_AttackTime == 30)
		{
			//m_AttackEnemy = RIGHT_ENEMY_ATTACK;
			m_RightEnemyAttack = true;
		}
		else if (AttackTurn(m_RightEnemyCount, 2) == SECOND_ATTACK && m_AttackTime == 140)
		{
			//m_AttackEnemy = RIGHT_ENEMY_ATTACK;
			m_RightEnemyAttack = true;
		}
		else if (AttackTurn(m_RightEnemyCount, 2) == THIRD_ATTACK && m_AttackTime == 260)
		{
			//m_AttackEnemy = RIGHT_ENEMY_ATTACK;
			m_RightEnemyAttack = true;
		}
		if (m_RightEnemyAttack == true)
		{
			m_AttackInterval += 1.f;
			if (m_AttackInterval == 30.f)
			{
				m_AttackEnemy = RIGHT_ENEMY_ATTACK;
				m_AttackInterval = 0;
			}
		}
		if (m_AttackEnemy == RIGHT_ENEMY_ATTACK)
		{
			SINGLETON_INSTANCE(KnifeManager).
				ThrowKnife(&D3DXVECTOR2(*m_PosRight, 576), GameDataManager::RIGHT_ENEMY_TARGET, GameDataManager::PLAYER_TARGET, ThrowSpeed(m_RightEnemyCount, 2));
			m_AttackEnemy = NOT_ENEMY_ATTACK;
			m_RightEnemyAttack = false;
		}
	}
	else if (m_EnemyLoad[m_RightEnemyCount][2] == 0 && m_RightEnemyHits == true)
	{
		m_AttackEnemy = NOT_ENEMY_ATTACK;
		m_AttackTime += 120.f;
	}
	
	if (m_AttackTime > 300)
	{
		m_AttackTime = 0;
		m_CenterEnemyAttack = false;
	}
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