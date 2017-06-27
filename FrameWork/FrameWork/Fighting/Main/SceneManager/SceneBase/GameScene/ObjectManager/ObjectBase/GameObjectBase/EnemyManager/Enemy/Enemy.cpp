#include "Enemy.h"
#include<time.h>
#include "Window/Window.h"
#include "Dx11/DX11Manager.h"
#include "Animation/AnimUvController.h"
#include "Texture/TextureManager.h"
#include "../../../../../CollisionManager/CollisionManager.h"
#include "DxInput/KeyBoard/KeyDevice.h"
#include "../../KnifeManager/KnifeManager.h"
#include "Sound/DSoundManager.h"
#include "Event/EventManager.h"

const D3DXVECTOR2 Enemy::m_Rect = D3DXVECTOR2(128, 256);

Enemy::Enemy(int _textureIndex, Lib::AnimUvController* _pUvController) :
m_pEnemy01WaitUvController(_pUvController),
m_pEnemy01AttackUvController(_pUvController),
m_pEnemy02WaitUvController(_pUvController),
m_pEnemy02AttackUvController(_pUvController),
m_pEnemy03WaitUvController(_pUvController),
m_pEnemy03AttackUvController(_pUvController),
m_TextureIndex(_textureIndex),
m_LeftEnemyCount(20),
m_CenterEnemyCount(20),
m_RightEnemyCount(20),
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
m_WaitEnemyAlfa(0.f),
m_AttackEnemyAlfa(0.f),
m_PosLeft{ (760), (576) },
m_PosCenter{ (960), (576) },
m_PosRight{ (1160), (576) }
{
	srand((unsigned int)time(NULL));

	int RandomSelect = rand() % 3;
	switch (RandomSelect)
	{
	case 0:
		EnemyLoad("Resource/EnemyPos1.csv");
		break;
	case 1:
		EnemyLoad("Resource/EnemyPos2.csv");
		break;
	case 2:
		EnemyLoad("Resource/EnemyPos3.csv");
		break;
	}
	//EnemyLoad("Resource/EnemyPos1.csv");
	SINGLETON_INSTANCE(Lib::DSoundManager).LoadSound("Resource/Sound/se/explosionSE_GOOD.wav", &m_GoodExplosionSound);
	SINGLETON_INSTANCE(Lib::DSoundManager).LoadSound("Resource/Sound/se/explosionSE_GOOD.wav", &m_AmazingAndFantasticExplosionSound);
	SINGLETON_INSTANCE(Lib::DSoundManager).LoadSound("Resource/Sound/se/damageVoice_001.wav", &m_DamageVoiceType01);
	SINGLETON_INSTANCE(Lib::DSoundManager).LoadSound("Resource/Sound/se/damageVoice_002.wav", &m_DamageVoiceType02);
	SINGLETON_INSTANCE(Lib::DSoundManager).LoadSound("Resource/Sound/se/damageVoice_003.wav", &m_DamageVoiceType03);
	SINGLETON_INSTANCE(Lib::DSoundManager).LoadSound("Resource/Sound/se/houchouSE_nage.wav", &m_ThrowSound);

	SINGLETON_INSTANCE(GameDataManager).SetLeftEnemyCrowdAlfa(m_LeftEnemyCrowdAlfa);
	SINGLETON_INSTANCE(GameDataManager).SetCenterEnemyCrowdAlfa(m_CenterEnemyCrowdAlfa);
	SINGLETON_INSTANCE(GameDataManager).SetRightEnemyCrowdAlfa(m_RightEnemyCrowdAlfa);

	//爆発描画関連 Start
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

	//爆発描画関連 End

	//敵描画処理 Start
	m_pEnemy01AttackUvController = new Lib::AnimUvController();
	m_pEnemy01WaitUvController = new Lib::AnimUvController();
	m_pEnemy01AttackUvController->LoadAnimation("Resource/test_001.anim", "e_attack01");
	m_pEnemy01WaitUvController->LoadAnimation("Resource/test_001.anim", "e_wait01");
	m_pEnemy02AttackUvController = new Lib::AnimUvController();
	m_pEnemy02WaitUvController = new Lib::AnimUvController();
	m_pEnemy02AttackUvController->LoadAnimation("Resource/test_001.anim", "e_attack02");
	m_pEnemy02WaitUvController->LoadAnimation("Resource/test_001.anim", "e_wait02");
	m_pEnemy03AttackUvController = new Lib::AnimUvController();
	m_pEnemy03WaitUvController = new Lib::AnimUvController();
	m_pEnemy03AttackUvController->LoadAnimation("Resource/test_001.anim", "e_attack03");
	m_pEnemy03WaitUvController->LoadAnimation("Resource/test_001.anim", "e_wait03");
	//m_pAttackUvController = new Lib::AnimUvController();
	//m_pWaitUvController = new Lib::AnimUvController();
	//m_pAttackUvController->LoadAnimation("Resource/test_001.anim", "e_attack01");
	//m_pWaitUvController->LoadAnimation("Resource/test_001.anim", "e_wait01");

	int Random = rand() % 3;
	/*switch (Random)
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
	}*/
	//敵描画処理 End

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
		//m_pLeftEnemyVertex->Init(&m_Rect, m_pWaitUvController->GetUV());
		switch (Random)
		{
		case 0:
			m_pLeftEnemyVertex->Init(&m_Rect, m_pEnemy01WaitUvController->GetUV());
			break;
		case 1:
			m_pLeftEnemyVertex->Init(&m_Rect, m_pEnemy02WaitUvController->GetUV());
			break;
		case 2:
			m_pLeftEnemyVertex->Init(&m_Rect, m_pEnemy03WaitUvController->GetUV());
			break;
		}
		m_pLeftEnemyVertex->SetTexture(
			SINGLETON_INSTANCE(Lib::TextureManager).GetTexture(m_TextureIndex));

		m_LeftEnemyHitState = m_pLeftEnemyCollisionData->GetCollisionState().HitState;

		//m_LeftEnemyCrowdAlfa = 1.0f;
		//SINGLETON_INSTANCE(GameDataManager).SetLeftEnemyCrowdAlfa(m_LeftEnemyCrowdAlfa);
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
		//m_pCenterEnemyVertex->Init(&m_Rect, m_pWaitUvController->GetUV());
		switch (Random)
		{
		case 0:
			m_pCenterEnemyVertex->Init(&m_Rect, m_pEnemy01WaitUvController->GetUV());
			break;
		case 1:
			m_pCenterEnemyVertex->Init(&m_Rect, m_pEnemy02WaitUvController->GetUV());
			break;
		case 2:
			m_pCenterEnemyVertex->Init(&m_Rect, m_pEnemy03WaitUvController->GetUV());
			break;
		}
		m_pCenterEnemyVertex->SetTexture(
			SINGLETON_INSTANCE(Lib::TextureManager).GetTexture(m_TextureIndex));

		m_CenterEnemyHitState = m_pCenterEnemyCollisionData->GetCollisionState().HitState;

		//m_CenterEnemyCrowdAlfa = 1.0f;
		//SINGLETON_INSTANCE(GameDataManager).SetCenterEnemyCrowdAlfa(m_CenterEnemyCrowdAlfa);
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
		//m_pRightEnemyVertex->Init(&m_Rect, m_pWaitUvController->GetUV());
		switch (Random)
		{
		case 0:
			m_pRightEnemyVertex->Init(&m_Rect, m_pEnemy01WaitUvController->GetUV());
			break;
		case 1:
			m_pRightEnemyVertex->Init(&m_Rect, m_pEnemy02WaitUvController->GetUV());
			break;
		case 2:
			m_pRightEnemyVertex->Init(&m_Rect, m_pEnemy03WaitUvController->GetUV());
			break;
		}
		m_pRightEnemyVertex->SetTexture(
			SINGLETON_INSTANCE(Lib::TextureManager).GetTexture(m_TextureIndex));

		m_RightEnemyHitState = m_pRightEnemyCollisionData->GetCollisionState().HitState;

		//m_RightEnemyCrowdAlfa = 1.0f;
		//SINGLETON_INSTANCE(GameDataManager).SetRightEnemyCrowdAlfa(m_RightEnemyCrowdAlfa);
	}

	SINGLETON_INSTANCE(Lib::EventManager).AddEvent("EnemyDamage", [this]()
	{
		m_WidthTime = 30;
	});
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

	delete m_pEnemy01AttackUvController;
	m_pEnemy01AttackUvController = NULL;
	delete m_pEnemy01WaitUvController;
	m_pEnemy01WaitUvController = NULL;
	delete m_pEnemy02AttackUvController;
	m_pEnemy02AttackUvController = NULL;
	delete m_pEnemy02WaitUvController;
	m_pEnemy02WaitUvController = NULL;
	delete m_pEnemy03AttackUvController;
	m_pEnemy03AttackUvController = NULL;
	delete m_pEnemy03WaitUvController;
	m_pEnemy03WaitUvController = NULL;

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

	SINGLETON_INSTANCE(Lib::DSoundManager).ReleaseSound(m_GoodExplosionSound);
	SINGLETON_INSTANCE(Lib::DSoundManager).ReleaseSound(m_AmazingAndFantasticExplosionSound);
	SINGLETON_INSTANCE(Lib::DSoundManager).ReleaseSound(m_DamageVoiceType01);
	SINGLETON_INSTANCE(Lib::DSoundManager).ReleaseSound(m_DamageVoiceType02);
	SINGLETON_INSTANCE(Lib::DSoundManager).ReleaseSound(m_DamageVoiceType03);
	SINGLETON_INSTANCE(Lib::DSoundManager).ReleaseSound(m_ThrowSound);

}

