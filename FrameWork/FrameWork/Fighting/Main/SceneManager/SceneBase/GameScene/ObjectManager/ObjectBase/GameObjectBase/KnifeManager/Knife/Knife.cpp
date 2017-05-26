﻿/**
 * @file   Knife.cpp
 * @brief  Knifeクラスの実装
 * @author kotani
 */
#include "Window/Window.h"
#include "Dx11/DX11Manager.h"
#include "Animation/AnimUvController.h"
#include "Texture/TextureManager.h"
#include "Knife.h"
#include "../../../UIBase/DistanceGaugeUI/JudgeGaugeUI/JudgeGaugeUI.h"
#include "../../../../../CollisionManager/CollisionManager.h"

const D3DXVECTOR2 Knife::m_Rect = D3DXVECTOR2(192, 384);
int	Knife::m_IndexMax = 0;


Knife::Knife(int _textureIndex) :
m_IsThrow(false),
m_IsCatch(false),
m_TextureIndex(_textureIndex),
m_RectCollisionRatio(D3DXVECTOR2(0.3f,0.3f))
{
	m_Index = m_IndexMax;
	m_IndexMax++;
	m_pCollisionData = new CollisionData();
	m_pCollisionData->SetEnable(false);
	m_pCollisionData->SetCollision(&D3DXVECTOR3(m_Pos.x, m_Pos.y, m_TargetDistance), &m_Rect, CollisionData::ENEMY_KNIFE_TYPE);
	SINGLETON_INSTANCE(CollisionManager).AddCollision(m_pCollisionData);

	m_pVertex = new Lib::Vertex2D(
		SINGLETON_INSTANCE(Lib::DX11Manager).GetDevice(),
		SINGLETON_INSTANCE(Lib::DX11Manager).GetDeviceContext(),
		SINGLETON_INSTANCE(Lib::Window).GetWindowHandle());
	D3DXVECTOR2 uv[4];
	for (int i = 0; i < 4; i++)
	{
		uv[i].x = 0.f;
		uv[i].y = 0.f;
	}
	m_pVertex->Init(&m_Rect, uv);
	m_pVertex->SetTexture(
		SINGLETON_INSTANCE(Lib::TextureManager).GetTexture(m_TextureIndex));
}

Knife::~Knife()
{
	m_pVertex->Release();
	delete m_pVertex;
	m_pVertex = NULL;

	delete m_pCollisionData;
	m_pCollisionData = NULL;
	m_IndexMax = 0;
}


//----------------------------------------------------------------------------------------------------
// Public Functions
//----------------------------------------------------------------------------------------------------

void Knife::Update()
{
	if (!m_IsThrow) return;
	if (!m_IsCatch)
	{
		m_Pos.x += m_Velocity * -cos(m_Angle);
		m_Pos.y -= m_Velocity * sin(m_Angle);
		m_Scale += m_ScaleAddValue;
		m_TargetDistance -= m_Velocity;
	}
	CollisionUpdate();
	CollisionControl();
}

void Knife::Draw()
{
	if (!m_IsThrow) return;
	m_pVertex->Draw(&m_Pos, m_pThrowUv->GetUV(), 1.f, &D3DXVECTOR2(m_Scale, m_Scale));
}

