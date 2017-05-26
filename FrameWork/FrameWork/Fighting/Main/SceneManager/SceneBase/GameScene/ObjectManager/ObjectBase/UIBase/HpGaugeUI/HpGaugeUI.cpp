/**
 * @file   HpGaugeUI.cpp
 * @brief  HpGaugeUIクラスの実装
 * @author kotani
 */
#include "HpGaugeUI.h"
#include "Texture/TextureManager.h"
#include "Window/Window.h"
#include "Dx11/DX11Manager.h"
#include "HpIcon/HpIcon.h"
#include "../../../../GameDataManager/GameDataManager.h"

const D3DXVECTOR2 HpGaugeUI::m_Rect = D3DXVECTOR2(225,96);


HpGaugeUI::HpGaugeUI(int _textureIndex) :
m_TextureIndex(_textureIndex)
{
	m_pUvController = new Lib::AnimUvController();
	m_pUvController->LoadAnimation("Resource/test_001.anim", "h_frame");
	m_Pos = D3DXVECTOR2(135, 75);
	m_pVertex = new Lib::Vertex2D(
		SINGLETON_INSTANCE(Lib::DX11Manager).GetDevice(),
		SINGLETON_INSTANCE(Lib::DX11Manager).GetDeviceContext(),
		SINGLETON_INSTANCE(Lib::Window).GetWindowHandle());
	m_pVertex->Init(&m_Rect, m_pUvController->GetUV());
	m_pVertex->SetTexture(
		SINGLETON_INSTANCE(Lib::TextureManager).GetTexture(m_TextureIndex));

	for (unsigned int i = 0; i < m_pHpIcon.size(); i++)
	{
		m_pHpIcon[i] = new HpIcon(m_TextureIndex, &D3DXVECTOR2(static_cast<FLOAT>((m_Pos.x - 75) + 75 * i), m_Pos.y));
	}
}


HpGaugeUI::~HpGaugeUI()
{
	for (int i = m_pHpIcon.size() - 1; i >= 0; i--)
	{
		delete m_pHpIcon[i];
		m_pHpIcon[i] = NULL;
	}

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

void HpGaugeUI::Update()
{
	for (unsigned int i = 0; i < m_pHpIcon.size(); i++)
	{
		m_pHpIcon[i]->Update();
	}
}

void HpGaugeUI::Draw()
{
	m_pVertex->Draw(&m_Pos, m_pUvController->GetUV());
	if (SINGLETON_INSTANCE(GameDataManager).GetPlayerHp() < 0) return;
	for (int i = 0; i < SINGLETON_INSTANCE(GameDataManager).GetPlayerHp(); i++)
	{
		m_pHpIcon[i]->Draw();
	}
}