void Enemy::Update()
{
	srand((unsigned int)time(NULL));

	CollisionControl();

	Hit();

	Attack();

	if ((m_EnemyLoad[m_LeftEnemyCount][0] == 0) &&
		(m_EnemyLoad[m_CenterEnemyCount][1] == 0) &&
		(m_EnemyLoad[m_RightEnemyCount][2] == 0))
	{
		m_Random1 = rand() % 3;
		m_Random2 = rand() % 3;
		m_Random3 = rand() % 3;

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

		m_AttackTime = 0.f;
		m_WaitEnemyAlfa = 0.f;
		m_GoodHit = m_AmazingHit = m_FantasticHit = false;
	}

	if (m_EnemyLoad[m_LeftEnemyCount][0] > 0)
	{
		m_pLeftEnemyCollisionData->SetEnable(true);

		m_LeftEnemyCrowdAlfa += 0.01f;
		m_WaitEnemyAlfa += 0.01f;
		m_AttackEnemyAlfa += 0.01f;
		SINGLETON_INSTANCE(GameDataManager).SetLeftEnemyCrowdAlfa(m_LeftEnemyCrowdAlfa);
	}

	if (m_EnemyLoad[m_CenterEnemyCount][1] > 0)
	{
		m_pCenterEnemyCollisionData->SetEnable(true);

		m_CenterEnemyCrowdAlfa += 0.01f;
		m_WaitEnemyAlfa += 0.01f;
		m_AttackEnemyAlfa += 0.01f;
		SINGLETON_INSTANCE(GameDataManager).SetCenterEnemyCrowdAlfa(m_CenterEnemyCrowdAlfa);
	}

	if (m_EnemyLoad[m_RightEnemyCount][2] > 0)
	{
		m_pRightEnemyCollisionData->SetEnable(true);

		m_RightEnemyCrowdAlfa += 0.01f;
		m_WaitEnemyAlfa += 0.01f;
		m_AttackEnemyAlfa += 0.01f;
		SINGLETON_INSTANCE(GameDataManager).SetRightEnemyCrowdAlfa(m_RightEnemyCrowdAlfa);
	}
	
	if (m_CenterEnemyHits == true || m_LeftEnemyHits == true || m_RightEnemyHits == true)
	{
		m_HitInterval += 1.0f;

		int Random = rand() % 3;

		switch (Random)
		{
		case 0:
			SINGLETON_INSTANCE(Lib::DSoundManager).SoundOperation(m_DamageVoiceType01, Lib::DSoundManager::SOUND_PLAY);
			break;
		case 1:
			SINGLETON_INSTANCE(Lib::DSoundManager).SoundOperation(m_DamageVoiceType02, Lib::DSoundManager::SOUND_PLAY);
			break;
		case 2:
			SINGLETON_INSTANCE(Lib::DSoundManager).SoundOperation(m_DamageVoiceType03, Lib::DSoundManager::SOUND_PLAY);
			break;
		}
	}

	if (m_LeftEnemyCount == 0 && m_CenterEnemyCount == 0 && m_RightEnemyCount == 0)
	{
		SINGLETON_INSTANCE(GameDataManager).SetIsGameOver(true);
	}

	SINGLETON_INSTANCE(GameDataManager).SetCurrentEnemyLine(m_CenterEnemyCount);
}

