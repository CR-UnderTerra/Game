﻿/**
 * @file   HandBase.h
 * @brief  HandBaseクラスのヘッダファイル
 * @author kotani
 */
#ifndef HANDBASE_H
#define HANDBASE_H
#include "../../../GameObjectBase/GameObjectBase.h"
#include "Vertex2D/Vertex2D.h"
#include "Animation/AnimUvController.h"
#include "../../../../../CollisionManager/CollisionManager.h"
#include "../../../../../CollisionManager/CollisionData/CollisionData.h"

class HandBase : public GameObjectBase
{
public:
	HandBase(D3DXVECTOR2* _pos,LPCTSTR _animName,int _textureIndex);
	~HandBase();

	/**
	 * 制御関数
	 */
	virtual void Update() override = 0;

	/**
	 * 描画関数
	 */
	virtual void Draw() override = 0;

	/**
	 * キャッチ出来る状態か?
	 * @return キャッチ出来るならtrue
	 */
	inline bool GetIsCatch()
	{
		return m_IsCatch;
	}

	inline CollisionData::HIT_STATE GetHitState()
	{
		return m_pCollisionData->GetCollisionState().HitState;
	}

protected:
	static const D3DXVECTOR2 m_Rect;
	static const float		 m_Acceleration;
	static		 bool		 m_IsCatch;

	Lib::AnimUvController*   m_pAnimUvController;
	Lib::Vertex2D*			 m_pVertex;
	int						 m_TextureIndex;
	D3DXVECTOR2				 m_Pos;
	float					 m_MoveSpeed;
	CollisionData*		     m_pCollisionData;

};


#endif
