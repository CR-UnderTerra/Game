/**
 * @file   DistanceGaugeUI.cpp
 * @brief  DistanceGaugeUIクラスの実装
 * @author kotani
 */
#include "DistanceGaugeUI.h"
#include "Texture/TextureManager.h"
#include "Window/Window.h"
#include "Dx11/DX11Manager.h"
#include "../../../../GameDataManager/GameDataManager.h"
#include "../../GameObjectBase/KnifeManager/KnifeManager.h"
#include "KnifeBar/KnifeBar.h"
#include "JudgeGaugeUI/JudgeGaugeUI.h"

const D3DXVECTOR2 DistanceGaugeUI::m_Rect = D3DXVECTOR2(64,500);


DistanceGaugeUI::DistanceGaugeUI(int _textureIndex) :
m_TextureIndex(_textureIndex)
{
	m_pUvController = new Lib::AnimUvController();
	m_pUvController->LoadAnimation("Resource/test_001.anim", "d_meter");
	m_Pos = D3DXVECTOR2(1180,400);
	m_pVertex = new Lib::Vertex2D(
		SINGLETON_INSTANCE(Lib::DX11Manager).GetDevice(),
		SINGLETON_INSTANCE(Lib::DX11Manager).GetDeviceContext(),
		SINGLETON_INSTANCE(Lib::Window).GetWindowHandle());
	m_pVertex->Init(&m_Rect, m_pUvController->GetUV());
	m_pVertex->SetTexture(
		SINGLETON_INSTANCE(Lib::TextureManager).GetTexture(m_TextureIndex));

	for (int i = 0; i < KnifeManager::m_KnifeMax; i++)
	{
		m_pKnifeBar.push_back(new KnifeBar(m_TextureIndex, &D3DXVECTOR2(m_Pos.x, m_Pos.y - m_Rect.y / 2)));
	}
	m_pJudgeGaugeUI = new JudgeGaugeUI(m_TextureIndex, &D3DXVECTOR2(m_Pos.x, m_Pos.y + m_Rect.y / 2));
	SINGLETON_INSTANCE(GameDataManager).SetDistanceGaugeUI(this);
}

DistanceGaugeUI::~DistanceGaugeUI()
{
	delete m_pJudgeGaugeUI;
	m_pJudgeGaugeUI = NULL;

	for (int i = KnifeManager::m_KnifeMax - 1; i >= 0; i--)
	{
		delete m_pKnifeBar[i];
		m_pKnifeBar[i] = NULL;
	}

	if (m_pVertex != NULL)
	{
		m_pVertex->Release();
		delete m_pVertex;
		m_pVertex = NULL;
	}

	delete m_pUvController;
	m_pUvController = NULL;
}


//----------------------------------------------------------------------------------------------------
// Public Functions
//----------------------------------------------------------------------------------------------------

void DistanceGaugeUI::Update()
{
	for (int i = 0; i < KnifeManager::m_KnifeMax; i++)
	{
		m_pKnifeBar[i]->Update();
	}
	m_pJudgeGaugeUI->Update();
}

void DistanceGaugeUI::Draw()
{
	m_pVertex->Draw(&m_Pos,m_pUvController->GetUV());
	for (int i = 0; i < KnifeManager::m_KnifeMax; i++)
	{
		m_pKnifeBar[i]->Draw();
	}
	m_pJudgeGaugeUI->Draw();
}
void DistanceGaugeUI::SetKnifeBar(float _distance, float _velocity, int _index)
{
	m_pKnifeBar[_index]->SetKnifeState(_distance, _velocity);
	m_pKnifeBar[_index]->SetIsEnable(true);
}

void DistanceGaugeUI::SetKnifeBarIsEnable(int _index, bool _IsEnable)
{
	m_pKnifeBar[_index]->SetIsEnable(_IsEnable);
}


JudgeGaugeUI::JUDGE DistanceGaugeUI::KnifeJadge(int _index)
{
	return m_pJudgeGaugeUI->Judge(m_pKnifeBar[_index]->GetPos());
}
