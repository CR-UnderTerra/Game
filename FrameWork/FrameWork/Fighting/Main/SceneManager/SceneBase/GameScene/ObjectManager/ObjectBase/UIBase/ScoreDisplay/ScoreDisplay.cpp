/**
 * @file   ScoreDisplay.cpp
 * @brief  ScoreDisplayクラスの実装
 * @author kotani
 */
#include "ScoreDisplay.h"
#include "ScoreBase/GoodText/GoodText.h"
#include "ScoreBase/AmazingText/AmazingText.h"
#include "ScoreBase/FantasticText/FantasticText.h"


ScoreDisplay::ScoreDisplay(int _textureIndex)
{
	m_Pos = D3DXVECTOR2(100,600);
	m_pScoreBase[0] = new GoodText(_textureIndex, &D3DXVECTOR2(m_Pos.x, m_Pos.y - 104.f));
	m_pScoreBase[1] = new AmazingText(_textureIndex, &D3DXVECTOR2(m_Pos.x, m_Pos.y));
	m_pScoreBase[2] = new FantasticText(_textureIndex, &D3DXVECTOR2(m_Pos.x, m_Pos.y + 104.f));
}

ScoreDisplay::~ScoreDisplay()
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

void ScoreDisplay::Update()
{
	for (unsigned int i = 0; i < m_pScoreBase.size(); i++)
	{
		m_pScoreBase[i]->Update();
	}
}

void ScoreDisplay::Draw()
{
	for (unsigned int i = 0; i < m_pScoreBase.size(); i++)
	{
		m_pScoreBase[i]->Draw();
	}
}
