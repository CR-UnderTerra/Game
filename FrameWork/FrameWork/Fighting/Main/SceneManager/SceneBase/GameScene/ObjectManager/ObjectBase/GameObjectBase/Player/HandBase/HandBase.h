/**
 * @file   HandBase.h
 * @brief  HandBaseクラスのヘッダファイル
 * @author kotani
 */
#ifndef HANDBASE_H
#define HANDBASE_H
#include "../../../GameObjectBase/GameObjectBase.h"
#include "Vertex2D/Vertex2D.h"
#include "Animation/AnimUvController.h"

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

protected:
	static const D3DXVECTOR2 m_Rect;
	static const float		 m_Acceleration;

	Lib::AnimUvController*   m_pAnimUvController;
	Lib::Vertex2D*			 m_pVertex;
	D3DXVECTOR2				 m_Pos;
	int						 m_TextureIndex;
	float					 m_MoveSpeed;
};


#endif
