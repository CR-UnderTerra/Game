/**
 * @file   JudgeCountWindow.cpp
 * @brief  JudgeCountWindowクラスの実装
 * @author kotani
 */
#include "JudgeCountWindow.h"
#include "CountDisplayBase/GoodCountDisplay/GoodCountDisplay.h"
#include "CountDisplayBase/AmazingCountDisplay/AmazingCountDisplay.h"
#include "CountDisplayBase/FantasticCountDisplay/FantasticCountDisplay.h"
#include "../ResultScene.h"
#include "Helper/Helper.h"

const float JudgeCountWindow::m_DisplayTime = 2.f;


JudgeCountWindow::JudgeCountWindow(int _textureIndex) :
	m_Alpha(0)
{
	m_Pos = D3DXVECTOR2(1150, 600);
	m_pCountDisplayBase[0] = new GoodCountDisplay(_textureIndex, &D3DXVECTOR2(m_Pos.x, m_Pos.y + 70.f));
	m_pCountDisplayBase[1] = new AmazingCountDisplay(_textureIndex, &D3DXVECTOR2(m_Pos.x, m_Pos.y));
	m_pCountDisplayBase[2] = new FantasticCountDisplay(_textureIndex, &D3DXVECTOR2(m_Pos.x, m_Pos.y - 70.f));
	m_AddAlphaValue = 1.f / (m_DisplayTime * 60);
}

JudgeCountWindow::~JudgeCountWindow()
{
	for (int i = m_pCountDisplayBase.size() - 1; i >= 0; i--)
	{
		Lib::SafeDelete(m_pCountDisplayBase[i]);
	}
}


//----------------------------------------------------------------------------------------------------
// Public Functions
//----------------------------------------------------------------------------------------------------
bool JudgeCountWindow::Update()
{
	for (unsigned int i = 0; i < m_pCountDisplayBase.size(); i++)
	{
		m_pCountDisplayBase[i]->Update();
	}
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

void JudgeCountWindow::Draw()
{
	for (unsigned int i = 0; i < m_pCountDisplayBase.size(); i++)
	{
		m_pCountDisplayBase[i]->Draw(m_Alpha);
	}
}
