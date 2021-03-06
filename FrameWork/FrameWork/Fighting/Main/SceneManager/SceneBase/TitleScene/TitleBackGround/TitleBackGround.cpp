﻿/**
 * @file   TitleBackGround.cpp
 * @brief  TitleBackGroundクラスの実装
 * @author kotani
 */
#include "TitleBackGround.h"
#include "Texture/TextureManager.h"
#include "Window/Window.h"
#include "Dx11/DX11Manager.h"
#include "DxInput/KeyBoard/KeyDevice.h"
#include "../TitleScene.h"
#include "Helper/Helper.h"

const D3DXVECTOR2 TitleBackGround::m_Rect = D3DXVECTOR2(1920, 1080);
const float TitleBackGround::m_DisplayTime = 1.8f;


TitleBackGround::TitleBackGround() :
m_Alpha(0.f),
m_IsTransitionControl(false)
{
	SINGLETON_INSTANCE(Lib::TextureManager).Load("Resource/TitleBackGround.png", &m_TextureIndex);
	SINGLETON_INSTANCE(Lib::TextureManager).Load("Resource/TitleBackGround2.png", &m_TextureIndex2);
	RECT ClientRect = SINGLETON_INSTANCE(Lib::Window).GetWindowSize();
	m_Pos = D3DXVECTOR2(static_cast<float>(ClientRect.right / 2), static_cast<float>(ClientRect.bottom / 2));
	m_pUvController = new Lib::AnimUvController();
	m_pUvController->LoadAnimation("Resource/TitleBackGround.anim", "bg_tit");
	
	m_pVertex = new Lib::Vertex2D(
		SINGLETON_INSTANCE(Lib::DX11Manager).GetDevice(),
		SINGLETON_INSTANCE(Lib::DX11Manager).GetDeviceContext(),
		SINGLETON_INSTANCE(Lib::Window).GetWindowSize());
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
		Lib::SafeDelete(m_pVertex);
	}

	Lib::SafeDelete(m_pUvController);
	SINGLETON_INSTANCE(Lib::TextureManager).ReleaseTexture(m_TextureIndex2);
	SINGLETON_INSTANCE(Lib::TextureManager).ReleaseTexture(m_TextureIndex);
}


//----------------------------------------------------------------------------------------------------
// Public Functions
//----------------------------------------------------------------------------------------------------

bool TitleBackGround::Update()
{
	if (m_IsTransitionControl) return true;
	
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

void TitleBackGround::Draw()
{
	m_pVertex->SetTexture(
		SINGLETON_INSTANCE(Lib::TextureManager).GetTexture(m_TextureIndex));
	m_pVertex->Draw(&m_Pos,m_pUvController->GetUV(),m_Alpha);
	if (m_IsTransitionControl)
	{
		m_pVertex->SetTexture(
			SINGLETON_INSTANCE(Lib::TextureManager).GetTexture(m_TextureIndex2));
		m_pVertex->Draw(&m_Pos, m_pUvController->GetUV(),1 - m_Alpha);
	}
}

bool TitleBackGround::NextSceneControl()
{
	m_IsTransitionControl = true;
	m_Alpha -= m_AddAlphaValue;
	if (m_Alpha < 0)
	{
		return true;
	}
	return false;
}
