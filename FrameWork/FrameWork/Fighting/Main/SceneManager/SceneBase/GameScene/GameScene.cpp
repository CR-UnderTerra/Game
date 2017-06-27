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
#include "Sound\DSoundManager.h"
#include "Helper/Helper.h"
#include "Event/EventManager.h"


namespace
{
	int FrameCount = 300;
}

GameScene::GameScene() :
SceneBase(SCENE_GAME)
{
	SINGLETON_CREATE(Lib::EventManager);
	RECT windowRect = SINGLETON_INSTANCE(Lib::Window).GetWindowSize();
	m_Pos.x = static_cast<float>(windowRect.right) / 2;
	m_Pos.y = static_cast<float>(windowRect.bottom) / 2;
	m_Rect = D3DXVECTOR2(45 * 2, 96 * 2);
	FrameCount = 300;
	SINGLETON_INSTANCE(Lib::TextureManager).Load("Resource/test_001.png",&m_TextureIndex);
	SINGLETON_INSTANCE(Lib::TextureManager).Load("Resource/test_006.png", &m_ButtonTextureIndex);
	
	m_pUvController = new Lib::AnimUvController();
	m_pUvController->LoadAnimation("Resource/test_001.anim", "Number");
	m_pVertex = new Lib::Vertex2D(
		SINGLETON_INSTANCE(Lib::DX11Manager).GetDevice(),
		SINGLETON_INSTANCE(Lib::DX11Manager).GetDeviceContext(),
		SINGLETON_INSTANCE(Lib::Window).GetWindowSize());
	m_pVertex->Init(&m_Rect, m_pUvController->GetUV());
	m_pVertex->SetTexture(
		SINGLETON_INSTANCE(Lib::TextureManager).GetTexture(m_TextureIndex));

	m_pXButtonUvController = new Lib::AnimUvController();
	m_pXButtonUvController->LoadAnimation("Resource/test_006.anim", "b_x");
	m_pYButtonUvController = new Lib::AnimUvController();
	m_pYButtonUvController->LoadAnimation("Resource/test_006.anim", "b_y");
	m_pBButtonUvController = new Lib::AnimUvController();
	m_pBButtonUvController->LoadAnimation("Resource/test_006.anim", "b_b");

	m_pButtonVertex = new Lib::Vertex2D(
		SINGLETON_INSTANCE(Lib::DX11Manager).GetDevice(),
		SINGLETON_INSTANCE(Lib::DX11Manager).GetDeviceContext(),
		SINGLETON_INSTANCE(Lib::Window).GetWindowSize());
	m_pButtonVertex->Init(&D3DXVECTOR2(100,100), m_pUvController->GetUV());
	m_pButtonVertex->SetTexture(
		SINGLETON_INSTANCE(Lib::TextureManager).GetTexture(m_ButtonTextureIndex));

	SINGLETON_CREATE(CollisionManager);
	m_pObjectManager = new ObjectManager();
	SINGLETON_INSTANCE(GameDataManager).Init();

	SINGLETON_INSTANCE(Lib::DSoundManager).LoadSound("Resource/Sound/bgm/gameBGM.wav", &m_BgmSoundIndex);
	SINGLETON_INSTANCE(Lib::DSoundManager).LoadSound("Resource/Sound/countdown/CountdownVoice.wav", &m_CountdownSoundIndex);
}

GameScene::~GameScene()
{
	SINGLETON_INSTANCE(Lib::DSoundManager).ReleaseSound(m_CountdownSoundIndex);
	SINGLETON_INSTANCE(Lib::DSoundManager).ReleaseSound(m_BgmSoundIndex);

	Lib::SafeDelete<ObjectManager>(m_pObjectManager);

	m_pButtonVertex->Release();
	Lib::SafeDelete(m_pButtonVertex);

	Lib::SafeDelete(m_pBButtonUvController);
	Lib::SafeDelete(m_pYButtonUvController);
	Lib::SafeDelete(m_pXButtonUvController);

	m_pVertex->Release();
	Lib::SafeDelete<Lib::Vertex2D>(m_pVertex);
	SINGLETON_INSTANCE(Lib::TextureManager).ReleaseTexture(m_ButtonTextureIndex);
	SINGLETON_INSTANCE(Lib::TextureManager).ReleaseTexture(m_TextureIndex);

	Lib::SafeDelete<Lib::AnimUvController>(m_pUvController);

	SINGLETON_DELETE(CollisionManager);
	SINGLETON_INSTANCE(Lib::TextureManager).Release();
	SINGLETON_INSTANCE(Lib::DSoundManager).ClearBuffer();
	SINGLETON_DELETE(Lib::EventManager);
}


//----------------------------------------------------------------------------------------------------
// Public Functions
//----------------------------------------------------------------------------------------------------

SceneBase::SceneID GameScene::Update()
{
	FrameCount--;
	if (FrameCount > 60 && FrameCount < 240)
	{
		SINGLETON_INSTANCE(Lib::DSoundManager).SoundOperation(m_CountdownSoundIndex, Lib::DSoundManager::SOUND_PLAY);
	}

	if (FrameCount > 0)
	{
		m_pUvController->SetAnimCount(FrameCount / 60);
	}
	else
	{
		SINGLETON_INSTANCE(Lib::DSoundManager).SoundOperation(m_BgmSoundIndex, Lib::DSoundManager::SOUND_LOOP);
		SINGLETON_INSTANCE(GameDataManager).Update();
		m_pObjectManager->Update();
		SINGLETON_INSTANCE(CollisionManager).Update();
		SINGLETON_INSTANCE(Lib::KeyDevice).Update();
		SINGLETON_INSTANCE(Lib::XInput).Update(Lib::GAMEPAD1);
		if (SINGLETON_INSTANCE(GameDataManager).GetIsGameOver())
		{
			m_SceneID = SCENE_RESULT;
		}
	}

	return m_SceneID;
}

void GameScene::Draw()
{
	SINGLETON_INSTANCE(Lib::DX11Manager).SetDepthStencilTest(false);
	SINGLETON_INSTANCE(Lib::DX11Manager).BeginScene();
	m_pObjectManager->Draw();
	if (FrameCount > 60 && FrameCount < 240)
	{
		m_pVertex->Draw(&m_Pos,m_pUvController->GetUV());
		D3DXVECTOR2 pos = SINGLETON_INSTANCE(GameDataManager).GetPos(GameDataManager::LEFT_ENEMY_TARGET);
		pos.y -= 180.f;
		m_pButtonVertex->Draw(&pos, m_pXButtonUvController->GetUV());
		pos = SINGLETON_INSTANCE(GameDataManager).GetPos(GameDataManager::FRONT_ENEMY_TARGET);
		pos.y -= 180.f;
		m_pButtonVertex->Draw(&pos, m_pYButtonUvController->GetUV());
		pos = SINGLETON_INSTANCE(GameDataManager).GetPos(GameDataManager::RIGHT_ENEMY_TARGET);
		pos.y -= 180.f;
		m_pButtonVertex->Draw(&pos, m_pBButtonUvController->GetUV());
	}
	SINGLETON_INSTANCE(Lib::DX11Manager).EndScene();
}
