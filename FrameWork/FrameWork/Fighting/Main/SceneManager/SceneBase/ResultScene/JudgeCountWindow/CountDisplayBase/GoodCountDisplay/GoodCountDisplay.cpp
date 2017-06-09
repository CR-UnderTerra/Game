/**
 * @file   GoodCountDisplay.cpp
 * @brief  GoodCountDisplayクラスの実装
 * @author kotani
 */
#include "GoodCountDisplay.h"
#include "Dx11/DX11Manager.h"
#include "Texture/TextureManager.h"
#include "Window/Window.h"

GoodCountDisplay::GoodCountDisplay(int _textureIndex, D3DXVECTOR2* _pos) :
CountDisplayBase(_pos,"e_good",_textureIndex)
{
	int goodCount = SINGLETON_INSTANCE(GameDataManager).GetResult().GoodCount;
	m_NumVertex[0].pUvController->SetAnimCount((goodCount / 10) % 10);
	m_NumVertex[1].pUvController->SetAnimCount(goodCount % 10);
}

GoodCountDisplay::~GoodCountDisplay()
{
}


//----------------------------------------------------------------------------------------------------
// Public Functions
//----------------------------------------------------------------------------------------------------

bool GoodCountDisplay::Update()
{
	return false;
}
