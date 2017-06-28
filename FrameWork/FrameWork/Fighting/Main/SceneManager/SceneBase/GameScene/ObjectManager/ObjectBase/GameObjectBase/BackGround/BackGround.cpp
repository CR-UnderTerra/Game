/**
 * @file   BackGround.cpp
 * @brief  BackGroundクラスの実装
 * @author kotani
 */
#include "BackGround.h"
#include "Texture/TextureManager.h"
#include "Window/Window.h"
#include "Dx11/DX11Manager.h"
#include "Helper/Helper.h"
#include "Event/EventManager.h"

const D3DXVECTOR2 BackGround::m_Rect = D3DXVECTOR2(1350, 1080);


BackGround::BackGround(int _textureIndex) :
m_TextureIndex(_textureIndex),
m_Alfa(1.f),
m_Alfa2(1.f),
m_Alfa3(0.f),
m_Alfa4(0.f),
m_Alfa5(0.f)
{
	SINGLETON_INSTANCE(Lib::TextureManager).Load("Resource/test_009.png", &m_PurpleSky);
	SINGLETON_INSTANCE(Lib::TextureManager).Load("Resource/test_010.png", &m_RedSky);
	SINGLETON_INSTANCE(Lib::TextureManager).Load("Resource/test_011.png", &m_OrangeSky);
	SINGLETON_INSTANCE(Lib::TextureManager).Load("Resource/test_003.png", &m_BlueSky);

	RECT ClientRect = SINGLETON_INSTANCE(Lib::Window).GetWindowSize();
	m_Pos = D3DXVECTOR2(static_cast<float>(ClientRect.right / 2), static_cast<float>(ClientRect.bottom / 2));
	m_pAnimUvController = new Lib::AnimUvController();
	m_pAnimUvController->LoadAnimation("Resource/test_003.anim", "bg01");

	m_pVertex = new Lib::Vertex2D(
		SINGLETON_INSTANCE(Lib::DX11Manager).GetDevice(),
		SINGLETON_INSTANCE(Lib::DX11Manager).GetDeviceContext(),
		SINGLETON_INSTANCE(Lib::Window).GetWindowSize());
	m_pVertex->Init(&m_Rect, m_pAnimUvController->GetUV());
	m_pVertex->SetTexture(
		SINGLETON_INSTANCE(Lib::TextureManager).GetTexture(m_TextureIndex));
	
	SINGLETON_INSTANCE(Lib::EventManager).AddEvent("EnemyDamage", [this]()
	{
		m_WidthTime = 30;
	});

	m_pVertex2 = new Lib::Vertex2D(
		SINGLETON_INSTANCE(Lib::DX11Manager).GetDevice(),
		SINGLETON_INSTANCE(Lib::DX11Manager).GetDeviceContext(),
		SINGLETON_INSTANCE(Lib::Window).GetWindowSize());
	m_pVertex2->Init(&m_Rect, m_pAnimUvController->GetUV());
}

BackGround::~BackGround()
{
	if (m_pVertex != NULL)
	{
		m_pVertex->Release();
		Lib::SafeDelete(m_pVertex);
	}

	if (m_pVertex2 != NULL)
	{
		m_pVertex2->Release();
		Lib::SafeDelete(m_pVertex2);
	}

	Lib::SafeDelete(m_pAnimUvController);

	SINGLETON_INSTANCE(Lib::TextureManager).ReleaseTexture(m_BlueSky);
	SINGLETON_INSTANCE(Lib::TextureManager).ReleaseTexture(m_OrangeSky);
	SINGLETON_INSTANCE(Lib::TextureManager).ReleaseTexture(m_RedSky);
	SINGLETON_INSTANCE(Lib::TextureManager).ReleaseTexture(m_PurpleSky);
}


//----------------------------------------------------------------------------------------------------
// Public Functions
//----------------------------------------------------------------------------------------------------

