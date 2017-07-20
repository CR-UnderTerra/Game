﻿#include "Enemy.h"
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
m_pWaitUvController(_pUvController),
m_pAttackUvController(_pUvController),
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
	m_pEnemyExplosionUvController = new Lib::AnimUvController();
	m_pEnemyExplosionVertex = new Lib::Vertex2D(
		SINGLETON_INSTANCE(Lib::DX11Manager).GetDevice(),
		SINGLETON_INSTANCE(Lib::DX11Manager).GetDeviceContext(),
		SINGLETON_INSTANCE(Lib::Window).GetWindowSize());
	m_pEnemyExplosionVertex->Init(&m_Rect, m_pEnemyExplosionUvController->GetUV());
	m_pEnemyExplosionVertex->SetTexture(
		SINGLETON_INSTANCE(Lib::TextureManager).GetTexture(m_TextureIndex));
	//爆発描画関連 End

	//敵描画処理 Start
	m_pAttackUvController = new Lib::AnimUvController();
	m_pWaitUvController = new Lib::AnimUvController();

	int Random = rand() % 3;

	EnemyWaitUvInit(Random);
	EnemyAttackUvInit(Random);

	//敵描画処理 End

	if (m_EnemyLoad[m_LeftEnemyCount][0] >= 0)
	{
		EnemyPosInit(&m_pLeftEnemyCollisionData, m_PosLeft, &m_pLeftEnemyVertex, m_LeftEnemyHitState);
	}

	if (m_EnemyLoad[m_CenterEnemyCount][1] >= 0)
	{
		EnemyPosInit(&m_pCenterEnemyCollisionData, m_PosCenter, &m_pCenterEnemyVertex, m_CenterEnemyHitState);
	}

	if (m_EnemyLoad[m_RightEnemyCount][2] >= 0)
	{
		EnemyPosInit(&m_pRightEnemyCollisionData, m_PosRight, &m_pRightEnemyVertex, m_RightEnemyHitState);
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

	delete m_pEnemyExplosionUvController;
	m_pEnemyExplosionUvController = NULL;

	delete m_pWaitUvController;
	m_pWaitUvController = NULL;
	delete m_pAttackUvController;
	m_pAttackUvController = NULL;

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
			EnemyWaitUvInit(m_Random1);
			EnemyAttackUvInit(m_Random1);
		}
		if (m_CenterEnemyCount > 0)
		{
			m_CenterEnemyCount -= 1;
			EnemyWaitUvInit(m_Random2);
			EnemyAttackUvInit(m_Random2);
		}
		if (m_RightEnemyCount > 0)
		{
			m_RightEnemyCount -= 1;
			EnemyWaitUvInit(m_Random3);
			EnemyAttackUvInit(m_Random3);
		}

		m_AttackTime = 0.f;
		m_WaitEnemyAlfa = 0.f;
		m_GoodHit = m_AmazingHit = m_FantasticHit = false;
	}

	if (m_EnemyLoad[m_LeftEnemyCount][0] > 0)
	{
		m_pLeftEnemyCollisionData->SetEnable(true);

		m_LeftEnemyCrowdAlfa += 0.01f;
		m_WaitEnemyAlfa		 += 0.01f;
		m_AttackEnemyAlfa	 += 0.01f;
		SINGLETON_INSTANCE(GameDataManager).SetLeftEnemyCrowdAlfa(m_LeftEnemyCrowdAlfa);
	}

	if (m_EnemyLoad[m_CenterEnemyCount][1] > 0)
	{
		m_pCenterEnemyCollisionData->SetEnable(true);

		m_CenterEnemyCrowdAlfa += 0.01f;
		m_WaitEnemyAlfa		   += 0.01f;
		m_AttackEnemyAlfa	   += 0.01f;
		SINGLETON_INSTANCE(GameDataManager).SetCenterEnemyCrowdAlfa(m_CenterEnemyCrowdAlfa);
	}

	if (m_EnemyLoad[m_RightEnemyCount][2] > 0)
	{
		m_pRightEnemyCollisionData->SetEnable(true);

		m_RightEnemyCrowdAlfa += 0.01f;
		m_WaitEnemyAlfa		  += 0.01f;
		m_AttackEnemyAlfa	  += 0.01f;
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
	Vibration();

	if (m_EnemyLoad[m_LeftEnemyCount][0] > 0)
	{
		EnemyDrawInit(m_LeftEnemyHits, m_LeftEnemyAttack, m_Random1, &m_pLeftEnemyVertex, m_PosLeft);	
	}
	if (m_EnemyLoad[m_LeftEnemyCount][0] == 0)
	{
		m_LeftEnemyCrowdAlfa = 0.f;
		SINGLETON_INSTANCE(GameDataManager).SetLeftEnemyCrowdAlfa(m_LeftEnemyCrowdAlfa);
	}

	if (m_EnemyLoad[m_CenterEnemyCount][1] > 0)
	{
		EnemyDrawInit(m_CenterEnemyHits, m_CenterEnemyAttack, m_Random2, &m_pCenterEnemyVertex, m_PosCenter);
	}
	if (m_EnemyLoad[m_CenterEnemyCount][1] == 0)
	{
		m_CenterEnemyCrowdAlfa = 0.f;
		SINGLETON_INSTANCE(GameDataManager).SetCenterEnemyCrowdAlfa(m_CenterEnemyCrowdAlfa);
	}

	if (m_EnemyLoad[m_RightEnemyCount][2] > 0)
	{
		EnemyDrawInit(m_RightEnemyHits, m_RightEnemyAttack, m_Random3, &m_pRightEnemyVertex, m_PosRight);
	}
	if (m_EnemyLoad[m_RightEnemyCount][0] == 0)
	{
		m_RightEnemyCrowdAlfa = 0.f;
		SINGLETON_INSTANCE(GameDataManager).SetRightEnemyCrowdAlfa(m_RightEnemyCrowdAlfa);
	}
}

