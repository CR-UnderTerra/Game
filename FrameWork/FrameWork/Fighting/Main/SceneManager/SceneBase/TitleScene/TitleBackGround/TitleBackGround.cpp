﻿/**
 * @file   TitleBackGround.cpp
 * @brief  TitleBackGroundクラスの実装
 * @author kotani
 */
#include "TitleBackGround.h"
#include "Texture/TextureManager.h"
#include "Window/Window.h"
#include "Dx11/DX11Manager.h"

const D3DXVECTOR2 TitleBackGround::m_Rect = D3DXVECTOR2(1920, 1080);
const float TitleBackGround::m_DisplayTime = 2.f;

TitleBackGround::TitleBackGround(int _textureIndex) :
m_TextureIndex(_textureIndex),
m_Alpha(0.f)
{
	RECT ClientRect;
	GetClientRect(SINGLETON_INSTANCE(Lib::Window).GetWindowHandle(), &ClientRect);
	m_Pos = D3DXVECTOR2(static_cast<float>(ClientRect.right / 2), static_cast<float>(ClientRect.bottom / 2));
	m_pUvController = new Lib::AnimUvController();
	m_pUvController->LoadAnimation("Resource/TitleBackGround.anim", "bg_tit");
	
	m_pVertex = new Lib::Vertex2D(
		SINGLETON_INSTANCE(Lib::DX11Manager).GetDevice(),
		SINGLETON_INSTANCE(Lib::DX11Manager).GetDeviceContext(),
		SINGLETON_INSTANCE(Lib::Window).GetWindowHandle());
	m_pVertex->Init(&m_Rect, m_pUvController->GetUV());
	m_pVertex->SetTexture(
		SINGLETON_INSTANCE(Lib::TextureManager).GetTexture(m_TextureIndex));

	m_AddAlphaValue = 1.f / (m_DisplayTime * 60);
}


TitleBackGround::~TitleBackGround()
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

bool TitleBackGround::Update()
{
	m_Alpha += m_AddAlphaValue;
	if (m_Alpha > 1.f)
	{
		m_Alpha = 1.f;
		return true;
	}
	return false;
}

void TitleBackGround::Draw()
{
	m_pVertex->Draw(&m_Pos,m_pUvController->GetUV(),m_Alpha);
}
