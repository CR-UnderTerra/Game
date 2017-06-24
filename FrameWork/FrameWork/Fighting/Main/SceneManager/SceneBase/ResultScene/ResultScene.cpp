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
#include "Sound/DSoundManager.h"
#include "Helper/Helper.h"
#include <stdlib.h>
#include <time.h>


ResultScene::ResultScene() :
SceneBase(SCENE_RESULT)
{
	srand(unsigned int(time(NULL)));
	if (SINGLETON_INSTANCE(GameDataManager).GetResultState())
	{
		SINGLETON_INSTANCE(Lib::DSoundManager).LoadSound("Resource/Sound/bgm/gameoverBGM.wav", &m_BgmSoundIndex);
		switch (rand() % 3)
		{
		case 0:
			SINGLETON_INSTANCE(Lib::TextureManager).Load("Resource/bg_g_over_01.png", &m_BackGroundTextureIndex);
			break;
		case 1:
			SINGLETON_INSTANCE(Lib::TextureManager).Load("Resource/bg_g_over_02.png", &m_BackGroundTextureIndex);
			break;
		case 2:
			SINGLETON_INSTANCE(Lib::TextureManager).Load("Resource/bg_g_over_03.png", &m_BackGroundTextureIndex);
			break;
		}
	}
	else
	{
		SINGLETON_INSTANCE(Lib::DSoundManager).LoadSound("Resource/Sound/bgm/gameclearBGM.wav", &m_BgmSoundIndex);
		SINGLETON_INSTANCE(Lib::TextureManager).Load("Resource/TitleBackGround.png", &m_BackGroundTextureIndex);
	}
	SINGLETON_INSTANCE(Lib::TextureManager).Load("Resource/Text.png", &m_TextTextureIndex);
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
	Lib::SafeDelete<Result::ScoreWindow>(m_pScoreWindow);

	Lib::SafeDelete<TimeWindow>(m_pTimeWindow);

	Lib::SafeDelete<JudgeCountWindow>(m_pJudgeCountWindow);

	Lib::SafeDelete<ContinueText>(m_pContinueText);

	Lib::SafeDelete<ReturnTitleText>(m_pReturnTitleText);

	Lib::SafeDelete<ClearText>(m_pClearText);

	Lib::SafeDelete<Result::BackGround>(m_pBackGround);

	SINGLETON_INSTANCE(Lib::TextureManager).ReleaseTexture(m_TextureIndex);
	SINGLETON_INSTANCE(Lib::TextureManager).ReleaseTexture(m_BackGroundTextureIndex);
	SINGLETON_INSTANCE(Lib::TextureManager).ReleaseTexture(m_TextTextureIndex);
	SINGLETON_INSTANCE(Lib::TextureManager).Release();
	SINGLETON_INSTANCE(Lib::DSoundManager).ReleaseSound(m_BgmSoundIndex);
	SINGLETON_INSTANCE(Lib::DSoundManager).ClearBuffer();
}


//----------------------------------------------------------------------------------------------------
// Public Functions
//----------------------------------------------------------------------------------------------------

SceneBase::SceneID ResultScene::Update()
{
	KeyUpdate();
	if (SINGLETON_INSTANCE(GameDataManager).GetResultState() == GameDataManager::CLEAR)
	{
		if (!m_pBackGround->Update()) return m_SceneID;
		SINGLETON_INSTANCE(Lib::DSoundManager).SoundOperation(m_BgmSoundIndex, Lib::DSoundManager::SOUND_LOOP);
		if (!m_pClearText->Update()) return m_SceneID;
		if (!m_pTimeWindow->Update()) return m_SceneID;
		if (!m_pJudgeCountWindow->Update()) return m_SceneID;
		if (!m_pScoreWindow->Update()) return m_SceneID;
		m_pContinueText->Update();
		m_pReturnTitleText->Update();
	}
	else
	{
		if (!m_pBackGround->Update()) return m_SceneID;
		SINGLETON_INSTANCE(Lib::DSoundManager).SoundOperation(m_BgmSoundIndex, Lib::DSoundManager::SOUND_LOOP);
		if (!m_pClearText->Update()) return m_SceneID;
		m_pContinueText->Update();
		m_pReturnTitleText->Update();
	}
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
	if (SINGLETON_INSTANCE(GameDataManager).GetResultState() == GameDataManager::CLEAR)
	{
		m_pBackGround->Draw();
		m_pClearText->Draw();
		m_pTimeWindow->Draw();
		m_pJudgeCountWindow->Draw();
		m_pScoreWindow->Draw();
		m_pContinueText->Draw();
		m_pReturnTitleText->Draw();
	}
	else
	{
		m_pBackGround->Draw();
		m_pClearText->Draw();
		m_pContinueText->Draw();
		m_pReturnTitleText->Draw();
	}
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
