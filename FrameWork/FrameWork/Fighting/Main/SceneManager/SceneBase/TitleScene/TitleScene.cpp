﻿/**
 * @file TitleScene.cpp
 * @brief TitleSceneクラス実装
 * @author kotani
 */
#include "Dx11/DX11Manager.h"
#include "TitleScene.h"
#include "Window/Window.h"
#include "Texture/TextureManager.h"
#include "Sound/DSoundManager.h"
#include "DxInput/KeyBoard/KeyDevice.h"
#include "DxInput/DXInputDevice.h"
#include "../../../XInput/XInput.h"
#include "TitleBackGround/TitleBackGround.h"
#include "StartButton/StartButton.h"
#include "TitleText/TitleText.h"


TitleScene::TitleScene() :
SceneBase(SCENE_TITLE)
{
	InitLibrary();
	SINGLETON_INSTANCE(Lib::TextureManager).Load("Resource/BlackOut.png",&m_BlackOutTextureIndex);
	SINGLETON_INSTANCE(Lib::TextureManager).Load("Resource/TitleText.png", &m_TextTextureIndex);
	SINGLETON_INSTANCE(Lib::TextureManager).Load("Resource/TitleBackGround.png", &m_BackGroundTextureIndex);

	m_pTitleBackGround = new TitleBackGround(m_BackGroundTextureIndex);
	m_pTitleText = new TitleText(m_TextTextureIndex);
	m_pStartButton = new StartButton(m_TextTextureIndex);
}

TitleScene::~TitleScene()
{
	delete m_pStartButton;
	delete m_pTitleText;
	delete m_pTitleBackGround;
	SINGLETON_INSTANCE(Lib::TextureManager).ReleaseTexture(m_BackGroundTextureIndex);
	SINGLETON_INSTANCE(Lib::TextureManager).ReleaseTexture(m_TextTextureIndex);
	SINGLETON_INSTANCE(Lib::TextureManager).ReleaseTexture(m_BlackOutTextureIndex);
	ReleaseLibrary();
}

//----------------------------------------------------------------------------------------------------
// Public Functions
//----------------------------------------------------------------------------------------------------

SceneBase::SceneID TitleScene::Update()
{
	KeyUpdate();

	if (m_pTitleBackGround->Update())
	{
		if (m_pTitleText->Update())
		{
			if (m_pStartButton->Update())
			{
				if (KeyCheck())
				{
					m_SceneID = SCENE_GAME;
				}
			}
		}
	}
	return m_SceneID;
}

void TitleScene::Draw()
{
	SINGLETON_INSTANCE(Lib::DX11Manager).SetDepthStencilTest(false);
	SINGLETON_INSTANCE(Lib::DX11Manager).BeginScene();
	m_pTitleBackGround->Draw();
	m_pStartButton->Draw();
	m_pTitleText->Draw();
	SINGLETON_INSTANCE(Lib::DX11Manager).EndScene();

}


//----------------------------------------------------------------------------------------------------
// Private Functions
//----------------------------------------------------------------------------------------------------

void TitleScene::InitLibrary()
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

		SINGLETON_CREATE(Lib::XInput);
	}

	{
		ID3D11Device* const pDevice = SINGLETON_INSTANCE(Lib::DX11Manager).GetDevice();

		// Lib::TextureManager Init
		SINGLETON_CREATE(Lib::TextureManager);
		SINGLETON_INSTANCE(Lib::TextureManager).Init(pDevice);
		// Lib::TextureManager Init end
	}
}

void TitleScene::ReleaseLibrary()
{
	// Lib::TextureManager Delete
	SINGLETON_INSTANCE(Lib::TextureManager).Release();
	SINGLETON_DELETE(Lib::TextureManager);
	// Lib::TextureManager Delete end

	SINGLETON_DELETE(Lib::XInput);

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

void TitleScene::KeyUpdate()
{
	SINGLETON_INSTANCE(Lib::KeyDevice).Update();
	SINGLETON_INSTANCE(Lib::KeyDevice).KeyCheck(DIK_Z);
	SINGLETON_INSTANCE(Lib::KeyDevice).KeyCheck(DIK_X);
	SINGLETON_INSTANCE(Lib::KeyDevice).KeyCheck(DIK_C);
	SINGLETON_INSTANCE(Lib::KeyDevice).KeyCheck(DIK_SPACE);
	SINGLETON_INSTANCE(Lib::KeyDevice).KeyCheck(DIK_RETURN);
}

bool TitleScene::KeyCheck()
{
	if (SINGLETON_INSTANCE(Lib::KeyDevice).GetKeyState()[DIK_Z] == Lib::KEY_RELEASE ||
		SINGLETON_INSTANCE(Lib::KeyDevice).GetKeyState()[DIK_X] == Lib::KEY_RELEASE ||
		SINGLETON_INSTANCE(Lib::KeyDevice).GetKeyState()[DIK_C] == Lib::KEY_RELEASE ||
		SINGLETON_INSTANCE(Lib::KeyDevice).GetKeyState()[DIK_SPACE] == Lib::KEY_RELEASE ||
		SINGLETON_INSTANCE(Lib::KeyDevice).GetKeyState()[DIK_RETURN] == Lib::KEY_RELEASE)
	{
		return true;
	}
	else
	{
		return false;
	}
}
