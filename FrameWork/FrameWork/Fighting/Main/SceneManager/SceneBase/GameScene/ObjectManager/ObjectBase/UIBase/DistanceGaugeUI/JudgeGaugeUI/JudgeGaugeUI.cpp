/**
 * @file   JudgeGaugeUI.cpp
 * @brief  JudgeGaugeUIクラスの実装
 * @author kotani
 */
#include "JudgeGaugeUI.h"
#include "Texture/TextureManager.h"
#include "Window/Window.h"
#include "Dx11/DX11Manager.h"


JudgeGaugeUI::JudgeGaugeUI(int _textureIndex, D3DXVECTOR2* _distanceGaugeButtomPos) :
m_TextureIndex(_textureIndex),
m_DistanceGaugeButtomPos(*_distanceGaugeButtomPos)
{
	SINGLETON_INSTANCE(Lib::TextureManager).Load("Resource/test_006.png",&m_TextureIndex);
	D3DXVECTOR2 pos = m_DistanceGaugeButtomPos;
	D3DXVECTOR2 rect = D3DXVECTOR2(45, 18);

	InitJudgeVertex(&m_FantasticJudgeVertex, &D3DXVECTOR2(pos.x - 75.f, pos.y - rect.y / 2), &rect, "d_line3");

	rect = D3DXVECTOR2(45, 42);
	InitJudgeVertex(&m_AmazingJudgeVertex, &D3DXVECTOR2(pos.x - 75.f,
		m_FantasticJudgeVertex.Pos.y - (m_FantasticJudgeVertex.Rect.y / 2 + rect.y / 2)), &rect, "d_line2");

	rect = D3DXVECTOR2(45, 60);
	InitJudgeVertex(&m_GoodJudgeVertex, &D3DXVECTOR2(pos.x - 75.f,
		m_AmazingJudgeVertex.Pos.y - (m_AmazingJudgeVertex.Rect.y / 2 + rect.y / 2)), &rect, "d_line1");
}

JudgeGaugeUI::~JudgeGaugeUI()
{
	ReleaseJudgeVertex(&m_FantasticJudgeVertex);
	ReleaseJudgeVertex(&m_AmazingJudgeVertex);
	ReleaseJudgeVertex(&m_GoodJudgeVertex);
	SINGLETON_INSTANCE(Lib::TextureManager).ReleaseTexture(m_TextureIndex);
}


//----------------------------------------------------------------------------------------------------
// Public Functions
//----------------------------------------------------------------------------------------------------

void JudgeGaugeUI::Update()
{
}

void JudgeGaugeUI::Draw()
{
	Vibration();
	m_GoodJudgeVertex.pVertex->Draw(&D3DXVECTOR2(m_GoodJudgeVertex.Pos.x, m_GoodJudgeVertex.Pos.y + m_VibValue), m_GoodJudgeVertex.pUvController->GetUV());
	m_AmazingJudgeVertex.pVertex->Draw(&D3DXVECTOR2(m_AmazingJudgeVertex.Pos.x, m_AmazingJudgeVertex.Pos.y + m_VibValue), m_AmazingJudgeVertex.pUvController->GetUV());
	m_FantasticJudgeVertex.pVertex->Draw(&D3DXVECTOR2(m_FantasticJudgeVertex.Pos.x, m_FantasticJudgeVertex.Pos.y + m_VibValue), m_FantasticJudgeVertex.pUvController->GetUV());
}

JudgeGaugeUI::JUDGE JudgeGaugeUI::Judge(D3DXVECTOR2 _KnifeBarPos)
{
	if (_KnifeBarPos.y > m_FantasticJudgeVertex.Pos.y - m_FantasticJudgeVertex.Rect.y / 2)
	{
		return FANTASTIC_JUDGE;
	}
	else if (_KnifeBarPos.y > m_AmazingJudgeVertex.Pos.y - m_AmazingJudgeVertex.Rect.y / 2)
	{
		return AMAZING_JUDGE;
	}
	else if (_KnifeBarPos.y > m_GoodJudgeVertex.Pos.y - m_GoodJudgeVertex.Rect.y / 2)
	{
		return GOOD_JUDGE;
	}
	return FAILED_JUDGE;
}


//----------------------------------------------------------------------------------------------------
// Private Functions
//----------------------------------------------------------------------------------------------------

void JudgeGaugeUI::InitJudgeVertex(JudgeGaugeUI::JudgeVertex* _pJudgeVertex, D3DXVECTOR2* _pos, D3DXVECTOR2* _rect, LPCTSTR _animName)
{
	_pJudgeVertex->pUvController = new Lib::AnimUvController();
	_pJudgeVertex->pUvController->LoadAnimation("Resource/test_006.anim", _animName);
	_pJudgeVertex->pVertex = new Lib::Vertex2D(
		SINGLETON_INSTANCE(Lib::DX11Manager).GetDevice(),
		SINGLETON_INSTANCE(Lib::DX11Manager).GetDeviceContext(),
		SINGLETON_INSTANCE(Lib::Window).GetWindowSize());
	_pJudgeVertex->pVertex->Init(_rect, _pJudgeVertex->pUvController->GetUV());
	_pJudgeVertex->pVertex->SetTexture(
		SINGLETON_INSTANCE(Lib::TextureManager).GetTexture(m_TextureIndex));
	_pJudgeVertex->Pos = *_pos;
	_pJudgeVertex->Rect = *_rect;
}

void JudgeGaugeUI::ReleaseJudgeVertex(JudgeGaugeUI::JudgeVertex* _pJudgeVertex)
{
	if (_pJudgeVertex->pVertex != NULL)
	{
		_pJudgeVertex->pVertex->Release();
		delete _pJudgeVertex->pVertex;
		_pJudgeVertex->pVertex = NULL;
	}

	delete _pJudgeVertex->pUvController;
	_pJudgeVertex->pUvController = NULL;
}
