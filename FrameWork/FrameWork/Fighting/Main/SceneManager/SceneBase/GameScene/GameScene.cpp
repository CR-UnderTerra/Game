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
#include "CollisionManager/CollisionManager.h"
#include "GameDataManager/GameDataManager.h"

GameScene::GameScene() :
SceneBase(SCENE_GAME)
{
	{
		const HWND hWnd = SINGLETON_INSTANCE(Lib::Window).GetWindowHandle();

		// Lib::DSoundManager Init
		SINGLETON_CREATE(Lib::DSoundManager);
		SINGLETON_INSTANCE(Lib::DSoundManager).Init(hWnd);
		// Lib::DSoundManager Init end

		SINGLETON_CREATE(Lib::DXInputDevice);

		// InputDevice関係
		SINGLETON_CREATE(Lib::DXInputDevice);
		SINGLETON_INSTANCE(Lib::DXInputDevice).Init(hWnd);

		SINGLETON_CREATE(Lib::MouseDevice);
		SINGLETON_INSTANCE(Lib::MouseDevice).Init(
			SINGLETON_INSTANCE(Lib::DXInputDevice).GetInputDevice(), hWnd);

		SINGLETON_CREATE(Lib::KeyDevice);
		SINGLETON_INSTANCE(Lib::KeyDevice).Init(
			SINGLETON_INSTANCE(Lib::DXInputDevice).GetInputDevice(), hWnd);
	}

	{
		ID3D11Device* const pDevice = SINGLETON_INSTANCE(Lib::DX11Manager).GetDevice();

		// Lib::TextureManager Init
		SINGLETON_CREATE(Lib::TextureManager);
		SINGLETON_INSTANCE(Lib::TextureManager).Init(pDevice);
		// Lib::TextureManager Init end
	}
	SINGLETON_CREATE(GameDataManager);
	SINGLETON_CREATE(CollisionManager);
	m_pObjectManager = new ObjectManager();
}

GameScene::~GameScene()
{
	delete m_pObjectManager;
	SINGLETON_DELETE(CollisionManager);
	SINGLETON_DELETE(GameDataManager);

	// Lib::TextureManager Delete
	SINGLETON_INSTANCE(Lib::TextureManager).Release();
	SINGLETON_DELETE(Lib::TextureManager);
	// Lib::TextureManager Delete end

	// Lib::InputDevice関係
	SINGLETON_INSTANCE(Lib::KeyDevice).Release();
	SINGLETON_DELETE(Lib::KeyDevice);

	SINGLETON_INSTANCE(Lib::MouseDevice).Release();
	SINGLETON_DELETE(Lib::MouseDevice);

	SINGLETON_INSTANCE(Lib::DXInputDevice).Release();
	SINGLETON_DELETE(Lib::DXInputDevice);

	// Lib::DSoundManager Delete
	SINGLETON_INSTANCE(Lib::DSoundManager).Release();
	SINGLETON_DELETE(Lib::DSoundManager);
	// Lib::DSoundManager Delete end

}


//----------------------------------------------------------------------------------------------------
// Public Functions
//----------------------------------------------------------------------------------------------------

SceneBase::SceneID GameScene::Update()
{
	m_pObjectManager->Update();
	SINGLETON_INSTANCE(CollisionManager).Update();
	SINGLETON_INSTANCE(Lib::KeyDevice).Update();
	SINGLETON_INSTANCE(Lib::KeyDevice).KeyCheck(DIK_R);
	if (SINGLETON_INSTANCE(Lib::KeyDevice).GetKeyState()[DIK_R] == Lib::KEY_PUSH)
	{
		m_SceneID = SCENE_TITLE;
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
