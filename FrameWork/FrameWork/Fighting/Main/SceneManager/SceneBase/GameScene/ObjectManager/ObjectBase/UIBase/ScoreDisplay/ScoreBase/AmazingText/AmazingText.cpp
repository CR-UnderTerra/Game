/**
 * @file   AmazingText.cpp
 * @brief  AmazingTextクラスの実装
 * @author kotani
 */
#include "AmazingText.h"
#include "Dx11/DX11Manager.h"
#include "Texture/TextureManager.h"
#include "Window/Window.h"
#include "../../../../../../../GameDataManager/GameDataManager.h"


AmazingText::AmazingText(int _textureIndex, D3DXVECTOR2* _pos) :
ScoreBase(_pos, "e_ama", _textureIndex)
{
}

AmazingText::~AmazingText()
{
}


//----------------------------------------------------------------------------------------------------
// Public Functions
//----------------------------------------------------------------------------------------------------

void AmazingText::Update()
{
	int amazingCount = SINGLETON_INSTANCE(GameDataManager).GetResult().AmazingCount;
	m_NumVertex[0].pUvController->SetAnimCount((amazingCount / 10) % 10);
	m_NumVertex[1].pUvController->SetAnimCount(amazingCount % 10);
}
