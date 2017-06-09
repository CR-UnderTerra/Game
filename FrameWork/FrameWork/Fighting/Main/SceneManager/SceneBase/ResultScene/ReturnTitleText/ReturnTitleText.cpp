/**
 * @file   ReturnTitleText.cpp
 * @brief  ReturnTitleTextクラスの実装
 * @author kotani
 */
#include "ReturnTitleText.h"
#include "Texture/TextureManager.h"
#include "Window/Window.h"
#include "Dx11/DX11Manager.h"
#include "DxInput/KeyBoard/KeyDevice.h"
#include "../ResultScene.h"

const D3DXVECTOR2 ReturnTitleText::m_Rect = D3DXVECTOR2(768, 192);
const float ReturnTitleText::m_DisplayTime = 1.5f;


ReturnTitleText::ReturnTitleText(int _textureIndex) :
m_TextureIndex(_textureIndex),
m_IsSelect(false)
{
	RECT ClientRect;
	GetClientRect(SINGLETON_INSTANCE(Lib::Window).GetWindowHandle(), &ClientRect);
	m_Pos = D3DXVECTOR2(static_cast<float>(ClientRect.right / 2), static_cast<float>(ClientRect.bottom / 2));
	m_Pos.y = static_cast<float>(ClientRect.bottom) - 160.f;
	m_pUvController = new Lib::AnimUvController();
	m_pUvController->LoadAnimation("Resource/Text.anim", "l_return");

	m_pVertex = new Lib::Vertex2D(
		SINGLETON_INSTANCE(Lib::DX11Manager).GetDevice(),
		SINGLETON_INSTANCE(Lib::DX11Manager).GetDeviceContext(),
		SINGLETON_INSTANCE(Lib::Window).GetWindowHandle());
	m_pVertex->Init(&m_Rect, m_pUvController->GetUV());
	m_pVertex->SetTexture(
		SINGLETON_INSTANCE(Lib::TextureManager).GetTexture(m_TextureIndex));
	m_AddAlphaValue = 1.f / (m_DisplayTime * 60);
}


ReturnTitleText::~ReturnTitleText()
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

bool ReturnTitleText::Update()
{
	if (m_IsAddAlpha)
	{
		m_Alpha += m_AddAlphaValue;
	}
	else
	{
		if (m_IsSelect)
		{
			m_Alpha -= m_AddAlphaValue;
		}
		else
		{
			m_Alpha = 1.f;
		}

	}

	if (m_Alpha >= 1.f)
	{
		m_Alpha = 1.f;
		m_IsButtonEnable = true;
		m_IsAddAlpha = false;
	}
	else if (m_Alpha <= 0.3f)
	{
		m_Alpha = 0.3f;
		m_IsAddAlpha = true;
	}

	if (ResultScene::KeyCheck())
	{
		m_Alpha = 1.f;
	}
	return m_IsButtonEnable;
}

void ReturnTitleText::Draw()
{
	m_pVertex->Draw(&m_Pos, m_pUvController->GetUV(), m_Alpha);
}
