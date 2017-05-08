/**
 * @file   ObjectManager.cpp
 * @brief  ObjectManagerクラスの実装
 * @author kotani
 */
#include "ObjectManager.h"
#include "Texture/TextureManager.h"
#include "ObjectBase/GameObjectBase/BackGround/BackGround.h"
#include "ObjectBase/GameObjectBase/Player/Player.h"


ObjectManager::ObjectManager()
{
	SINGLETON_INSTANCE(Lib::TextureManager).Load("Resource/test_001.png",&m_TextureIndex1);
	SINGLETON_INSTANCE(Lib::TextureManager).Load("Resource/test_003.png", &m_TextureIndex3);

	m_pGameObject.push_back(new BackGround(m_TextureIndex3));
	m_pGameObject.push_back(new Player(m_TextureIndex1));
}

ObjectManager::~ObjectManager()
{
	for (int i = m_pGameObject.size() - 1; i >= 0; i--)
	{
		delete m_pGameObject[i];
		m_pGameObject[i] = NULL;
	}

	SINGLETON_INSTANCE(Lib::TextureManager).ReleaseTexture(m_TextureIndex3);
	SINGLETON_INSTANCE(Lib::TextureManager).ReleaseTexture(m_TextureIndex1);
}


//----------------------------------------------------------------------------------------------------
// Public Functions
//----------------------------------------------------------------------------------------------------

void ObjectManager::Update()
{
	for (unsigned int i = 0; i < m_pGameObject.size();i++)
	{
		m_pGameObject[i]->Update();
	}
}

void ObjectManager::Draw()
{
	for (unsigned int i = 0; i < m_pGameObject.size(); i++)
	{
		m_pGameObject[i]->Draw();
	}
}
