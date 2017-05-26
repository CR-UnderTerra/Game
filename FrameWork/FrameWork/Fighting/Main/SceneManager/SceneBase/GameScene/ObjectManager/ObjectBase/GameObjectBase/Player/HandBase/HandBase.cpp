/**
 * @file   HandBase.cpp
 * @brief  HandBaseクラスの実装
 * @author kotani
 */
#include "HandBase.h"
#include "Texture/TextureManager.h"
#include "Window/Window.h"
#include "Dx11/DX11Manager.h"

const D3DXVECTOR2 HandBase::m_Rect = D3DXVECTOR2(192, 384);
const float HandBase::m_Acceleration = 1.f;


HandBase::HandBase(D3DXVECTOR2* _playerTopPos, LPCTSTR _animName, int _textureIndex) :
m_PlayerTopPos(*_playerTopPos),
m_TextureIndex(_textureIndex)
{
	m_pAnimUvController = new Lib::AnimUvController();
	m_pAnimUvController->LoadAnimation("Resource/test_001.anim", _animName);

	m_pVertex = new Lib::Vertex2D(
		SINGLETON_INSTANCE(Lib::DX11Manager).GetDevice(),
		SINGLETON_INSTANCE(Lib::DX11Manager).GetDeviceContext(),
		SINGLETON_INSTANCE(Lib::Window).GetWindowHandle());
	m_pVertex->Init(&m_Rect, m_pAnimUvController->GetUV());
	m_pVertex->SetTexture(
		SINGLETON_INSTANCE(Lib::TextureManager).GetTexture(m_TextureIndex));

	m_pCollisionData = new CollisionData();
	m_pCollisionData->SetCollision(&D3DXVECTOR3(m_Pos), &D3DXVECTOR2(m_Rect.x, m_Rect.y), CollisionData::PLAYER_TYPE);
	m_pCollisionData->SetEnable(true);
	SINGLETON_INSTANCE(CollisionManager).AddCollision(m_pCollisionData);

}


HandBase::~HandBase()
{
	delete m_pCollisionData;
	m_pCollisionData = NULL;

	if (m_pVertex != NULL)
	{
		m_pVertex->Release();
		delete m_pVertex;
		m_pVertex = NULL;
	}

	delete m_pAnimUvController;
	m_pAnimUvController = NULL;
}
