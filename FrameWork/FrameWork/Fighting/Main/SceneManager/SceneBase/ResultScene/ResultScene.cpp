/**
 * @file   ResultScene.cpp
 * @brief  ResultSceneクラスの実装
 * @author kotani
 */
#include "ResultScene.h"
#include "Dx11/DX11Manager.h"
#include "Window/Window.h"
#include "Texture/TextureManager.h"
#include "Sound/DSoundManager.h"
#include "DxInput/KeyBoard/KeyDevice.h"
#include "DxInput/DXInputDevice.h"
#include "XInput/XInput.h"
#include "BackGround/ResultBackGround.h"
#include "ClearText/ClearText.h"
#include "ContinueText/ContinueText.h"
#include "ReturnTitleText/ReturnTitleText.h"
#include "TimeWindow/TimeWindow.h"
#include "JudgeCountWindow/JudgeCountWindow.h"


ResultScene::ResultScene() :
SceneBase(SCENE_RESULT)
{
	SINGLETON_INSTANCE(Lib::TextureManager).Load("Resource/Text.png", &m_TextTextureIndex);
	SINGLETON_INSTANCE(Lib::TextureManager).Load("Resource/TitleBackGround.png", &m_BackGroundTextureIndex);
	SINGLETON_INSTANCE(Lib::TextureManager).Load("Resource/test_001.png", &m_TextureIndex);
	m_pBackGround = new Result::BackGround(m_BackGroundTextureIndex);
	m_pClearText = new ClearText(m_TextTextureIndex);
	m_pReturnTitleText = new ReturnTitleText(m_TextTextureIndex);
	m_pContinueText = new ContinueText(m_TextTextureIndex);
	m_pJudgeCountWindow = new JudgeCountWindow(m_TextureIndex);
	m_pTimeWindow = new TimeWindow();
	m_pScoreWindow = new Result::ScoreWindow();
}

ResultScene::~ResultScene()
{
	delete m_pScoreWindow;
	m_pScoreWindow = NULL;

	delete m_pTimeWindow;
	m_pTimeWindow = NULL;

	delete m_pJudgeCountWindow;
	m_pJudgeCountWindow = NULL;

	delete m_pContinueText;
	m_pContinueText = NULL;

	delete m_pReturnTitleText;
	m_pReturnTitleText = NULL;

	delete m_pClearText;
	m_pClearText = NULL;

	delete m_pBackGround;
	m_pBackGround = NULL;

	SINGLETON_INSTANCE(Lib::TextureManager).ReleaseTexture(m_TextureIndex);
	SINGLETON_INSTANCE(Lib::TextureManager).ReleaseTexture(m_BackGroundTextureIndex);
	SINGLETON_INSTANCE(Lib::TextureManager).ReleaseTexture(m_TextTextureIndex);
	SINGLETON_INSTANCE(Lib::TextureManager).Release();
}


//----------------------------------------------------------------------------------------------------
// Public Functions
//----------------------------------------------------------------------------------------------------

SceneBase::SceneID ResultScene::Update()
{
	KeyUpdate();

	if (!m_pBackGround->Update()) return m_SceneID;
	if (!m_pClearText->Update()) return m_SceneID;
	if (!m_pTimeWindow->Update()) return m_SceneID;
	if (!m_pJudgeCountWindow->Update()) return m_SceneID;
	if (!m_pScoreWindow->Update()) return m_SceneID;
	m_pContinueText->Update();
	m_pReturnTitleText->Update();
	if (SINGLETON_INSTANCE(Lib::KeyDevice).GetKeyState()[DIK_UPARROW] == Lib::KEY_PUSH ||
		SINGLETON_INSTANCE(Lib::KeyDevice).GetKeyState()[DIK_DOWNARROW] == Lib::KEY_PUSH ||
		SINGLETON_INSTANCE(Lib::XInput).GetButtonState(Lib::GAMEPAD_ANALOG_UP, Lib::GAMEPAD1) == Lib::PAD_PUSH ||
		SINGLETON_INSTANCE(Lib::XInput).GetButtonState(Lib::GAMEPAD_ANALOG_DOWN, Lib::GAMEPAD1) == Lib::PAD_PUSH)
	{
		if (m_pContinueText->GetIsSelect())
		{
			m_pContinueText->SetIsSelect(false);
			m_pReturnTitleText->SetIsSelect(true);
		}
		else
		{
			m_pReturnTitleText->SetIsSelect(false);
			m_pContinueText->SetIsSelect(true);
		}
	}

	if (KeyCheck())
	{
		if (m_pContinueText->GetIsSelect())
		{
			return SCENE_GAME;
		}
		else if (m_pReturnTitleText->GetIsSelect())
		{
			return SCENE_TITLE;
		}
	}
	return m_SceneID;
}

