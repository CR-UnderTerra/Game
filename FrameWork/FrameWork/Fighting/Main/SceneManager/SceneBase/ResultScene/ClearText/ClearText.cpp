/**
 * @file   ClearText.cpp
 * @brief  ClearTextクラスの実装
 * @author kotani
 */
#include "ClearText.h"
#include "Texture/TextureManager.h"
#include "Window/Window.h"
#include "Dx11/DX11Manager.h"
#include "DxInput/KeyBoard/KeyDevice.h"
#include "../ResultScene.h"
#include "../../GameDataManager/GameDataManager.h"
#include "Helper/Helper.h"

const D3DXVECTOR2 ClearText::m_Rect = D3DXVECTOR2(1920.f * 0.7, 450.f * 0.7f);
const float ClearText::m_DisplayTime = 3.f;


ClearText::ClearText(int _textureIndex) :
m_TextureIndex(_textureIndex)
{
	RECT ClientRect = SINGLETON_INSTANCE(Lib::Window).GetWindowSize();
	m_Pos = D3DXVECTOR2(static_cast<float>(ClientRect.right / 2), static_cast<float>(ClientRect.bottom / 2));
	m_pUvController = new Lib::AnimUvController();

	if (SINGLETON_INSTANCE(GameDataManager).GetResultState() == GameDataManager::CLEAR)
	{
		m_Pos.y = 120.f;
		m_pUvController->LoadAnimation("Resource/Text.anim", "l_clear");
	}
	else
	{
		m_Pos.y = 300.f;
		m_pUvController->LoadAnimation("Resource/Text.anim", "l_over");
	}

	m_pVertex = new Lib::Vertex2D(
		SINGLETON_INSTANCE(Lib::DX11Manager).GetDevice(),
		SINGLETON_INSTANCE(Lib::DX11Manager).GetDeviceContext(),
		SINGLETON_INSTANCE(Lib::Window).GetWindowSize());
	m_pVertex->Init(&m_Rect, m_pUvController->GetUV());
	m_pVertex->SetTexture(
		SINGLETON_INSTANCE(Lib::TextureManager).GetTexture(m_TextureIndex));
	m_AddAlphaValue = 1.f / (m_DisplayTime * 60);
}

ClearText::~ClearText()
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

bool ClearText::Update()
{
	m_Alpha += m_AddAlphaValue;
	if (m_Alpha > 1.f)
	{
		m_Alpha = 1.f;
		return true;
	}
	if (ResultScene::KeyCheck())
	{
		m_Alpha = 1.f;
	}
	return false;
}

void ClearText::Draw()
{
	m_pVertex->Draw(&m_Pos, m_pUvController->GetUV(), m_Alpha);
}
