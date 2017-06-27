#include "KnifeBar.h"
#include "Texture/TextureManager.h"
#include "Window/Window.h"
#include "Dx11/DX11Manager.h"

const D3DXVECTOR2 KnifeBar::m_Rect(96*0.7f, 60*0.7f);

KnifeBar::KnifeBar(int m_TextureIndex,D3DXVECTOR2* _GaugeTopPos) :
m_TextureIndex(m_TextureIndex),
m_GaugeTopPos(*_GaugeTopPos),
m_OffsetPos(0, 0),
m_IsEnable(false)
{
	m_pAnimUvController = new Lib::AnimUvController();
	m_pAnimUvController->LoadAnimation("Resource/test_006.anim", "d_mark");

	m_pVertex = new Lib::Vertex2D(
		SINGLETON_INSTANCE(Lib::DX11Manager).GetDevice(),
		SINGLETON_INSTANCE(Lib::DX11Manager).GetDeviceContext(),
		SINGLETON_INSTANCE(Lib::Window).GetWindowSize());
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
	if (!m_IsEnable) return;
	m_Distance -= m_Velocity;
	m_OffsetPos.y += m_AddValue;
	if (m_Distance <= 0)
	{
		m_IsEnable = false;
		m_OffsetPos.y = 0;
	}
}


//----------------------------------------------------------------------------------------------------
// Public Functions
//----------------------------------------------------------------------------------------------------

void KnifeBar::Draw()
{
	if (!m_IsEnable) return;
	m_pVertex->Draw(&D3DXVECTOR2(m_GaugeTopPos.x, m_GaugeTopPos.y + m_OffsetPos.y), m_pAnimUvController->GetUV());
}

void KnifeBar::SetIsEnable(bool _enable)
{
	m_OffsetPos.y = 0;
	m_IsEnable = _enable;
}
