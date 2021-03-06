﻿#include "ResultBackGround.h"
#include "Texture/TextureManager.h"
#include "Window/Window.h"
#include "Dx11/DX11Manager.h"
#include "DxInput/KeyBoard/KeyDevice.h"
#include "../ResultScene.h"
#include "Helper/Helper.h"

namespace Result
{
	const D3DXVECTOR2 BackGround::m_Rect = D3DXVECTOR2(1920, 1080);
	const float BackGround::m_DisplayTime = 2.f;


	BackGround::BackGround(int _textureIndex) :
		m_TextureIndex(_textureIndex)
	{
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

	BackGround::~BackGround()
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

	bool BackGround::Update()
	{
		m_Alpha += m_AddAlphaValue;
		if (ResultScene::KeyCheck())
		{
			m_Alpha = 1.f;
		}
		if (m_Alpha >= 1.f)
		{
			m_Alpha = 1.f;
			return true;
		}
		return false;
	}

	void BackGround::Draw()
	{
		m_pVertex->Draw(&m_Pos, m_pUvController->GetUV(), m_Alpha);
	}
}
