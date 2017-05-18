﻿/**
 * @file   TimerUI.cpp
 * @brief  クラスの実装
 * @author kotani
 */
#include "TimerUI.h"
#include "Texture/TextureManager.h"
#include "Window/Window.h"
#include "Dx11/DX11Manager.h"


TimerUI::TimerUI() :
m_Count(0),
m_Second(0),
m_Minute(0)
{
	SINGLETON_INSTANCE(Lib::TextureManager).Load("Resource/Number.png",&m_TextureIndex);
	m_Pos = D3DXVECTOR2(1170, 80);
	InitVertex(&m_Pos, &D3DXVECTOR2(106, 64), "Number", &m_FrameVertex);
	InitVertex(&m_Pos, &D3DXVECTOR2(16, 64), "Number", &m_ColonVertex);
	m_ColonVertex.pUvController->SetAnimCount(6);

	InitVertex(&D3DXVECTOR2(m_Pos.x - (30.f - 8.f), m_Pos.y), &D3DXVECTOR2(30, 64), "Number", &m_NumVertex[0]);
	InitVertex(&D3DXVECTOR2(m_Pos.x - (60.f - 8.f), m_Pos.y), &D3DXVECTOR2(30, 64), "Number", &m_NumVertex[1]);
	InitVertex(&D3DXVECTOR2(m_Pos.x + (30.f - 8.f), m_Pos.y), &D3DXVECTOR2(30, 64), "Number", &m_NumVertex[2]);
	InitVertex(&D3DXVECTOR2(m_Pos.x + (60.f - 8.f), m_Pos.y), &D3DXVECTOR2(30, 64), "Number", &m_NumVertex[3]);
}

TimerUI::~TimerUI()
{
	ReleaseVertex(&m_NumVertex[3]);
	ReleaseVertex(&m_NumVertex[2]);
	ReleaseVertex(&m_NumVertex[1]);
	ReleaseVertex(&m_NumVertex[0]);

	ReleaseVertex(&m_ColonVertex);
	ReleaseVertex(&m_FrameVertex);
	SINGLETON_INSTANCE(Lib::TextureManager).ReleaseTexture(m_TextureIndex);
}


//----------------------------------------------------------------------------------------------------
// Public Functions
//----------------------------------------------------------------------------------------------------

void TimerUI::Update()
{
	if (m_Count > 60)
	{
		m_Count = 0;
		m_Second++;
		if (m_Second > 60)
		{
			m_Second = 0;
			m_Minute++;
		}
	}
	m_Count++;

	m_NumVertex[0].pUvController->SetAnimCount((m_Minute / 10) % 10);
	m_NumVertex[1].pUvController->SetAnimCount(m_Minute % 10);
	m_NumVertex[2].pUvController->SetAnimCount((m_Second / 10) % 10);
	m_NumVertex[3].pUvController->SetAnimCount(m_Second % 10);
}

void TimerUI::Draw()
{
	m_FrameVertex.pVertex->Draw(&m_FrameVertex.Pos, m_FrameVertex.pUvController->GetUV());
	m_ColonVertex.pVertex->Draw(&m_ColonVertex.Pos, m_ColonVertex.pUvController->GetUV());

	for (int i = 0; i < 4; i++)
	{
		m_NumVertex[i].pVertex->Draw(&m_NumVertex[i].Pos, m_NumVertex[i].pUvController->GetUV());
	}
}


//----------------------------------------------------------------------------------------------------
// Private Functions
//----------------------------------------------------------------------------------------------------

void TimerUI::InitVertex(D3DXVECTOR2* _pos, D3DXVECTOR2* _rect, LPCTSTR _animName, Vertex* _vertex)
{
	_vertex->Pos = *_pos;
	_vertex->Rect = *_rect;
	_vertex->pUvController = new Lib::AnimUvController();
	_vertex->pUvController->LoadAnimation("Resource/Number.anim", _animName);
	_vertex->pVertex = new Lib::Vertex2D(
		SINGLETON_INSTANCE(Lib::DX11Manager).GetDevice(),
		SINGLETON_INSTANCE(Lib::DX11Manager).GetDeviceContext(),
		SINGLETON_INSTANCE(Lib::Window).GetWindowHandle());
	_vertex->pVertex->Init(&_vertex->Rect, _vertex->pUvController->GetUV());
	_vertex->pVertex->SetTexture(
		SINGLETON_INSTANCE(Lib::TextureManager).GetTexture(m_TextureIndex));
}

void TimerUI::ReleaseVertex(Vertex* _vertex)
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