void BackGround::Update()
{
	m_EnemyLine = SINGLETON_INSTANCE(GameDataManager).GetCurrentEnemyLine();

	if (m_EnemyLine > 14)
	{
		if (m_EnemyLine == 20)
		{
			m_Alfa2 = 1.f;
			m_Alfa3 = 0.f;
		}
		if (m_EnemyLine == 19)
		{
			m_Alfa2 = 0.9f;
			m_Alfa3 = 0.1f;
		}
		if (m_EnemyLine == 18)
		{
			m_Alfa2 = 0.8f;
			m_Alfa3 = 0.2f;
		}
		if (m_EnemyLine == 17)
		{
			m_Alfa2 = 0.6f;
			m_Alfa3 = 0.4f;
		}
		if (m_EnemyLine == 16)
		{
			m_Alfa2 = 0.4f;
			m_Alfa3 = 0.6f;
		}
		if (m_EnemyLine == 15)
		{
			m_Alfa2 = 0.2f;
			m_Alfa3 = 0.8f;
		}
		//m_Alfa2 -= 0.001f;
		//m_Alfa3 += 0.001f;
	}
	if (m_EnemyLine == 14)
	{
		m_Alfa2 = 0.f;
		m_Alfa3 = 1.f;
	}
	if (m_EnemyLine < 14 && m_EnemyLine > 8)
	{
		if (m_EnemyLine == 13)
		{
			m_Alfa3 = 0.8f;
			m_Alfa4 = 0.2f;
		}
		if (m_EnemyLine == 12)
		{
			m_Alfa3 = 0.6f;
			m_Alfa4 = 0.4f;
		}
		if (m_EnemyLine == 11)
		{
			m_Alfa3 = 0.4f;
			m_Alfa4 = 0.6f;
		}
		if (m_EnemyLine == 10)
		{
			m_Alfa3 = 0.2f;
			m_Alfa4 = 0.8f;
		}
		if (m_EnemyLine == 9)
		{
			m_Alfa3 = 0.1f;
			m_Alfa4 = 0.9f;
		}
		//m_Alfa3 -= 0.001f;
		//m_Alfa4 += 0.001f;
	}
	if (m_EnemyLine == 8)
	{
		m_Alfa3 = 0.f;
		m_Alfa4 = 1.f;
	}
	if (m_EnemyLine < 8 && m_EnemyLine > 2)
	{
		if (m_EnemyLine == 7)
		{
			m_Alfa4 = 0.8f;
			m_Alfa5 = 0.2f;
		}
		if (m_EnemyLine == 6)
		{
			m_Alfa4 = 0.6f;
			m_Alfa5 = 0.4f;
		}
		if (m_EnemyLine == 5)
		{
			m_Alfa4 = 0.4f;
			m_Alfa5 = 0.6f;
		}
		if (m_EnemyLine == 4)
		{
			m_Alfa4 = 0.2f;
			m_Alfa5 = 0.8f;
		}
		if (m_EnemyLine == 3)
		{
			m_Alfa4 = 0.1f;
			m_Alfa5 = 0.9f;
		}
		//m_Alfa4 -= 0.001f;
		//m_Alfa5 += 0.001f;
	}
	if (m_EnemyLine == 2)
	{
		m_Alfa4 = 0.f;
		m_Alfa5 = 1.f;
	}
}

void BackGround::Draw()
{
	m_pVertex->Draw(&m_Pos, m_pAnimUvController->GetUV());
	if (m_EnemyLine >= 14)
	{
		m_pVertex->Draw(&m_Pos, m_pAnimUvController->GetUV(), m_Alfa2);
		Vibration();
		m_pVertex->Draw(&D3DXVECTOR2(m_Pos.x + m_WidthVibValue, m_Pos.y), m_pAnimUvController->GetUV());
	}
	if (m_EnemyLine >= 14)
	{
		m_pVertex->Draw(&D3DXVECTOR2(m_Pos.x + m_WidthVibValue, m_Pos.y), m_pAnimUvController->GetUV(), m_Alfa2);
		m_pVertex->SetTexture(
			SINGLETON_INSTANCE(Lib::TextureManager).GetTexture(m_PurpleSky));
	}
	if (m_EnemyLine >= 8)
	{
		m_pVertex2->Draw(&m_Pos, m_pAnimUvController->GetUV(), m_Alfa3);
		m_pVertex2->Draw(&D3DXVECTOR2(m_Pos.x + m_WidthVibValue, m_Pos.y), m_pAnimUvController->GetUV(), m_Alfa3);
		m_pVertex2->SetTexture(
			SINGLETON_INSTANCE(Lib::TextureManager).GetTexture(m_RedSky));
	}
	if (m_EnemyLine <= 14 && m_EnemyLine >= 8)
	{
		m_pVertex->Draw(&m_Pos, m_pAnimUvController->GetUV(), m_Alfa4);
		m_pVertex->Draw(&D3DXVECTOR2(m_Pos.x + m_WidthVibValue, m_Pos.y), m_pAnimUvController->GetUV(), m_Alfa4);
		m_pVertex->SetTexture(
			SINGLETON_INSTANCE(Lib::TextureManager).GetTexture(m_OrangeSky));
	}
	if (m_EnemyLine <= 8 && m_EnemyLine >= 0)
	{
		m_pVertex2->Draw(&m_Pos, m_pAnimUvController->GetUV(), m_Alfa5);
		m_pVertex2->Draw(&D3DXVECTOR2(m_Pos.x + m_WidthVibValue, m_Pos.y), m_pAnimUvController->GetUV(), m_Alfa5);
		m_pVertex2->SetTexture(
			SINGLETON_INSTANCE(Lib::TextureManager).GetTexture(m_BlueSky));
	}
}
