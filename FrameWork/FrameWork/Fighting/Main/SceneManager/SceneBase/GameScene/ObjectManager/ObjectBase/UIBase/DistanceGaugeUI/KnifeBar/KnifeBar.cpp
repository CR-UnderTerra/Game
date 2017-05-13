#include "KnifeBar.h"
#include "Texture/TextureManager.h"
#include "Window/Window.h"
#include "Dx11/DX11Manager.h"

const D3DXVECTOR2 KnifeBar::m_Rect(64, 16);

KnifeBar::KnifeBar(int m_TextureIndex,D3DXVECTOR2* _GaugeTopPos) :
m_TextureIndex(m_TextureIndex),
m_GaugeTopPos(*_GaugeTopPos),
m_Offset(0, 0)
{
	m_IsVisible = false;
	m_pAnimUvController = new Lib::AnimUvController();
	m_pAnimUvController->LoadAnimation("Resource/test_001.anim", "d_mark");

	m_pVertex = new Lib::Vertex2D(
		SINGLETON_INSTANCE(Lib::DX11Manager).GetDevice(),
		SINGLETON_INSTANCE(Lib::DX11Manager).GetDeviceContext(),
		SINGLETON_INSTANCE(Lib::Window).GetWindowHandle());
	m_pVertex->Init(&m_Rect, m_pAnimUvController->GetUV());
	m_pVertex->SetTexture(
		SINGLETON_INSTANCE(Lib::TextureManager).GetTexture(m_TextureIndex));
}


KnifeBar::~KnifeBar()
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

void KnifeBar::Update()
{
	if (!m_IsVisible) return;
	m_Distance -= m_Velocity;
	m_Offset.y += m_AddValue;
	if (m_Distance <= 0)
	{
		m_IsVisible = false;
		m_Offset.y = 0;
	}
}

void KnifeBar::Draw()
{
	if (!m_IsVisible) return;
	m_pVertex->Draw(&D3DXVECTOR2(m_GaugeTopPos.x, m_GaugeTopPos.y + m_Offset.y), m_pAnimUvController->GetUV());
}
