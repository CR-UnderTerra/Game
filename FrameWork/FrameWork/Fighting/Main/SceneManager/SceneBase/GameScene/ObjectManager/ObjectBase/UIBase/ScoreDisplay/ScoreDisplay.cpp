/**
 * @file   ScoreDisplay.cpp
 * @brief  ScoreDisplayクラスの実装
 * @author kotani
 */
#include "ScoreDisplay.h"
#include "GoodText/GoodText.h"
#include "AmazingText/AmazingText.h"
#include "FantasticText/FantasticText.h"


ScoreDisplay::ScoreDisplay(int _textureIndex)
{
	m_Pos = D3DXVECTOR2(100,600);
	m_pGoodText = new GoodText(_textureIndex, &D3DXVECTOR2(m_Pos.x, m_Pos.y - 84.f));
	m_pAmazingText = new AmazingText(_textureIndex, &D3DXVECTOR2(m_Pos.x, m_Pos.y));
	m_pFantasticText = new FantasticText(_textureIndex, &D3DXVECTOR2(m_Pos.x, m_Pos.y + 84.f));
}

ScoreDisplay::~ScoreDisplay()
{
	delete m_pFantasticText;
	m_pFantasticText = NULL;

	delete m_pAmazingText;
	m_pAmazingText = NULL;

	delete m_pGoodText;
	m_pGoodText = NULL;
}


//----------------------------------------------------------------------------------------------------
// Public Functions
//----------------------------------------------------------------------------------------------------

void ScoreDisplay::Update()
{
	m_pGoodText->Update();
	m_pFantasticText->Update();
	m_pAmazingText->Update();
}

void ScoreDisplay::Draw()
{
	m_pGoodText->Draw();
	m_pFantasticText->Draw();
	m_pAmazingText->Draw();
}