void Enemy::Draw()
{
	//int Random = rand() % 3;
	Vibration();

	if (m_EnemyLoad[m_LeftEnemyCount][0] > 0)
	{
		if (m_LeftEnemyHits == false)
		{
			if (m_LeftEnemyAttack == false)
			{
				switch (m_Random1)
				{
				case 0:
					m_pLeftEnemyVertex->Draw(&D3DXVECTOR2(m_PosLeft.x + m_WidthVibValue, m_PosLeft.y), m_pEnemy01WaitUvController->GetUV(), m_WaitEnemyAlfa);
					break;
				case 1:
					m_pLeftEnemyVertex->Draw(&D3DXVECTOR2(m_PosLeft.x + m_WidthVibValue, m_PosLeft.y), m_pEnemy02WaitUvController->GetUV(), m_WaitEnemyAlfa);
					break;
				case 2:
					m_pLeftEnemyVertex->Draw(&D3DXVECTOR2(m_PosLeft.x + m_WidthVibValue, m_PosLeft.y), m_pEnemy03WaitUvController->GetUV(), m_WaitEnemyAlfa);
					break;
				}

				//m_pLeftEnemyVertex->Draw(&m_PosLeft, m_pWaitUvController->GetUV(), m_WaitEnemyAlfa);
			}
			if (m_LeftEnemyAttack == true)
			{
				switch (m_Random1)
				{
				case 0:
					m_pLeftEnemyVertex->Draw(&D3DXVECTOR2(m_PosLeft.x + m_WidthVibValue, m_PosLeft.y), m_pEnemy01AttackUvController->GetUV(), m_AttackEnemyAlfa);
					break;
				case 1:
					m_pLeftEnemyVertex->Draw(&D3DXVECTOR2(m_PosLeft.x + m_WidthVibValue, m_PosLeft.y), m_pEnemy02AttackUvController->GetUV(), m_AttackEnemyAlfa);
					break;
				case 2:
					m_pLeftEnemyVertex->Draw(&D3DXVECTOR2(m_PosLeft.x + m_WidthVibValue, m_PosLeft.y), m_pEnemy03AttackUvController->GetUV(), m_AttackEnemyAlfa);
					break;
				}
				//m_pLeftEnemyVertex->Draw(&m_PosLeft, m_pAttackUvController->GetUV(), m_AttackEnemyAlfa);
			}

			SINGLETON_INSTANCE(GameDataManager).SetLeftEnemyCrowdAlfa(m_LeftEnemyCrowdAlfa);
			EnemyExplosionDraw(m_PosLeft, 0.f, EXPLOSION_MAX);
		}
		else if (m_LeftEnemyHits == true)
		{
			m_ExplosionTime += 0.1f;
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
				switch (m_Random2)
				{
				case 0:
					m_pCenterEnemyVertex->Draw(&D3DXVECTOR2(m_PosCenter.x + m_WidthVibValue, m_PosCenter.y), m_pEnemy01WaitUvController->GetUV(), m_WaitEnemyAlfa);
					break;
				case 1:
					m_pCenterEnemyVertex->Draw(&D3DXVECTOR2(m_PosCenter.x + m_WidthVibValue, m_PosCenter.y), m_pEnemy02WaitUvController->GetUV(), m_WaitEnemyAlfa);
					break;
				case 2:
					m_pCenterEnemyVertex->Draw(&D3DXVECTOR2(m_PosCenter.x + m_WidthVibValue, m_PosCenter.y), m_pEnemy03WaitUvController->GetUV(), m_WaitEnemyAlfa);
					break;
				}
				//m_pCenterEnemyVertex->Draw(&m_PosCenter, m_pWaitUvController->GetUV(), m_WaitEnemyAlfa);
			}
			if (m_CenterEnemyAttack == true)
			{
				switch (m_Random2)
				{
				case 0:
					m_pCenterEnemyVertex->Draw(&D3DXVECTOR2(m_PosCenter.x + m_WidthVibValue, m_PosCenter.y), m_pEnemy01AttackUvController->GetUV(), m_AttackEnemyAlfa);
					break;
				case 1:
					m_pCenterEnemyVertex->Draw(&D3DXVECTOR2(m_PosCenter.x + m_WidthVibValue, m_PosCenter.y), m_pEnemy02AttackUvController->GetUV(), m_AttackEnemyAlfa);
					break;
				case 2:
					m_pCenterEnemyVertex->Draw(&D3DXVECTOR2(m_PosCenter.x + m_WidthVibValue, m_PosCenter.y), m_pEnemy03AttackUvController->GetUV(), m_AttackEnemyAlfa);
					break;
				}
				//m_pCenterEnemyVertex->Draw(&m_PosCenter, m_pAttackUvController->GetUV(), m_AttackEnemyAlfa);
			}

			SINGLETON_INSTANCE(GameDataManager).SetCenterEnemyCrowdAlfa(m_CenterEnemyCrowdAlfa);
			EnemyExplosionDraw(m_PosCenter, 0.f, EXPLOSION_MAX);
		}
		else if (m_CenterEnemyHits)
		{
			m_ExplosionTime += 0.1f;
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
				switch (m_Random3)
				{
				case 0:
					m_pRightEnemyVertex->Draw(&D3DXVECTOR2(m_PosRight.x + m_WidthVibValue, m_PosRight.y), m_pEnemy01WaitUvController->GetUV(), m_WaitEnemyAlfa);
					break;
				case 1:
					m_pRightEnemyVertex->Draw(&D3DXVECTOR2(m_PosRight.x + m_WidthVibValue, m_PosRight.y), m_pEnemy02WaitUvController->GetUV(), m_WaitEnemyAlfa);
					break;
				case 2:
					m_pRightEnemyVertex->Draw(&D3DXVECTOR2(m_PosRight.x + m_WidthVibValue, m_PosRight.y), m_pEnemy03WaitUvController->GetUV(), m_WaitEnemyAlfa);
					break;
				}
				//m_pRightEnemyVertex->Draw(&m_PosRight, m_pWaitUvController->GetUV(), m_WaitEnemyAlfa);
			}
			if (m_RightEnemyAttack == true)
			{
				switch (m_Random3)
				{
				case 0:
					m_pRightEnemyVertex->Draw(&D3DXVECTOR2(m_PosRight.x + m_WidthVibValue, m_PosRight.y), m_pEnemy01AttackUvController->GetUV(), m_AttackEnemyAlfa);
					break;
				case 1:
					m_pRightEnemyVertex->Draw(&D3DXVECTOR2(m_PosRight.x + m_WidthVibValue, m_PosRight.y), m_pEnemy02AttackUvController->GetUV(), m_AttackEnemyAlfa);
					break;
				case 2:
					m_pRightEnemyVertex->Draw(&D3DXVECTOR2(m_PosRight.x + m_WidthVibValue, m_PosRight.y), m_pEnemy03AttackUvController->GetUV(), m_AttackEnemyAlfa);
					break;
				}
				//m_pRightEnemyVertex->Draw(&m_PosRight, m_pAttackUvController->GetUV(), m_AttackEnemyAlfa);
			}

			SINGLETON_INSTANCE(GameDataManager).SetRightEnemyCrowdAlfa(m_RightEnemyCrowdAlfa);
			EnemyExplosionDraw(m_PosRight, 0.f, EXPLOSION_MAX);
		}
		else if (m_RightEnemyHits == true)
		{
			m_ExplosionTime += 0.1f;
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
#ifdef _DEBUG
	SINGLETON_INSTANCE(Lib::KeyDevice).KeyCheck(DIK_1);
	SINGLETON_INSTANCE(Lib::KeyDevice).KeyCheck(DIK_2);
	SINGLETON_INSTANCE(Lib::KeyDevice).KeyCheck(DIK_3);

	if (SINGLETON_INSTANCE(Lib::KeyDevice).GetKeyState()[DIK_1] == Lib::KEY_ON)
	{
		m_AmazingHit = true;
		m_LeftEnemyHits = true;
	}
	if (SINGLETON_INSTANCE(Lib::KeyDevice).GetKeyState()[DIK_2] == Lib::KEY_ON)
	{
		m_AmazingHit = true;
		m_CenterEnemyHits = true;
	}
	if (SINGLETON_INSTANCE(Lib::KeyDevice).GetKeyState()[DIK_3] == Lib::KEY_ON)
	{
		m_AmazingHit = true;
		m_RightEnemyHits = true;
	}
#endif
	if (m_LeftEnemyHits == true && m_HitInterval == HITINTERVAL)
	{
		m_HitInterval = 0;
		m_LeftEnemyHits = false;
		m_EnemyLoad[m_LeftEnemyCount][0] = 0;
		EnemyExplosionDraw(m_PosLeft, 0.f, EXPLOSION_MAX);
		m_ExplosionTime = 0.f;

		m_LeftEnemyCrowdAlfa = 0.f;
		SINGLETON_INSTANCE(GameDataManager).SetLeftEnemyCrowdAlfa(m_LeftEnemyCrowdAlfa);
	}
	if (m_CenterEnemyHits == true && m_HitInterval == HITINTERVAL)
	{
		m_HitInterval = 0;
		m_CenterEnemyHits = false;
		m_EnemyLoad[m_CenterEnemyCount][1] = 0;
		EnemyExplosionDraw(m_PosCenter, 0.f, EXPLOSION_MAX);
		m_ExplosionTime = 0.f;

		m_CenterEnemyCrowdAlfa = 0.f;
		SINGLETON_INSTANCE(GameDataManager).SetCenterEnemyCrowdAlfa(m_CenterEnemyCrowdAlfa);
	}
	if (m_RightEnemyHits == true && m_HitInterval == HITINTERVAL)
	{
		m_HitInterval = 0;
		m_RightEnemyHits = false;
		m_EnemyLoad[m_RightEnemyCount][2] = 0;
		EnemyExplosionDraw(m_PosRight, 0.f, EXPLOSION_MAX);
		m_ExplosionTime = 0.f;

		m_RightEnemyCrowdAlfa = 0.f;
		SINGLETON_INSTANCE(GameDataManager).SetRightEnemyCrowdAlfa(m_RightEnemyCrowdAlfa);
	}

}

