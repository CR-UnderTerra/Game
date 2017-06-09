/**
 * @file   GoodText.cpp
 * @brief  GoodTextクラスの実装
 * @author kotani
 */
#include "GoodText.h"
#include "Dx11/DX11Manager.h"
#include "Texture/TextureManager.h"
#include "Window/Window.h"
#include "../../../../../../../GameDataManager/GameDataManager.h"


GoodText::GoodText(int _textureIndex,D3DXVECTOR2* _pos) :
ScoreBase(_pos,"e_good",_textureIndex)
{
}

GoodText::~GoodText()
{
}


//----------------------------------------------------------------------------------------------------
// Public Functions
//----------------------------------------------------------------------------------------------------

void GoodText::Update()
{
	int goodCount = SINGLETON_INSTANCE(GameDataManager).GetResult().GoodCount;
	m_NumVertex[0].pUvController->SetAnimCount((goodCount / 10) % 10);
	m_NumVertex[1].pUvController->SetAnimCount(goodCount % 10);
}
