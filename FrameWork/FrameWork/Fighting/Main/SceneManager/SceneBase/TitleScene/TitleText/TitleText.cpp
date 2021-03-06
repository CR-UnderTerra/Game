﻿/**
 * @file   TitleText.cpp
 * @brief  TitleTextクラスの実装
 * @author kotani
 */
#include "TitleText.h"
#include "Texture/TextureManager.h"
#include "Window/Window.h"
#include "Dx11/DX11Manager.h"
#include "DxInput/KeyBoard/KeyDevice.h"
#include "../TitleScene.h"
#include "Helper/Helper.h"

const D3DXVECTOR2 TitleText::m_Rect = D3DXVECTOR2(1920 * 0.7, 450 * 0.7);
const float TitleText::m_DisplayTime = 3.f;


TitleText::TitleText(int _textureIndex) :
m_TextureIndex(_textureIndex),
m_Alpha(0)
{
	RECT ClientRect = SINGLETON_INSTANCE(Lib::Window).GetWindowSize();
	m_Pos = D3DXVECTOR2(static_cast<float>(ClientRect.right / 2), static_cast<float>(ClientRect.bottom / 2));
	m_Pos.y = 435.f;
	m_pUvController = new Lib::AnimUvController();
	m_pUvController->LoadAnimation("Resource/Text.anim", "l_titile");

	m_pVertex = new Lib::Vertex2D(
		SINGLETON_INSTANCE(Lib::DX11Manager).GetDevice(),
		SINGLETON_INSTANCE(Lib::DX11Manager).GetDeviceContext(),
		SINGLETON_INSTANCE(Lib::Window).GetWindowSize());
	m_pVertex->Init(&m_Rect, m_pUvController->GetUV());
	m_pVertex->SetTexture(
		SINGLETON_INSTANCE(Lib::TextureManager).GetTexture(m_TextureIndex));
	m_AddAlphaValue = 1.f / (m_DisplayTime * 60);
}


TitleText::~TitleText()
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

bool TitleText::Update()
{
	m_Alpha += m_AddAlphaValue;
	if (m_Alpha > 1.f)
	{
		m_Alpha = 1.f;
		return true;
	}

	if (TitleScene::KeyCheck())
	{
		m_Alpha = 1.f;
	}
	return false;
}

void TitleText::Draw()
{
	m_pVertex->Draw(&m_Pos, m_pUvController->GetUV(), m_Alpha);
}