//敵と手紙の衝突判定処理
void Enemy::CollisionControl()
{
	if (m_EnemyLoad[m_LeftEnemyCount][0] > 0)
	{
		m_pLeftEnemyCollisionData->SetEnable(true);

		CollisionData::HIT_STATE m_LeftEnemyHitState = m_pLeftEnemyCollisionData->GetCollisionState().HitState;
		if (m_LeftEnemyHitState == CollisionData::GOOD_HIT)
		{
			m_GoodHit = true;
			SINGLETON_INSTANCE(Lib::DSoundManager).SoundOperation(m_GoodExplosionSound, Lib::DSoundManager::SOUND_PLAY);
		}
		if (m_LeftEnemyHitState == CollisionData::AMAZING_HIT)
		{
			m_AmazingHit = true;
			SINGLETON_INSTANCE(Lib::DSoundManager).SoundOperation(m_AmazingAndFantasticExplosionSound, Lib::DSoundManager::SOUND_PLAY);
		}
		if (m_LeftEnemyHitState == CollisionData::FANTASTIC_HIT)
		{
			m_FantasticHit = true;
			SINGLETON_INSTANCE(Lib::DSoundManager).SoundOperation(m_AmazingAndFantasticExplosionSound, Lib::DSoundManager::SOUND_PLAY);
		}
		if (m_LeftEnemyHitState == CollisionData::GOOD_HIT ||
			m_LeftEnemyHitState == CollisionData::FANTASTIC_HIT ||
			m_LeftEnemyHitState == CollisionData::AMAZING_HIT)
		{
			//m_ExplosionTime += 0.5f;
			m_pLeftEnemyCollisionData->SetEnable(false);
			m_LeftEnemyHits = true;
			//SINGLETON_INSTANCE(Lib::DSoundManager).SoundOperation(m_DamageVoiceType01, Lib::DSoundManager::SOUND_PLAY);
		}
	}
	if (m_EnemyLoad[m_CenterEnemyCount][1] > 0)
	{
		m_pCenterEnemyCollisionData->SetEnable(true);

		CollisionData::HIT_STATE m_CenterEnemyHitState = m_pCenterEnemyCollisionData->GetCollisionState().HitState;
		if (m_CenterEnemyHitState == CollisionData::GOOD_HIT)
		{
			m_GoodHit = true;
			SINGLETON_INSTANCE(Lib::DSoundManager).SoundOperation(m_GoodExplosionSound, Lib::DSoundManager::SOUND_PLAY);
		}
		if (m_CenterEnemyHitState == CollisionData::AMAZING_HIT)
		{
			m_AmazingHit = true;
			SINGLETON_INSTANCE(Lib::DSoundManager).SoundOperation(m_AmazingAndFantasticExplosionSound, Lib::DSoundManager::SOUND_PLAY);
		}
		if (m_CenterEnemyHitState == CollisionData::FANTASTIC_HIT)
		{
			m_FantasticHit = true;
			SINGLETON_INSTANCE(Lib::DSoundManager).SoundOperation(m_AmazingAndFantasticExplosionSound, Lib::DSoundManager::SOUND_PLAY);
		}
		if (m_CenterEnemyHitState == CollisionData::GOOD_HIT ||
			m_CenterEnemyHitState == CollisionData::FANTASTIC_HIT ||
			m_CenterEnemyHitState == CollisionData::AMAZING_HIT)
		{
			//m_ExplosionTime += 0.5f;
			m_pCenterEnemyCollisionData->SetEnable(false);
			m_CenterEnemyHits = true;
			//SINGLETON_INSTANCE(Lib::DSoundManager).SoundOperation(m_DamageVoiceType01, Lib::DSoundManager::SOUND_PLAY);
		}
	}
	if (m_EnemyLoad[m_RightEnemyCount][2] > 0)
	{
		m_pRightEnemyCollisionData->SetEnable(true);

		CollisionData::HIT_STATE m_RightEnemyHitState = m_pRightEnemyCollisionData->GetCollisionState().HitState;
		if (m_RightEnemyHitState == CollisionData::GOOD_HIT)
		{
			m_GoodHit = true;
			SINGLETON_INSTANCE(Lib::DSoundManager).SoundOperation(m_GoodExplosionSound, Lib::DSoundManager::SOUND_PLAY);
		}
		if (m_RightEnemyHitState == CollisionData::AMAZING_HIT)
		{
			m_AmazingHit = true;
			SINGLETON_INSTANCE(Lib::DSoundManager).SoundOperation(m_AmazingAndFantasticExplosionSound, Lib::DSoundManager::SOUND_PLAY);
		}
		if (m_RightEnemyHitState == CollisionData::FANTASTIC_HIT)
		{
			m_FantasticHit = true;
			SINGLETON_INSTANCE(Lib::DSoundManager).SoundOperation(m_AmazingAndFantasticExplosionSound, Lib::DSoundManager::SOUND_PLAY);
		}
		if (m_RightEnemyHitState == CollisionData::GOOD_HIT ||
			m_RightEnemyHitState == CollisionData::FANTASTIC_HIT ||
			m_RightEnemyHitState == CollisionData::AMAZING_HIT)
		{
			//m_ExplosionTime += 0.5f;
			m_pRightEnemyCollisionData->SetEnable(false);
			m_RightEnemyHits = true;
			//SINGLETON_INSTANCE(Lib::DSoundManager).SoundOperation(m_DamageVoiceType01, Lib::DSoundManager::SOUND_PLAY);
		}
	}
}

