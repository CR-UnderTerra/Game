﻿/**
 * @file   HandBase.cpp
 * @brief  HandBaseクラスの実装
 * @author kotani
 */
#include "HandBase.h"
#include "Texture/TextureManager.h"
#include "Window/Window.h"
#include "Dx11/DX11Manager.h"

const D3DXVECTOR2 HandBase::m_Rect = D3DXVECTOR2(128, 256);
const float HandBase::m_Acceleration = 3.f;


HandBase::HandBase(D3DXVECTOR2* _pos, LPCTSTR _animName, int _textureIndex) :
m_Pos(*_pos),
m_TextureIndex(_textureIndex)
{
	m_pAnimUvController = new Lib::AnimUvController();
	m_pAnimUvController->LoadAnimation("Resource/test_001.anim", _animName);

	m_pVertex = new Lib::Vertex2D(
		SINGLETON_INSTANCE(Lib::DX11Manager).GetDevice(),
		SINGLETON_INSTANCE(Lib::DX11Manager).GetDeviceContext(),
		SINGLETON_INSTANCE(Lib::Window).GetWindowHandle());
	m_pVertex->Init(&m_Rect, m_pAnimUvController->GetUV());
	m_pVertex->SetTexture(
		SINGLETON_INSTANCE(Lib::TextureManager).GetTexture(m_TextureIndex));
}


HandBase::~HandBase()
{
	if (m_pVertex != NULL)
	{
		m_pVertex->Release();
		delete m_pVertex;
		m_pVertex = NULL;
	}

	delete m_pAnimUvController;
	m_pAnimUvController = NULL;
}