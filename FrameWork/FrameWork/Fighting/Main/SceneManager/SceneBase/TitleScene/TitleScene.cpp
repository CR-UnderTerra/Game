/**
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
#include "XInput/XInput.h"
#include "TitleBackGround/TitleBackGround.h"
#include "StartButton/StartButton.h"
#include "TitleText/TitleText.h"


TitleScene::TitleScene() :
SceneBase(SCENE_TITLE)
{
	SINGLETON_INSTANCE(Lib::TextureManager).Load("Resource/BlackOut.png", &m_BlackOutTextureIndex);
	SINGLETON_INSTANCE(Lib::TextureManager).Load("Resource/Text.png", &m_TextTextureIndex);
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
	SINGLETON_INSTANCE(Lib::TextureManager).Release();
}

//----------------------------------------------------------------------------------------------------
// Public Functions
//----------------------------------------------------------------------------------------------------

SceneBase::SceneID TitleScene::Update()
{
	KeyUpdate();

	// alpha値が1になると次の絵を描画するので
	// alpha値が1になるとtrueになって次の処理をするようにする
	if (!m_pTitleBackGround->Update()) return m_SceneID;
	if (!m_pTitleText->Update()) return m_SceneID;
	if (!m_pStartButton->Update()) return m_SceneID;

	if (KeyCheck())
	{
		m_SceneID = SCENE_GAME;
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

bool TitleScene::KeyCheck()
{
	if (SINGLETON_INSTANCE(Lib::KeyDevice).GetKeyState()[DIK_Z] == Lib::KEY_RELEASE ||
		SINGLETON_INSTANCE(Lib::KeyDevice).GetKeyState()[DIK_X] == Lib::KEY_RELEASE ||
		SINGLETON_INSTANCE(Lib::KeyDevice).GetKeyState()[DIK_C] == Lib::KEY_RELEASE ||
		SINGLETON_INSTANCE(Lib::KeyDevice).GetKeyState()[DIK_SPACE] == Lib::KEY_RELEASE ||
		SINGLETON_INSTANCE(Lib::KeyDevice).GetKeyState()[DIK_RETURN] == Lib::KEY_RELEASE ||
		SINGLETON_INSTANCE(Lib::XInput).GetButtonState(Lib::GAMEPAD_X,Lib::GAMEPAD1) == Lib::PAD_RELEASE ||
		SINGLETON_INSTANCE(Lib::XInput).GetButtonState(Lib::GAMEPAD_Y, Lib::GAMEPAD1) == Lib::PAD_RELEASE ||
		SINGLETON_INSTANCE(Lib::XInput).GetButtonState(Lib::GAMEPAD_B, Lib::GAMEPAD1) == Lib::PAD_RELEASE)
	{
		return true;
	}
	else
	{
		return false;
	}
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
	SINGLETON_INSTANCE(Lib::XInput).Update(Lib::GAMEPAD1);
	SINGLETON_INSTANCE(Lib::XInput).CheckButton(Lib::GAMEPAD1,Lib::GAMEPAD_X,XINPUT_GAMEPAD_X);
	SINGLETON_INSTANCE(Lib::XInput).CheckButton(Lib::GAMEPAD1, Lib::GAMEPAD_Y, XINPUT_GAMEPAD_Y);
	SINGLETON_INSTANCE(Lib::XInput).CheckButton(Lib::GAMEPAD1, Lib::GAMEPAD_B, XINPUT_GAMEPAD_B);

	SINGLETON_INSTANCE(Lib::KeyDevice).KeyCheck(DIK_Z);
	SINGLETON_INSTANCE(Lib::KeyDevice).KeyCheck(DIK_X);
	SINGLETON_INSTANCE(Lib::KeyDevice).KeyCheck(DIK_C);
	SINGLETON_INSTANCE(Lib::KeyDevice).KeyCheck(DIK_SPACE);
	SINGLETON_INSTANCE(Lib::KeyDevice).KeyCheck(DIK_RETURN);
}
