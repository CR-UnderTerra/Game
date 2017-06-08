#include "ScoreBase.h"
#include "Dx11/DX11Manager.h"
#include "Texture/TextureManager.h"
#include "Window/Window.h"


ScoreBase::ScoreBase(D3DXVECTOR2* _pos,LPCTSTR _animName, int _textureIndex) :
m_TextureIndex(_textureIndex)
{
	InitVertex(_pos, &D3DXVECTOR2(150, 64), _animName, &m_Vertex);
	InitVertex(&D3DXVECTOR2(_pos->x + 98, _pos->y), &D3DXVECTOR2(30, 64), "u_feed", &m_NumSymbolVertex);
	InitVertex(&D3DXVECTOR2(_pos->x + 130, _pos->y), &D3DXVECTOR2(30, 64), "Number", &m_NumVertex[0]);
	InitVertex(&D3DXVECTOR2(_pos->x + 160, _pos->y), &D3DXVECTOR2(30, 64), "Number", &m_NumVertex[1]);
}

ScoreBase::~ScoreBase()
{
	ReleaseVertex(&m_NumVertex[1]);
	ReleaseVertex(&m_NumVertex[0]);
	ReleaseVertex(&m_NumSymbolVertex);
	ReleaseVertex(&m_Vertex);
}

void ScoreBase::Draw()
{
	auto VertexDraw = [this](Vertex _vertex)
	{
		_vertex.pVertex->Draw(&_vertex.Pos, _vertex.pUvController->GetUV());
	};

	VertexDraw(m_Vertex);
	VertexDraw(m_NumSymbolVertex);
	VertexDraw(m_NumVertex[0]);
	VertexDraw(m_NumVertex[1]);
}


//----------------------------------------------------------------------------------------------------
// Private Functions
//----------------------------------------------------------------------------------------------------

void ScoreBase::InitVertex(D3DXVECTOR2* _pos, D3DXVECTOR2* _rect, LPCTSTR _animName, Vertex* _vertex)
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

void ScoreBase::ReleaseVertex(Vertex* _vertex)
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