void Enemy::EnemyDrawInit(bool enemyhit_, bool enemyattack_, int random_, Lib::Vertex2D** vertex_, D3DXVECTOR2 pos_)
{
	if (enemyhit_ == false && enemyattack_ == false)
	{
		EnemyWaitUvInit(random_);
		(*vertex_)->Draw(&D3DXVECTOR2(pos_.x + m_WidthVibValue, pos_.y), m_pWaitUvController->GetUV(), m_WaitEnemyAlfa);
	}
	else if (enemyhit_ == false && enemyattack_ == true)
	{
		EnemyAttackUvInit(random_);
		(*vertex_)->Draw(&D3DXVECTOR2(pos_.x + m_WidthVibValue, pos_.y), m_pAttackUvController->GetUV(), m_AttackEnemyAlfa);
	}
	else if (enemyhit_ == true)
	{
		m_ExplosionTime += 0.1f;
	}
	if (enemyhit_ == true && m_GoodHit == true)
	{
		EnemyExplosionDraw(pos_, 1.f, GOOD_EXPLOSION);
	}
	else if (enemyhit_ == true && m_AmazingHit == true)
	{
		EnemyExplosionDraw(pos_, 1.f, AMAZING_EXPLOSION);
	}
	else if (enemyhit_ == true && m_FantasticHit == true)
	{
		EnemyExplosionDraw(pos_, 1.f, FANTASTIC_EXPLOSION);
	}
}

void Enemy::EnemyPosInit(CollisionData** _pcollisiondata, D3DXVECTOR2 _pos, Lib::Vertex2D** _vertex, CollisionData::HIT_STATE _hitstate)
{
	*_pcollisiondata = new CollisionData();
	(*_pcollisiondata)->SetEnable(false);
	(*_pcollisiondata)->SetCollision(&D3DXVECTOR3(_pos), &m_Rect, CollisionData::ENEMY_TYPE);
	SINGLETON_INSTANCE(CollisionManager).AddCollision(*_pcollisiondata);

	*_vertex = new Lib::Vertex2D(
		SINGLETON_INSTANCE(Lib::DX11Manager).GetDevice(),
		SINGLETON_INSTANCE(Lib::DX11Manager).GetDeviceContext(),
		SINGLETON_INSTANCE(Lib::Window).GetWindowSize());

	(*_vertex)->Init(&m_Rect, m_pWaitUvController->GetUV());

	(*_vertex)->SetTexture(
		SINGLETON_INSTANCE(Lib::TextureManager).GetTexture(m_TextureIndex));

	_hitstate = (*_pcollisiondata)->GetCollisionState().HitState;
}

