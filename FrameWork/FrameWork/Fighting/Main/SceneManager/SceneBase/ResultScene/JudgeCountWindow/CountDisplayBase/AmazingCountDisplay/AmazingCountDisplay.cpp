/**
 * @file   AmazingCountDisplay.cpp
 * @brief  AmazingCountDisplayクラスの実装
 * @author kotani
 */
#include "AmazingCountDisplay.h"
#include "Dx11/DX11Manager.h"
#include "Texture/TextureManager.h"
#include "Window/Window.h"

AmazingCountDisplay::AmazingCountDisplay(int _textureIndex, D3DXVECTOR2* _pos) :
CountDisplayBase(_pos, "e_ama", _textureIndex)
{
	int amazingCount = SINGLETON_INSTANCE(GameDataManager).GetResult().AmazingCount;
	m_NumVertex[0].pUvController->SetAnimCount((amazingCount / 10) % 10);
	m_NumVertex[1].pUvController->SetAnimCount(amazingCount % 10);
}

AmazingCountDisplay::~AmazingCountDisplay()
{
}


//----------------------------------------------------------------------------------------------------
// Public Functions
//----------------------------------------------------------------------------------------------------

bool AmazingCountDisplay::Update()
{
	return false;
}