void Enemy::EnemyExplosionDraw(D3DXVECTOR2 pos_, float alpha_, EXPLOSION_TYPE explosiontype_)
{
	switch (explosiontype_)
	{
	case GOOD_EXPLOSION:
		m_pEnemyGoodExplosionVertex->Draw(&D3DXVECTOR2(pos_.x, pos_.y - (m_Rect.y * m_ExplosionTime / 2 - 256) / 2), m_pEnemyGoodExplosionUvController->GetUV(), alpha_,
			&D3DXVECTOR2(m_ExplosionTime / 2, m_ExplosionTime / 2));
		break;
	case AMAZING_EXPLOSION:
		m_pEnemyAmazingExplosionVertex->Draw(&D3DXVECTOR2(pos_.x, pos_.y - (m_Rect.y * m_ExplosionTime - 256) / 2), m_pEnemyAmazingExplosionUvController->GetUV(), alpha_,
			/*&D3DXVECTOR2(1.5f, 1.f)*/&D3DXVECTOR2(m_ExplosionTime, m_ExplosionTime));
		break;
	case FANTASTIC_EXPLOSION:
		m_pEnemyFantasticExplosionVertex->Draw(&D3DXVECTOR2(pos_.x, pos_.y - (m_Rect.y * m_ExplosionTime - 256) / 2), m_pEnemyFantasticExplosionUvController->GetUV(), alpha_,
			/*&D3DXVECTOR2(1.5f, 1.5f)*/&D3DXVECTOR2(m_ExplosionTime, m_ExplosionTime));
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
		if (AttackTurn(m_LeftEnemyCount, 0) == FIRST_ATTACK && m_AttackTime == 60)
		{
			m_LeftEnemyAttack = true;
		}
		else if (AttackTurn(m_LeftEnemyCount, 0) == SECOND_ATTACK && m_AttackTime == 170)
		{
			m_LeftEnemyAttack = true;
		}
		else if (AttackTurn(m_LeftEnemyCount, 0) == THIRD_ATTACK && m_AttackTime == 270)
		{
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
			SINGLETON_INSTANCE(Lib::DSoundManager).SoundOperation(m_ThrowSound, Lib::DSoundManager::SOUND_PLAY);
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
		if (AttackTurn(m_CenterEnemyCount, 1) == FIRST_ATTACK && m_AttackTime == 60)
		{
			m_CenterEnemyAttack = true;
		}
		else if (AttackTurn(m_CenterEnemyCount, 1) == SECOND_ATTACK && m_AttackTime == 170)
		{
			m_CenterEnemyAttack = true;
		}
		else if (AttackTurn(m_CenterEnemyCount, 1) == THIRD_ATTACK && m_AttackTime == 270)
		{
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
			SINGLETON_INSTANCE(Lib::DSoundManager).SoundOperation(m_ThrowSound, Lib::DSoundManager::SOUND_PLAY);
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
		if (AttackTurn(m_RightEnemyCount, 2) == FIRST_ATTACK && m_AttackTime == 60)
		{
			m_RightEnemyAttack = true;
		}
		else if (AttackTurn(m_RightEnemyCount, 2) == SECOND_ATTACK && m_AttackTime == 170)
		{
			m_RightEnemyAttack = true;
		}
		else if (AttackTurn(m_RightEnemyCount, 2) == THIRD_ATTACK && m_AttackTime == 270)
		{
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
			SINGLETON_INSTANCE(Lib::DSoundManager).SoundOperation(m_ThrowSound, Lib::DSoundManager::SOUND_PLAY);
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
		return 0.7f;
		break;
	case 3:
		return 1.80f;
		break;
	case 4:
		return 1.60f;
		break;
	}
}