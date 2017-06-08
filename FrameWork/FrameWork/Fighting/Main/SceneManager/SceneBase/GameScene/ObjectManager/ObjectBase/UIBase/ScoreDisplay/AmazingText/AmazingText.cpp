/**
 * @file   AmazingText.cpp
 * @brief  AmazingTextクラスの実装
 * @author kotani
 */
#include "AmazingText.h"
#include "Dx11/DX11Manager.h"
#include "Texture/TextureManager.h"
#include "Window/Window.h"
#include "../../../../../../GameDataManager/GameDataManager.h"


AmazingText::AmazingText(int _textureIndex, D3DXVECTOR2* _pos) :
m_TextureIndex(_textureIndex)
{
	InitVertex(_pos, &D3DXVECTOR2(200, 64), "e_ama", &m_Vertex);
	InitVertex(&D3DXVECTOR2(_pos->x + 130, _pos->y), &D3DXVECTOR2(30, 64), "Number", &m_NumVertex[0]);
	InitVertex(&D3DXVECTOR2(_pos->x + 160, _pos->y), &D3DXVECTOR2(30, 64), "Number", &m_NumVertex[1]);
}

AmazingText::~AmazingText()
{
	ReleaseVertex(&m_NumVertex[1]);
	ReleaseVertex(&m_NumVertex[0]);
	ReleaseVertex(&m_Vertex);
}


//----------------------------------------------------------------------------------------------------
// Public Functions
//----------------------------------------------------------------------------------------------------

void AmazingText::Update()
{
	int amazingCount = SINGLETON_INSTANCE(GameDataManager).GetResult().AmazingCount;
	m_NumVertex[0].pUvController->SetAnimCount((amazingCount / 10) % 10);
	m_NumVertex[1].pUvController->SetAnimCount(amazingCount % 10);
}

void AmazingText::Draw()
{
	m_Vertex.pVertex->Draw(&m_Vertex.Pos, m_Vertex.pUvController->GetUV());
	m_NumVertex[0].pVertex->Draw(&m_NumVertex[0].Pos, m_NumVertex[0].pUvController->GetUV());
	m_NumVertex[1].pVertex->Draw(&m_NumVertex[1].Pos, m_NumVertex[1].pUvController->GetUV());
}


//----------------------------------------------------------------------------------------------------
// Private Functions
//----------------------------------------------------------------------------------------------------

void AmazingText::InitVertex(D3DXVECTOR2* _pos, D3DXVECTOR2* _rect, LPCTSTR _animName, Vertex* _vertex)
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

void AmazingText::ReleaseVertex(Vertex* _vertex)
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
