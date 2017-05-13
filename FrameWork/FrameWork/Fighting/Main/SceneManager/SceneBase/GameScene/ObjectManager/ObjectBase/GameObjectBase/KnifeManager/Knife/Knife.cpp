/**
 * @file   Knife.cpp
 * @brief  Knifeクラスの実装
 * @author kotani
 */
#include "Window/Window.h"
#include "Window/Window.h"
#include "Dx11/DX11Manager.h"
#include "Animation/AnimUvController.h"
#include "Texture/TextureManager.h"
#include "Knife.h"
#include "../../../../../CollisionManager/CollisionManager.h"
#include "../../../../../GameDataManager/GameDataManager.h"

const D3DXVECTOR2 Knife::m_Rect = D3DXVECTOR2(128, 256);
int	Knife::m_IndexMax = 0;


Knife::Knife(int _textureIndex, Lib::AnimUvController* _pUvController) :
m_IsThrow(false),
m_IsCatch(false),
m_pUvController(_pUvController),
m_TextureIndex(_textureIndex),
m_RectCollisionRatio(0.6f)
{
	m_Index = m_IndexMax;
	m_IndexMax++;
	m_pCollisionData = new CollisionData();
	m_pCollisionData->SetEnable(false);
	m_pCollisionData->SetCollision(&m_Pos, &m_Rect, CollisionData::ENEMY_KNIFE_TYPE);
	SINGLETON_INSTANCE(CollisionManager).AddCollision(m_pCollisionData);

	m_pVertex = new Lib::Vertex2D(
		SINGLETON_INSTANCE(Lib::DX11Manager).GetDevice(),
		SINGLETON_INSTANCE(Lib::DX11Manager).GetDeviceContext(),
		SINGLETON_INSTANCE(Lib::Window).GetWindowHandle());
	m_pVertex->Init(&m_Rect, m_pUvController->GetUV());
	m_pVertex->SetTexture(
		SINGLETON_INSTANCE(Lib::TextureManager).GetTexture(m_TextureIndex));
}

Knife::~Knife()
{
	m_pVertex->Release();
	delete m_pVertex;

	delete m_pCollisionData;
	m_pCollisionData = NULL;
}

void Knife::Update()
{
	if (!m_IsThrow) return;
	CollisionData::HIT_STATE hitState = m_pCollisionData->GetCollisionState().HitState;
	m_IsCatch;
	if (!m_IsCatch)
	{
		m_Pos.x += m_Velocity * -cos(m_Angle);
		m_Pos.y -= m_Velocity * sin(m_Angle);
		m_Scale += m_ScaleAddValue;
		m_TargetDistance -= m_Velocity;
	}

	if (m_TargetDistance <= 0 && m_Target != PLAYER)
	{
		m_pCollisionData->SetEnable(false);
		m_IsThrow = false;
	}
	else
	{
		m_pCollisionData->SetEnable(true);
	}

	if (m_Target != PLAYER)
	{
		m_pCollisionData->SetCollision(&m_Pos, &D3DXVECTOR2((m_Rect.x * m_Scale) * m_RectCollisionRatio,
			(m_Rect.y * m_Scale) * m_RectCollisionRatio), CollisionData::PLAYER_KNIFE_TYPE);
	}
	else
	{
		m_pCollisionData->SetCollision(&m_Pos, &D3DXVECTOR2((m_Rect.x * m_Scale) * m_RectCollisionRatio,
			(m_Rect.y * m_Scale) * m_RectCollisionRatio), CollisionData::ENEMY_KNIFE_TYPE);
	}

	if (hitState == CollisionData::CATCH_HIT)
	{
		SINGLETON_INSTANCE(GameDataManager).SetKnifeBarIsEnable(m_Index, false);
		m_IsCatch = true;
	}
	else if (hitState == CollisionData::KNIFE_HIT)
	{
		SINGLETON_INSTANCE(GameDataManager).SetKnifeBarIsEnable(m_Index, false);
		m_pCollisionData->SetEnable(false);
		m_IsThrow = false;
	}
	else if (m_OldHitState == CollisionData::CATCH_HIT &&
		hitState == CollisionData::NON_HIT)
	{
		m_IsCatch = false;
	}
	m_OldHitState = hitState;
}

