/**
 * @file   GameScene.cpp
 * @brief  GameSceneクラスの実装
 * @author kotani
 */
#include "GameScene.h"
#include "Window/Window.h"
#include "Texture/TextureManager.h"
#include "Sound/DSoundManager.h"
#include "DxInput/KeyBoard/KeyDevice.h"
#include "Dx11/DX11Manager.h"
#include "ObjectManager/ObjectManager.h"
#include "DxInput/DXInputDevice.h"
#include "Texture/TextureManager.h"
#include "CollisionManager/CollisionManager.h"
#include "../GameDataManager/GameDataManager.h"
#include "XInput/XInput.h"


GameScene::GameScene() :
SceneBase(SCENE_GAME)
{
	SINGLETON_CREATE(CollisionManager);
	m_pObjectManager = new ObjectManager();
	SINGLETON_INSTANCE(GameDataManager).Init();
}

GameScene::~GameScene()
{
	delete m_pObjectManager;
	m_pObjectManager = NULL;

	SINGLETON_DELETE(CollisionManager);
	SINGLETON_INSTANCE(Lib::TextureManager).Release();
}


//----------------------------------------------------------------------------------------------------
// Public Functions
//----------------------------------------------------------------------------------------------------

SceneBase::SceneID GameScene::Update()
{
	SINGLETON_INSTANCE(GameDataManager).Update();
	m_pObjectManager->Update();
	SINGLETON_INSTANCE(CollisionManager).Update();
	SINGLETON_INSTANCE(Lib::KeyDevice).Update();
	SINGLETON_INSTANCE(Lib::XInput).Update(Lib::GAMEPAD1);
	if (SINGLETON_INSTANCE(GameDataManager).GetIsGameOver())
	{
		m_SceneID = SCENE_RESULT;
	}
	return m_SceneID;
}

void GameScene::Draw()
{
	SINGLETON_INSTANCE(Lib::DX11Manager).SetDepthStencilTest(false);
	SINGLETON_INSTANCE(Lib::DX11Manager).BeginScene();
	m_pObjectManager->Draw();
	SINGLETON_INSTANCE(Lib::DX11Manager).EndScene();
}
