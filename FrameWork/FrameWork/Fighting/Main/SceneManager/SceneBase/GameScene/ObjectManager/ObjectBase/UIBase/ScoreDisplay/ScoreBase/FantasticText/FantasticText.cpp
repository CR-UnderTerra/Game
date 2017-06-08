/**
 * @file   FantasticText.cpp
 * @brief  FantasticTextクラスの実装
 * @author kotani
 */
#include "FantasticText.h"
#include "Dx11/DX11Manager.h"
#include "Texture/TextureManager.h"
#include "Window/Window.h"
#include "../../../../../../../GameDataManager/GameDataManager.h"


FantasticText::FantasticText(int _textureIndex,D3DXVECTOR2* _pos) :
ScoreBase(_pos,"e_fan",_textureIndex)
{
}

FantasticText::~FantasticText()
{
}


//----------------------------------------------------------------------------------------------------
// Public Functions
//----------------------------------------------------------------------------------------------------

void FantasticText::Update()
{
	int fantasticCount = SINGLETON_INSTANCE(GameDataManager).GetResult().FantasticCount;
	m_NumVertex[0].pUvController->SetAnimCount((fantasticCount / 10) % 10);
	m_NumVertex[1].pUvController->SetAnimCount(fantasticCount % 10);
}
