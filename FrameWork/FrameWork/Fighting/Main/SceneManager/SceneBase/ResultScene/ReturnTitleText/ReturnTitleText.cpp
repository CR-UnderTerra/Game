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
#include "Helper/Helper.h"

const D3DXVECTOR2 ReturnTitleText::m_Rect = D3DXVECTOR2(768 * 0.7f, 192 * 0.7f);
const float ReturnTitleText::m_DisplayTime = 2.f;


ReturnTitleText::ReturnTitleText(int _textureIndex) :
m_TextureIndex(_textureIndex),
m_IsSelect(false)
{
	RECT ClientRect = SINGLETON_INSTANCE(Lib::Window).GetWindowSize();
	m_Pos = D3DXVECTOR2(static_cast<float>(ClientRect.right / 2), static_cast<float>(ClientRect.bottom / 2));
	m_Pos.y = static_cast<float>(ClientRect.bottom) - 160.f;
	m_pUvController = new Lib::AnimUvController();
	m_pUvController->LoadAnimation("Resource/Text.anim", "l_return");

	m_pVertex = new Lib::Vertex2D(
		SINGLETON_INSTANCE(Lib::DX11Manager).GetDevice(),
		SINGLETON_INSTANCE(Lib::DX11Manager).GetDeviceContext(),
		SINGLETON_INSTANCE(Lib::Window).GetWindowSize());
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
		Lib::SafeDelete(m_pVertex);
	}

	Lib::SafeDelete(m_pUvController);
}


//----------------------------------------------------------------------------------------------------
// Public Functions
//----------------------------------------------------------------------------------------------------

bool ReturnTitleText::Update()
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

void ReturnTitleText::Draw()
{
	m_pVertex->Draw(&m_Pos, m_pUvController->GetUV(), m_Alpha);
}
