﻿/**
 * @file   HpIcon.cpp
 * @brief  HpIconクラスの実装
 * @author kotani
 */
#include "HpIcon.h"
#include "Texture/TextureManager.h"
#include "Window/Window.h"
#include "Dx11/DX11Manager.h"

const D3DXVECTOR2 HpIcon::m_Rect = D3DXVECTOR2(75 * 0.5, 75 * 0.5);


HpIcon::HpIcon(int _textureIndex, D3DXVECTOR2* _pos) :
m_TextureIndex(_textureIndex),
m_Pos(*_pos)
{
	m_pUvController = new Lib::AnimUvController();
	m_pUvController->LoadAnimation("Resource/test_001.anim", "h_picture");
	m_pVertex = new Lib::Vertex2D(
		SINGLETON_INSTANCE(Lib::DX11Manager).GetDevice(),
		SINGLETON_INSTANCE(Lib::DX11Manager).GetDeviceContext(),
		SINGLETON_INSTANCE(Lib::Window).GetWindowSize());
	m_pVertex->Init(&m_Rect, m_pUvController->GetUV());
	m_pVertex->SetTexture(
		SINGLETON_INSTANCE(Lib::TextureManager).GetTexture(m_TextureIndex));
}

HpIcon::~HpIcon()
{
	if (m_pVertex != NULL)
	{
		m_pVertex->Release();
		delete m_pVertex;
	}

	delete m_pUvController;
	m_pUvController = NULL;
}


//----------------------------------------------------------------------------------------------------
// Public Functions
//----------------------------------------------------------------------------------------------------

void HpIcon::Update()
{
}

void HpIcon::Draw()
{
	Vibration();
	m_pVertex->Draw(&D3DXVECTOR2(m_Pos.x + m_WidthVibValue, m_Pos.y + m_HeightVibValue), m_pUvController->GetUV());
}
