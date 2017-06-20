/**
 * @file   ContinueText.cpp
 * @brief  ContinueTextクラスの実装
 * @author kotani
 */
#include "ContinueText.h"
#include "Texture/TextureManager.h"
#include "Window/Window.h"
#include "Dx11/DX11Manager.h"
#include "DxInput/KeyBoard/KeyDevice.h"
#include "../ResultScene.h"

const D3DXVECTOR2 ContinueText::m_Rect = D3DXVECTOR2(768 * 0.7, 192*0.7);
const float ContinueText::m_DisplayTime = 2.f;


ContinueText::ContinueText(int _textureIndex) :
m_TextureIndex(_textureIndex),
m_IsSelect(false)
{
	RECT ClientRect = SINGLETON_INSTANCE(Lib::Window).GetWindowSize();
	m_Pos = D3DXVECTOR2(static_cast<float>(ClientRect.right / 2), static_cast<float>(ClientRect.bottom / 2));
	m_Pos.y = static_cast<float>(ClientRect.bottom) - 280.f;
	m_pUvController = new Lib::AnimUvController();
	m_pUvController->LoadAnimation("Resource/Text.anim", "l_continue");

	m_pVertex = new Lib::Vertex2D(
		SINGLETON_INSTANCE(Lib::DX11Manager).GetDevice(),
		SINGLETON_INSTANCE(Lib::DX11Manager).GetDeviceContext(),
		SINGLETON_INSTANCE(Lib::Window).GetWindowSize());
	m_pVertex->Init(&m_Rect, m_pUvController->GetUV());
	m_pVertex->SetTexture(
		SINGLETON_INSTANCE(Lib::TextureManager).GetTexture(m_TextureIndex));
	m_AddAlphaValue = 1.f / (m_DisplayTime * 60);
}


ContinueText::~ContinueText()
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

bool ContinueText::Update()
{
	m_Alpha += m_AddAlphaValue;
	if (m_IsButtonEnable)
	{
		if (m_IsSelect)
		{
			m_Alpha = 1.f;
		}
		else
		{
			m_Alpha = 0.5f;
		}
	}

	if (m_Alpha >= 1.f)
	{
		m_Alpha = 1.f;
		m_IsButtonEnable = true;
	}

	if (ResultScene::KeyCheck())
	{
		m_Alpha = 1.f;
	}
	return m_IsButtonEnable;
}

void ContinueText::Draw()
{
	m_pVertex->Draw(&m_Pos, m_pUvController->GetUV(), m_Alpha);
}
