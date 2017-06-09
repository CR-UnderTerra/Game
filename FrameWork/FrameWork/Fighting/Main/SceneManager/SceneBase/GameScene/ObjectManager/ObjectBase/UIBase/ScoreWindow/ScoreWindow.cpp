/**
 * @file   ScoreWindow.cpp
 * @brief  ScoreWindowクラスの実装
 * @author kotani
 */
#include "ScoreWindow.h"
#include "ScoreBase/GoodText/GoodText.h"
#include "ScoreBase/AmazingText/AmazingText.h"
#include "ScoreBase/FantasticText/FantasticText.h"


ScoreWindow::ScoreWindow(int _textureIndex)
{
	m_Pos = D3DXVECTOR2(120,500);
	m_pScoreBase[0] = new GoodText(_textureIndex, &D3DXVECTOR2(m_Pos.x, m_Pos.y + 124.f));
	m_pScoreBase[1] = new AmazingText(_textureIndex, &D3DXVECTOR2(m_Pos.x, m_Pos.y));
	m_pScoreBase[2] = new FantasticText(_textureIndex, &D3DXVECTOR2(m_Pos.x, m_Pos.y - 124.f));
}

ScoreWindow::~ScoreWindow()
{
	for (int i = m_pScoreBase.size() - 1; i >= 0; i--)
	{
		delete m_pScoreBase[i];
		m_pScoreBase[i] = NULL;
	}
}


//----------------------------------------------------------------------------------------------------
// Public Functions
//----------------------------------------------------------------------------------------------------

void ScoreWindow::Update()
{
	for (unsigned int i = 0; i < m_pScoreBase.size(); i++)
	{
		m_pScoreBase[i]->Update();
	}
}

void ScoreWindow::Draw()
{
	for (unsigned int i = 0; i < m_pScoreBase.size(); i++)
	{
		m_pScoreBase[i]->Draw();
	}
}
