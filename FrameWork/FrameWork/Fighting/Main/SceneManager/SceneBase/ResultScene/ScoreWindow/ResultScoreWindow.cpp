/**
 * @file   ScoreWindow.cpp
 * @brief  ScoreWindowクラスの実装
 * @author kotani
 */
#include "ResultScoreWindow.h"
#include "Texture/TextureManager.h"
#include "Window/Window.h"
#include "Dx11/DX11Manager.h"
#include "../ResultScene.h"
#include "../../GameDataManager/GameDataManager.h"


namespace Result
{
	const float ScoreWindow::m_DisplayTime = 2.f;
	const D3DXVECTOR2 ScoreWindow::m_Rect = D3DXVECTOR2(45 * 2,96 * 2);

	ScoreWindow::ScoreWindow() :
		m_Scale(0),
		m_Score(0)
	{
		SINGLETON_INSTANCE(Lib::TextureManager).Load("Resource/test_001.png", &m_TextureIndex);
		RECT ClientRect = SINGLETON_INSTANCE(Lib::Window).GetWindowSize();

		m_Pos = D3DXVECTOR2(static_cast<float>(ClientRect.right / 2), 350);

		float offsetPosX = (m_Rect.x * 2);
		for (int i = 0; i < 5; i++)
		{
			InitVertex(&D3DXVECTOR2(m_Pos.x + offsetPosX, m_Pos.y), &D3DXVECTOR2(m_Rect.x, m_Rect.y), "Number", &m_NumVertex[i]);
			offsetPosX -= m_Rect.x;
		}

		int minute = SINGLETON_INSTANCE(GameDataManager).GetResult().Minute;
		int second = SINGLETON_INSTANCE(GameDataManager).GetResult().Second;
		second = second + minute * 60;
		int goodCount = SINGLETON_INSTANCE(GameDataManager).GetResult().GoodCount;
		int amazingCount = SINGLETON_INSTANCE(GameDataManager).GetResult().AmazingCount;
		int fantasticCount = SINGLETON_INSTANCE(GameDataManager).GetResult().FantasticCount;
		int playerHp = SINGLETON_INSTANCE(GameDataManager).GetPlayerHp();

		m_Score = goodCount * 300;
		m_Score += amazingCount * 500;
		m_Score += fantasticCount * 1000;
		m_Score += playerHp * 500;
		m_Score -= second * 30;
		if (m_Score < 0)
		{
			m_Score = 0;
		}

		m_NumVertex[0].pUvController->SetAnimCount((m_Score) % 10);
		m_NumVertex[1].pUvController->SetAnimCount((m_Score / 10) % 10);
		m_NumVertex[2].pUvController->SetAnimCount((m_Score / 100) % 10);
		m_NumVertex[3].pUvController->SetAnimCount((m_Score / 1000) % 10);
		m_NumVertex[4].pUvController->SetAnimCount((m_Score / 10000) % 10);
		m_AddScaleValue = 1.f / (m_DisplayTime * 60);
	}

	ScoreWindow::~ScoreWindow()
	{
		ReleaseVertex(&m_NumVertex[4]);
		ReleaseVertex(&m_NumVertex[3]);
		ReleaseVertex(&m_NumVertex[2]);
		ReleaseVertex(&m_NumVertex[1]);
		ReleaseVertex(&m_NumVertex[0]);

		SINGLETON_INSTANCE(Lib::TextureManager).ReleaseTexture(m_TextureIndex);
	}


	//----------------------------------------------------------------------------------------------------
	// Public Functions
	//----------------------------------------------------------------------------------------------------

	bool ScoreWindow::Update()
	{
		m_Scale += m_AddScaleValue;
		if (m_Scale > 1.f)
		{
			m_Scale = 1.f;
			return true;
		}
		if (ResultScene::KeyCheck())
		{
			m_Scale = 1.f;
		}
		return false;
	}

	void ScoreWindow::Draw()
	{
		int digit = 0;
		int num = m_Score;
		while (num != 0)
		{
			num /= 10;
			digit++;
		}

		if (digit == 0)
		{
			m_NumVertex[0].pVertex->Draw(&m_NumVertex[0].Pos, m_NumVertex[0].pUvController->GetUV(), 1.f, &D3DXVECTOR2(m_Scale, m_Scale));
		}
		else
		{
			for (int i = digit - 1; i >= 0; i--)
			{
				m_NumVertex[i].pVertex->Draw(&m_NumVertex[i].Pos, m_NumVertex[i].pUvController->GetUV(), 1.f, &D3DXVECTOR2(m_Scale, m_Scale));
			}
		}
	}

	//----------------------------------------------------------------------------------------------------
	// Private Functions
	//----------------------------------------------------------------------------------------------------

	void ScoreWindow::InitVertex(D3DXVECTOR2* _pos, D3DXVECTOR2* _rect, LPCTSTR _animName, Vertex* _vertex)
	{
		_vertex->Pos = *_pos;
		_vertex->Rect = *_rect;
		_vertex->pUvController = new Lib::AnimUvController();
		_vertex->pUvController->LoadAnimation("Resource/test_001.anim", _animName);
		_vertex->pVertex = new Lib::Vertex2D(
			SINGLETON_INSTANCE(Lib::DX11Manager).GetDevice(),
			SINGLETON_INSTANCE(Lib::DX11Manager).GetDeviceContext(),
			SINGLETON_INSTANCE(Lib::Window).GetWindowSize());
		_vertex->pVertex->Init(&_vertex->Rect, _vertex->pUvController->GetUV());
		_vertex->pVertex->SetTexture(
			SINGLETON_INSTANCE(Lib::TextureManager).GetTexture(m_TextureIndex));
	}

	void ScoreWindow::ReleaseVertex(Vertex* _vertex)
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
}