void Enemy::EnemyWaitUvInit(int random_)
{
	switch (random_)
	{
	case 0:
		m_pWaitUvController->LoadAnimation("Resource/test_001.anim", "e_wait01");
		break;
	case 1:
		m_pWaitUvController->LoadAnimation("Resource/test_001.anim", "e_wait02");
		break;
	case 2:
		m_pWaitUvController->LoadAnimation("Resource/test_001.anim", "e_wait03");
		break;
	}
}

void Enemy::EnemyAttackUvInit(int random_)
{
	switch (random_)
	{
	case 0:
		m_pAttackUvController->LoadAnimation("Resource/test_001.anim", "e_attack01");
		break;
	case 1:
		m_pAttackUvController->LoadAnimation("Resource/test_001.anim", "e_attack02");
		break;
	case 2:
		m_pAttackUvController->LoadAnimation("Resource/test_001.anim", "e_attack03");
		break;
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
		m_pEnemyExplosionUvController->LoadAnimation("Resource/test_001.anim", "e_bom_g");
		m_pEnemyExplosionVertex->Draw(&D3DXVECTOR2(pos_.x, pos_.y - (m_Rect.y * m_ExplosionTime / 2 - 256) / 2),
			m_pEnemyExplosionUvController->GetUV(), alpha_,&D3DXVECTOR2(m_ExplosionTime / 2, m_ExplosionTime / 2));
		break;
	case AMAZING_EXPLOSION:
		m_pEnemyExplosionUvController->LoadAnimation("Resource/test_001.anim", "e_bom_a");
		m_pEnemyExplosionVertex->Draw(&D3DXVECTOR2(pos_.x, pos_.y - (m_Rect.y * m_ExplosionTime - 256) / 2),
			m_pEnemyExplosionUvController->GetUV(), alpha_, &D3DXVECTOR2(m_ExplosionTime, m_ExplosionTime));
		break;
	case FANTASTIC_EXPLOSION:
		m_pEnemyExplosionUvController->LoadAnimation("Resource/test_001.anim", "e_bom_f");
		m_pEnemyExplosionVertex->Draw(&D3DXVECTOR2(pos_.x, pos_.y - (m_Rect.y * m_ExplosionTime - 256) / 2),
			m_pEnemyExplosionUvController->GetUV(), alpha_,&D3DXVECTOR2(m_ExplosionTime, m_ExplosionTime));
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
		if (AttackTurn(m_LeftEnemyCount, 0) == FIRST_ATTACK && m_AttackTime == FIRSTATTACKTIME)
		{
			m_LeftEnemyAttack = true;
		}
		else if (AttackTurn(m_LeftEnemyCount, 0) == SECOND_ATTACK && m_AttackTime == SECONDATTACKTIME)
		{
			m_LeftEnemyAttack = true;
		}
		else if (AttackTurn(m_LeftEnemyCount, 0) == THIRD_ATTACK && m_AttackTime == THIRDATTACKTIME)
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
		if (AttackTurn(m_CenterEnemyCount, 1) == FIRST_ATTACK && m_AttackTime == FIRSTATTACKTIME)
		{
			m_CenterEnemyAttack = true;
		}
		else if (AttackTurn(m_CenterEnemyCount, 1) == SECOND_ATTACK && m_AttackTime == SECONDATTACKTIME)
		{
			m_CenterEnemyAttack = true;
		}
		else if (AttackTurn(m_CenterEnemyCount, 1) == THIRD_ATTACK && m_AttackTime == THIRDATTACKTIME)
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
		if (AttackTurn(m_RightEnemyCount, 2) == FIRST_ATTACK && m_AttackTime == FIRSTATTACKTIME)
		{
			m_RightEnemyAttack = true;
		}
		else if (AttackTurn(m_RightEnemyCount, 2) == SECOND_ATTACK && m_AttackTime == SECONDATTACKTIME)
		{
			m_RightEnemyAttack = true;
		}
		else if (AttackTurn(m_RightEnemyCount, 2) == THIRD_ATTACK && m_AttackTime == THIRDATTACKTIME)
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

	if (m_AttackTime > 200)
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