void ResultScene::Draw()
{
	SINGLETON_INSTANCE(Lib::DX11Manager).SetDepthStencilTest(false);
	SINGLETON_INSTANCE(Lib::DX11Manager).BeginScene();
	m_pBackGround->Draw();
	m_pClearText->Draw();
	m_pTimeWindow->Draw();
	m_pJudgeCountWindow->Draw();
	m_pScoreWindow->Draw();
	m_pContinueText->Draw();
	m_pReturnTitleText->Draw();
	SINGLETON_INSTANCE(Lib::DX11Manager).EndScene();
}

bool ResultScene::KeyCheck()
{
	if (SINGLETON_INSTANCE(Lib::KeyDevice).GetKeyState()[DIK_Z] == Lib::KEY_RELEASE ||
		SINGLETON_INSTANCE(Lib::KeyDevice).GetKeyState()[DIK_X] == Lib::KEY_RELEASE ||
		SINGLETON_INSTANCE(Lib::KeyDevice).GetKeyState()[DIK_C] == Lib::KEY_RELEASE ||
		SINGLETON_INSTANCE(Lib::KeyDevice).GetKeyState()[DIK_SPACE] == Lib::KEY_RELEASE ||
		SINGLETON_INSTANCE(Lib::KeyDevice).GetKeyState()[DIK_RETURN] == Lib::KEY_RELEASE ||
		SINGLETON_INSTANCE(Lib::XInput).GetButtonState(Lib::GAMEPAD_X, Lib::GAMEPAD1) == Lib::PAD_RELEASE ||
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

void ResultScene::InitLibrary()
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

void ResultScene::ReleaseLibrary()
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

void ResultScene::KeyUpdate()
{
	SINGLETON_INSTANCE(Lib::KeyDevice).Update();
	SINGLETON_INSTANCE(Lib::XInput).Update(Lib::GAMEPAD1);
	SINGLETON_INSTANCE(Lib::XInput).CheckButton(Lib::GAMEPAD1, Lib::GAMEPAD_X, XINPUT_GAMEPAD_X);
	SINGLETON_INSTANCE(Lib::XInput).CheckButton(Lib::GAMEPAD1, Lib::GAMEPAD_Y, XINPUT_GAMEPAD_Y);
	SINGLETON_INSTANCE(Lib::XInput).CheckButton(Lib::GAMEPAD1, Lib::GAMEPAD_B, XINPUT_GAMEPAD_B);
	SINGLETON_INSTANCE(Lib::XInput).CheckAnalogPad(Lib::GAMEPAD1, Lib::GAMEPAD_ANALOG_UP);
	SINGLETON_INSTANCE(Lib::XInput).CheckAnalogPad(Lib::GAMEPAD1, Lib::GAMEPAD_ANALOG_DOWN);

	SINGLETON_INSTANCE(Lib::KeyDevice).KeyCheck(DIK_Z);
	SINGLETON_INSTANCE(Lib::KeyDevice).KeyCheck(DIK_X);
	SINGLETON_INSTANCE(Lib::KeyDevice).KeyCheck(DIK_C);
	SINGLETON_INSTANCE(Lib::KeyDevice).KeyCheck(DIK_UPARROW);
	SINGLETON_INSTANCE(Lib::KeyDevice).KeyCheck(DIK_DOWNARROW);
	SINGLETON_INSTANCE(Lib::KeyDevice).KeyCheck(DIK_SPACE);
	SINGLETON_INSTANCE(Lib::KeyDevice).KeyCheck(DIK_RETURN);
}
