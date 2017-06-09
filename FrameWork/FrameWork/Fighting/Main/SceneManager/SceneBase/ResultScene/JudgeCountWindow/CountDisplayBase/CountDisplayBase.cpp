#include "CountDisplayBase.h"
#include "Dx11/DX11Manager.h"
#include "Texture/TextureManager.h"
#include "Window/Window.h"


CountDisplayBase::CountDisplayBase(D3DXVECTOR2* _pos, LPCTSTR _animName, int _textureIndex) :
	m_TextureIndex(_textureIndex)
{
	InitVertex(_pos, &D3DXVECTOR2(200, 32), _animName, &m_Vertex);
	InitVertex(&D3DXVECTOR2(_pos->x + 120.f, _pos->y), &D3DXVECTOR2(30 * 0.7f, 64 * 0.7f), "u_feed", &m_NumSymbolVertex);
	InitVertex(&D3DXVECTOR2(_pos->x + 145.f, _pos->y), &D3DXVECTOR2(30 * 0.7f, 64 * 0.7f), "Number", &m_NumVertex[0]);
	InitVertex(&D3DXVECTOR2(_pos->x + 165.f, _pos->y), &D3DXVECTOR2(30 * 0.7f, 64 * 0.7f), "Number", &m_NumVertex[1]);
}

CountDisplayBase::~CountDisplayBase()
{
	ReleaseVertex(&m_NumVertex[1]);
	ReleaseVertex(&m_NumVertex[0]);
	ReleaseVertex(&m_NumSymbolVertex);
	ReleaseVertex(&m_Vertex);
}

void CountDisplayBase::Draw(float _alpha)
{
	auto VertexDraw = [this](Vertex _vertex, float _alpha)
	{
		_vertex.pVertex->Draw(&_vertex.Pos, _vertex.pUvController->GetUV(), _alpha);
	};

	VertexDraw(m_Vertex, _alpha);
	VertexDraw(m_NumSymbolVertex, _alpha);
	VertexDraw(m_NumVertex[0], _alpha);
	VertexDraw(m_NumVertex[1], _alpha);
}


//----------------------------------------------------------------------------------------------------
// Private Functions
//----------------------------------------------------------------------------------------------------

void CountDisplayBase::InitVertex(D3DXVECTOR2* _pos, D3DXVECTOR2* _rect, LPCTSTR _animName, Vertex* _vertex)
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

void CountDisplayBase::ReleaseVertex(Vertex* _vertex)
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