void Knife::Draw()
{
	if (!m_IsThrow) return;
	m_pVertex->Draw(&m_Pos, m_pUvController->GetUV(), 1.f, &D3DXVECTOR2(m_Scale, m_Scale));
}

void Knife::Throw(D3DXVECTOR2* _pos, TARGET _target, float _velocity)
{
	m_pCollisionData->SetEnable(true);
	m_OldHitState = CollisionData::NON_HIT;
	m_Pos = *_pos;
	m_IsThrow = true;
	m_IsCatch = false;
	m_Velocity = _velocity;
	m_Target = _target;

	RECT ClientRect;
	GetClientRect(SINGLETON_INSTANCE(Lib::Window).GetWindowHandle(), &ClientRect);

	D3DXVECTOR2 playerPos;
	playerPos.x = static_cast<float>(ClientRect.right / 2);
	playerPos.y = static_cast<float>(ClientRect.bottom / 2 + 200);

	D3DXVECTOR2 leftEnemyPos;
	leftEnemyPos.x = static_cast<float>(ClientRect.right / 2 - 150);
	leftEnemyPos.y = 200.f;

	D3DXVECTOR2 frontEnemyPos;
	frontEnemyPos.x = static_cast<float>(ClientRect.right / 2);
	frontEnemyPos.y = 200.f;

	D3DXVECTOR2 rightEnemyPos;
	rightEnemyPos.x = static_cast<float>(ClientRect.right / 2 + 150);
	rightEnemyPos.y = 200.f;
	switch (m_Target)
	{
	case LEFT_ENEMY:
		m_Angle = atan2(_pos->y - leftEnemyPos.y, _pos->x - leftEnemyPos.x);
		m_TargetDistance = sqrt(pow(_pos->x - leftEnemyPos.x, 2) + pow(_pos->y - leftEnemyPos.y, 2));
		break;
	case FRONT_ENEMY:
		m_Angle = atan2(_pos->y - frontEnemyPos.y, _pos->x - frontEnemyPos.x);
		m_TargetDistance = sqrt(pow(_pos->x - frontEnemyPos.x, 2) + pow(_pos->y - frontEnemyPos.y, 2));
		break;
	case RIGHT_ENEMY:
		m_Angle = atan2(_pos->y - rightEnemyPos.y, _pos->x - rightEnemyPos.x);
		m_TargetDistance = sqrt(pow(_pos->x - rightEnemyPos.x, 2) + pow(_pos->y - rightEnemyPos.y, 2));
		break;
	case PLAYER:
		m_Angle = atan2(_pos->y - playerPos.y, _pos->x - playerPos.x);
		m_TargetDistance = sqrt(pow(_pos->x - playerPos.x, 2) + pow(_pos->y - playerPos.y, 2));
		break;
	}

	m_ArriveFrame = static_cast<int>(m_TargetDistance / m_Velocity);
	if (m_Target != PLAYER)
	{
		m_pCollisionData->SetCollision(&m_Pos, &D3DXVECTOR2((m_Rect.x * m_Scale) * m_RectCollisionRatio,
			(m_Rect.y * m_Scale) * m_RectCollisionRatio), CollisionData::PLAYER_KNIFE_TYPE);
		m_ScaleAddValue = -((0.5f) / m_ArriveFrame);
	}
	else
	{
		SINGLETON_INSTANCE(GameDataManager).SetKnifeDistance(m_TargetDistance, m_Velocity, m_Index);
		m_Scale = 0.3f;
		m_pCollisionData->SetCollision(&m_Pos, &D3DXVECTOR2((m_Rect.x * m_Scale) * m_RectCollisionRatio,
			(m_Rect.y * m_Scale) * m_RectCollisionRatio), CollisionData::ENEMY_KNIFE_TYPE);
		m_ScaleAddValue = (1.f - m_Scale) / m_ArriveFrame;
	}
}

void Knife::Throw(TARGET _target, float _velocity)
{
	Throw(&m_Pos, _target, _velocity);
}