void Knife::Throw(D3DXVECTOR2* _pos, GameDataManager::TARGET _target, float _arriveTime, Lib::AnimUvController* _pThrowUv)
{
	m_pCollisionData->SetEnable(true);
	m_Pos = *_pos;
	m_IsThrow = true;
	m_IsCatch = false;
	m_Velocity = 0;
	m_pThrowUv = _pThrowUv;
	m_ArriveFrame = static_cast<int>(_arriveTime * 60);
	m_Target = _target;
	m_CatchState = JudgeGaugeUI::FAILED_JUDGE;
	RECT ClientRect;
	GetClientRect(SINGLETON_INSTANCE(Lib::Window).GetWindowHandle(), &ClientRect);

	D3DXVECTOR2 pos = SINGLETON_INSTANCE(GameDataManager).GetPos(m_Target);
	m_Angle = atan2(_pos->y - pos.y, _pos->x - pos.x);
	m_TargetDistance = sqrt(pow(_pos->x - pos.x, 2) + pow(_pos->y - pos.y, 2));

	m_Velocity = m_TargetDistance / m_ArriveFrame;
	if (m_Target != GameDataManager::PLAYER_TARGET)
	{
		m_pCollisionData->SetCollision(&D3DXVECTOR3(m_Pos.x, m_Pos.y, m_TargetDistance), &D3DXVECTOR2((m_Rect.x * m_Scale) * m_RectCollisionRatio.x,
			(m_Rect.y * m_Scale) * m_RectCollisionRatio.y), CollisionData::PLAYER_KNIFE_TYPE);
		m_ScaleAddValue = -((0.5f) / m_ArriveFrame);
	}
	else
	{
		SINGLETON_INSTANCE(GameDataManager).SetKnifeDistance(m_TargetDistance, m_Velocity, m_Index);
		m_Scale = 0.1f;
		m_pCollisionData->SetCollision(&D3DXVECTOR3(m_Pos.x, m_Pos.y, m_TargetDistance), &D3DXVECTOR2((m_Rect.x * m_Scale) * m_RectCollisionRatio.x,
			(m_Rect.y * m_Scale) * m_RectCollisionRatio.y), CollisionData::ENEMY_KNIFE_TYPE);
		m_ScaleAddValue = (1.f - m_Scale) / m_ArriveFrame;
	}
}

void Knife::Throw(GameDataManager::TARGET _target, float _arriveTime, Lib::AnimUvController* _pThrowUv)
{
	Throw(&m_Pos, _target, _arriveTime, _pThrowUv);
}


//----------------------------------------------------------------------------------------------------
// Private Functions
//----------------------------------------------------------------------------------------------------

void Knife::CollisionUpdate()
{
	if (m_Target == GameDataManager::PLAYER_TARGET)
	{
		if (m_TargetDistance <= 0)
		{
			int playerHp = SINGLETON_INSTANCE(GameDataManager).GetPlayerHp();
			SINGLETON_INSTANCE(GameDataManager).SetPlayerHp(--playerHp);
			SINGLETON_INSTANCE(GameDataManager).SetKnifeBarIsEnable(m_Index, false);
			m_pCollisionData->SetEnable(false);
			m_IsThrow = false;
		}
		else
		{
			m_pCollisionData->SetEnable(true);
		}
		m_pCollisionData->SetCollision(&D3DXVECTOR3(m_Pos.x, m_Pos.y, m_TargetDistance), &D3DXVECTOR2((m_Rect.x * m_Scale) * m_RectCollisionRatio.x,
			(m_Rect.y * m_Scale) * m_RectCollisionRatio.y), CollisionData::ENEMY_KNIFE_TYPE);
	}
	else
	{
		if (m_TargetDistance <= 0)
		{
			m_pCollisionData->SetEnable(false);
			m_IsThrow = false;
		}
		else
		{
			m_pCollisionData->SetEnable(true);
		}
		m_pCollisionData->SetCollision(&D3DXVECTOR3(m_Pos.x, m_Pos.y, m_TargetDistance), &D3DXVECTOR2((m_Rect.x * m_Scale) * m_RectCollisionRatio.x,
			(m_Rect.y * m_Scale) * m_RectCollisionRatio.y), CollisionData::PLAYER_KNIFE_TYPE);
	}
}

void Knife::CollisionControl()
{
	if (!m_IsCatch)
	{
		m_CatchState = SINGLETON_INSTANCE(GameDataManager).KnifeJadge(m_Index);
		if (m_CatchState != JudgeGaugeUI::FAILED_JUDGE)
		{
			m_pCollisionData->SetCatchEnable(true);
		}
		else
		{
			m_pCollisionData->SetCatchEnable(false);
		}
	}

	CollisionData::HIT_STATE hitState = m_pCollisionData->GetCollisionState().HitState;
	if (hitState == CollisionData::KNIFE_HIT)
	{
		SINGLETON_INSTANCE(GameDataManager).SetKnifeBarIsEnable(m_Index, false);
		m_pCollisionData->SetEnable(false);
		m_IsThrow = false;
		m_IsCatch = false;
	}
	else if (hitState == CollisionData::CATCH_HIT &&
		m_Target == GameDataManager::PLAYER_TARGET &&
		!m_IsCatch)
	{
		if (m_CatchState != JudgeGaugeUI::FAILED_JUDGE)
		{
			SINGLETON_INSTANCE(GameDataManager).SetKnifeBarIsEnable(m_Index, false);
			m_IsCatch = true;
		}
	}
}