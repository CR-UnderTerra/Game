/**
 * @file   BackGround.cpp
 * @brief  BackGroundクラスの実装
 * @author kotani
 */
#include "BackGround.h"
#include "Texture/TextureManager.h"
#include "Window/Window.h"
#include "Dx11/DX11Manager.h"
#include "Helper/Helper.h"

const D3DXVECTOR2 BackGround::m_Rect = D3DXVECTOR2(1350, 1080);


BackGround::BackGround(int _textureIndex) :
m_TextureIndex(_textureIndex)
{
	SINGLETON_INSTANCE(Lib::TextureManager).Load("Resource/test_009.png", &m_TextureIndex);
	SINGLETON_INSTANCE(Lib::TextureManager).Load("Resource/test_010.png", &m_TextureIndex);
	SINGLETON_INSTANCE(Lib::TextureManager).Load("Resource/test_011.png", &m_TextureIndex);
	SINGLETON_INSTANCE(Lib::TextureManager).Load("Resource/test_003.png", &m_TextureIndex);

	RECT ClientRect = SINGLETON_INSTANCE(Lib::Window).GetWindowSize();
	m_Pos = D3DXVECTOR2(static_cast<float>(ClientRect.right / 2), static_cast<float>(ClientRect.bottom / 2));
	m_pAnimUvController = new Lib::AnimUvController();
	m_pAnimUvController->LoadAnimation("Resource/test_003.anim", "bg01");

	m_pVertex = new Lib::Vertex2D(
		SINGLETON_INSTANCE(Lib::DX11Manager).GetDevice(),
		SINGLETON_INSTANCE(Lib::DX11Manager).GetDeviceContext(),
		SINGLETON_INSTANCE(Lib::Window).GetWindowSize());
	m_pVertex->Init(&m_Rect, m_pAnimUvController->GetUV());
	m_pVertex->SetTexture(
		SINGLETON_INSTANCE(Lib::TextureManager).GetTexture(m_TextureIndex));

}

BackGround::~BackGround()
{
	if (m_pVertex != NULL)
	{
		m_pVertex->Release();
		Lib::SafeDelete(m_pVertex);
	}
	
	Lib::SafeDelete(m_pAnimUvController);
}


//----------------------------------------------------------------------------------------------------
// Public Functions
//----------------------------------------------------------------------------------------------------

void BackGround::Update()
{
}

void BackGround::Draw()
{
	m_pVertex->Draw(&m_Pos, m_pAnimUvController->GetUV());
}
