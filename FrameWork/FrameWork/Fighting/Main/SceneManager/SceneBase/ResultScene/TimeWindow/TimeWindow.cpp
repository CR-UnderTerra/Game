/**
 * @file   TimeWindow.cpp
 * @brief  TimeWindowクラスの実装
 * @author kotani
 */
#include "TimeWindow.h"
#include "Texture/TextureManager.h"
#include "Window/Window.h"
#include "Dx11/DX11Manager.h"
#include "../ResultScene.h"
#include "../../GameDataManager/GameDataManager.h"

const float TimeWindow::m_DisplayTime = 2.f;


TimeWindow::TimeWindow() :
m_Alpha(0)
{
	SINGLETON_INSTANCE(Lib::TextureManager).Load("Resource/test_001.png", &m_TextureIndex);
	RECT ClientRect;
	GetClientRect(SINGLETON_INSTANCE(Lib::Window).GetWindowHandle(), &ClientRect);

	m_Pos = D3DXVECTOR2(550, 600);
	InitVertex(&m_Pos, &D3DXVECTOR2(24, 64), "t_colon", &m_ColonVertex);

	InitVertex(&D3DXVECTOR2(m_Pos.x - (90.f - m_ColonVertex.Rect.x / 2), m_Pos.y), &D3DXVECTOR2(45, 96), "Number", &m_NumVertex[0]);
	InitVertex(&D3DXVECTOR2(m_Pos.x - (45.f - m_ColonVertex.Rect.x / 2), m_Pos.y), &D3DXVECTOR2(45, 96), "Number", &m_NumVertex[1]);
	InitVertex(&D3DXVECTOR2(m_Pos.x + (45.f - m_ColonVertex.Rect.x / 2), m_Pos.y), &D3DXVECTOR2(45, 96), "Number", &m_NumVertex[2]);
	InitVertex(&D3DXVECTOR2(m_Pos.x + (90.f - m_ColonVertex.Rect.x / 2), m_Pos.y), &D3DXVECTOR2(45, 96), "Number", &m_NumVertex[3]);

	m_Minute = SINGLETON_INSTANCE(GameDataManager).GetResult().Minute;
	m_Second = SINGLETON_INSTANCE(GameDataManager).GetResult().Second;

	m_NumVertex[0].pUvController->SetAnimCount((m_Minute / 10) % 10);
	m_NumVertex[1].pUvController->SetAnimCount(m_Minute % 10);
	m_NumVertex[2].pUvController->SetAnimCount((m_Second / 10) % 10);
	m_NumVertex[3].pUvController->SetAnimCount(m_Second % 10);
	m_AddAlphaValue = 1.f / (m_DisplayTime * 60);
}


TimeWindow::~TimeWindow()
{
	ReleaseVertex(&m_NumVertex[3]);
	ReleaseVertex(&m_NumVertex[2]);
	ReleaseVertex(&m_NumVertex[1]);
	ReleaseVertex(&m_NumVertex[0]);

	ReleaseVertex(&m_ColonVertex);
	SINGLETON_INSTANCE(Lib::TextureManager).ReleaseTexture(m_TextureIndex);
}


//----------------------------------------------------------------------------------------------------
// Public Functions
//----------------------------------------------------------------------------------------------------

bool TimeWindow::Update()
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

void TimeWindow::Draw()
{
	m_ColonVertex.pVertex->Draw(&m_ColonVertex.Pos, m_ColonVertex.pUvController->GetUV(),m_Alpha);

	for (int i = 0; i < 4; i++)
	{
		m_NumVertex[i].pVertex->Draw(&m_NumVertex[i].Pos, m_NumVertex[i].pUvController->GetUV(), m_Alpha);
	}
}


//----------------------------------------------------------------------------------------------------
// Private Functions
//----------------------------------------------------------------------------------------------------

void TimeWindow::InitVertex(D3DXVECTOR2* _pos, D3DXVECTOR2* _rect, LPCTSTR _animName, Vertex* _vertex)
{
	_vertex->Pos = *_pos;
	_vertex->Rect = *_rect;
	_vertex->pUvController = new Lib::AnimUvController();
	_vertex->pUvController->LoadAnimation("Resource/test_001.anim", _animName);
	_vertex->pVertex = new Lib::Vertex2D(
		SINGLETON_INSTANCE(Lib::DX11Manager).GetDevice(),
		SINGLETON_INSTANCE(Lib::DX11Manager).GetDeviceContext(),
		SINGLETON_INSTANCE(Lib::Window).GetWindowHandle());
	_vertex->pVertex->Init(&_vertex->Rect, _vertex->pUvController->GetUV());
	_vertex->pVertex->SetTexture(
		SINGLETON_INSTANCE(Lib::TextureManager).GetTexture(m_TextureIndex));
}

void TimeWindow::ReleaseVertex(Vertex* _vertex)
{
	if (_vertex->pVertex != NULL)
	{
		_vertex->pVertex->Release();
		delete _vertex->pVertex;
		_vertex->pVertex = NULL;
	}

	delete _vertex->pUvController;
	_vertex->pUvController = NULL;
}
