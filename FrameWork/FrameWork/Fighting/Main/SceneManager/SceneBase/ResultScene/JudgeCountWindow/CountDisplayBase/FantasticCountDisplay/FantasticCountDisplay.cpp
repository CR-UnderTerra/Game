/**
 * @file   FantasticCountDisplay.cpp
 * @brief  FantasticCountDisplayクラスの実装
 * @author kotani
 */
#include "FantasticCountDisplay.h"
#include "Dx11/DX11Manager.h"
#include "Texture/TextureManager.h"
#include "Window/Window.h"

FantasticCountDisplay::FantasticCountDisplay(int _textureIndex, D3DXVECTOR2* _pos) :
CountDisplayBase(_pos, "e_fan", _textureIndex)
{
	int fantasticCount = SINGLETON_INSTANCE(GameDataManager).GetResult().FantasticCount;
	m_NumVertex[0].pUvController->SetAnimCount((fantasticCount / 10) % 10);
	m_NumVertex[1].pUvController->SetAnimCount(fantasticCount % 10);
}

FantasticCountDisplay::~FantasticCountDisplay()
{
}


//----------------------------------------------------------------------------------------------------
// Public Functions
//----------------------------------------------------------------------------------------------------

bool FantasticCountDisplay::Update()
{
	return false;
}
