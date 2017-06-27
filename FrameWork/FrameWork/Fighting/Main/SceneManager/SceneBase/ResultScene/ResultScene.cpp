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

namespace
{
	D3DXVECTOR2 g_uv[4] = 
	{
		D3DXVECTOR2(0,0),		
		D3DXVECTOR2(1,0),
		D3DXVECTOR2(0,1),
		D3DXVECTOR2(1,1)
	};
}

ResultScene::ResultScene() :
SceneBase(SCENE_RESULT),
m_ReturnTime(1800),
m_FrameCount(0),
m_BlackOutAlpha(0)
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
		SINGLETON_INSTANCE(Lib::TextureManager).Load("Resource/Clear.png", &m_BackGroundTextureIndex);
	}
	SINGLETON_INSTANCE(Lib::TextureManager).Load("Resource/Text.png", &m_TextTextureIndex);
	SINGLETON_INSTANCE(Lib::TextureManager).Load("Resource/test_001.png", &m_TextureIndex);
	SINGLETON_INSTANCE(Lib::TextureManager).Load("Resource/BlackOut.jpg",&m_BlackOutTextureIndex);

	m_pBlackOutVertex = new Lib::Vertex2D(
		SINGLETON_INSTANCE(Lib::DX11Manager).GetDevice(),
		SINGLETON_INSTANCE(Lib::DX11Manager).GetDeviceContext(),
		SINGLETON_INSTANCE(Lib::Window).GetWindowSize());
	m_pBlackOutVertex->Init(&D3DXVECTOR2(1920, 1080), g_uv);
	m_pBlackOutVertex->SetTexture(
		SINGLETON_INSTANCE(Lib::TextureManager).GetTexture(m_BlackOutTextureIndex));

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
	Lib::SafeDelete(m_pScoreWindow);
	Lib::SafeDelete(m_pTimeWindow);
	Lib::SafeDelete(m_pJudgeCountWindow);
	Lib::SafeDelete(m_pContinueText);
	Lib::SafeDelete(m_pReturnTitleText);
	Lib::SafeDelete(m_pClearText);
	Lib::SafeDelete(m_pBackGround);
	Lib::SafeDelete(m_pBlackOutVertex);
	SINGLETON_INSTANCE(Lib::TextureManager).ReleaseTexture(m_BlackOutTextureIndex);
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
	m_FrameCount++;
	if (m_FrameCount >= m_ReturnTime)
	{
		m_BlackOutAlpha += 1.f / (2 * 60);;
		if (m_BlackOutAlpha >= 1.f)
		{
			return SCENE_TITLE;
		}
	}

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
	m_pBlackOutVertex->Draw(&D3DXVECTOR2(960.f, 540.f),g_uv,m_BlackOutAlpha);
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
