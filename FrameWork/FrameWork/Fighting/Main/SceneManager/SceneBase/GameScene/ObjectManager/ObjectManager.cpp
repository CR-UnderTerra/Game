﻿/**
 * @file   ObjectManager.cpp
 * @brief  ObjectManagerクラスの実装
 * @author kotani
 */
#include "ObjectManager.h"
#include "Texture/TextureManager.h"
#include "ObjectBase/GameObjectBase/BackGround/BackGround.h"
#include "ObjectBase/GameObjectBase/Player/Player.h"
#include "ObjectBase/GameObjectBase/KnifeManager/KnifeManager.h"
#include "ObjectBase/UIBase/DistanceGaugeUI/DistanceGaugeUI.h"
#include "ObjectBase/UIBase/HpGaugeUI/HpGaugeUI.h"
#include "ObjectBase/UIBase/TimerUI/TimerUI.h"
#include "ObjectBase/GameObjectBase/EnemyManager/EnemyManager.h"

ObjectManager::ObjectManager()
{
	SINGLETON_INSTANCE(Lib::TextureManager).Load("Resource/test_001.png",&m_TextureIndex1);
	SINGLETON_INSTANCE(Lib::TextureManager).Load("Resource/test_003.png", &m_TextureIndex3);
	SINGLETON_INSTANCE(Lib::TextureManager).Load("Resource/test_001.png", &m_TextureIndex4);
	SINGLETON_CREATE(KnifeManager);
	SINGLETON_INSTANCE(KnifeManager).Init(m_TextureIndex1);

	m_pBackGround = new BackGround(m_TextureIndex3);
	m_pPlayer = new Player(m_TextureIndex1);
	SINGLETON_CREATE(EnemyManager);
	SINGLETON_INSTANCE(EnemyManager).Init(m_TextureIndex4);

	m_pUIBase.push_back(new DistanceGaugeUI(m_TextureIndex1));
	m_pUIBase.push_back(new HpGaugeUI(m_TextureIndex1));
	m_pUIBase.push_back(new TimerUI());
}

ObjectManager::~ObjectManager()
{
	for (int i = m_pUIBase.size() - 1; i >= 0; i--)
	{
		delete m_pUIBase[i];
		m_pUIBase[i] = NULL;
	}

	SINGLETON_DELETE(EnemyManager);
	delete m_pPlayer;
	m_pPlayer = NULL;

	delete m_pBackGround;
	m_pBackGround = NULL;

	SINGLETON_DELETE(KnifeManager);
	SINGLETON_INSTANCE(Lib::TextureManager).ReleaseTexture(m_TextureIndex4);
	SINGLETON_INSTANCE(Lib::TextureManager).ReleaseTexture(m_TextureIndex3);
	SINGLETON_INSTANCE(Lib::TextureManager).ReleaseTexture(m_TextureIndex1);
}


//----------------------------------------------------------------------------------------------------
// Public Functions
//----------------------------------------------------------------------------------------------------

void ObjectManager::Update()
{
	m_pBackGround->Update();
	SINGLETON_INSTANCE(KnifeManager).Update();
	m_pPlayer->Update();
	SINGLETON_INSTANCE(EnemyManager).Update();
	for (unsigned int i = 0; i < m_pUIBase.size(); i++)
	{
		m_pUIBase[i]->Update();
	}
}

void ObjectManager::Draw()
{
	m_pBackGround->Draw();
	SINGLETON_INSTANCE(KnifeManager).Draw();
	m_pPlayer->Draw();
	SINGLETON_INSTANCE(EnemyManager).Draw();
	for (unsigned int i = 0; i < m_pUIBase.size(); i++)
	{
		m_pUIBase[i]->Draw();
	}
}
