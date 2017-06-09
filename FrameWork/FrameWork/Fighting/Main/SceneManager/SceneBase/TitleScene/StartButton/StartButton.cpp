/**
 * @file   StartButton.cpp
 * @brief  StartButtonクラスの実装
 * @author kotani
 */
#include "StartButton.h"
#include "Texture/TextureManager.h"
#include "Window/Window.h"
#include "Dx11/DX11Manager.h"
#include "DxInput/KeyBoard/KeyDevice.h"
#include "../TitleScene.h"

const D3DXVECTOR2 StartButton::m_Rect = D3DXVECTOR2(768, 192);
const float StartButton::m_DisplayTime = 2.f;


StartButton::StartButton(int _textureIndex) :
m_TextureIndex(_textureIndex),
m_Alpha(0),
m_IsAddAlpha(true),
m_IsButtonEnable(false)
{
	RECT ClientRect = SINGLETON_INSTANCE(Lib::Window).GetWindowSize();
	m_Pos = D3DXVECTOR2(static_cast<float>(ClientRect.right / 2), static_cast<float>(ClientRect.bottom / 2));
	m_Pos.y = 638.f;
	m_pUvController = new Lib::AnimUvController();
	m_pUvController->LoadAnimation("Resource/Text.anim", "l_button");

	m_pVertex = new Lib::Vertex2D(
		SINGLETON_INSTANCE(Lib::DX11Manager).GetDevice(),
		SINGLETON_INSTANCE(Lib::DX11Manager).GetDeviceContext(),
		SINGLETON_INSTANCE(Lib::Window).GetWindowSize());
	m_pVertex->Init(&m_Rect, m_pUvController->GetUV());
	m_pVertex->SetTexture(
		SINGLETON_INSTANCE(Lib::TextureManager).GetTexture(m_TextureIndex));

	m_AddAlphaValue = 1.f / (m_DisplayTime * 60);
}


StartButton::~StartButton()
{
	if (m_pVertex != NULL)
	{
		m_pVertex->Release();
		delete m_pVertex;
		m_pVertex = NULL;
	}

	delete m_pUvController;
	m_pUvController = NULL;
}


//----------------------------------------------------------------------------------------------------
// Public Functions
//----------------------------------------------------------------------------------------------------

bool StartButton::Update()
{
	if (m_IsAddAlpha)
	{
		m_Alpha += m_AddAlphaValue;
	}
	else
	{
		m_Alpha -= m_AddAlphaValue;
	}

	if (m_Alpha >= 1.f)
	{
		m_Alpha = 1.f;
		m_IsButtonEnable = true;
		m_IsAddAlpha = false;
	}
	else if (m_Alpha <= 0.2f)
	{
		m_Alpha = 0.2f;
		m_IsAddAlpha = true;
	}

	if (TitleScene::KeyCheck())
	{
		m_Alpha = 1.f;
	}
	return m_IsButtonEnable;
}

void StartButton::Draw()
{
	m_pVertex->Draw(&m_Pos, m_pUvController->GetUV(),m_Alpha);
}
