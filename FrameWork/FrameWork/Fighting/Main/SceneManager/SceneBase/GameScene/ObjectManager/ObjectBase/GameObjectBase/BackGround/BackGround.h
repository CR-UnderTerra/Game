/**
 * @file   BackGround.h
 * @brief  BackGroundクラスのヘッダファイル
 * @author kotani
 */
#ifndef BACKGROUND_H
#define BACKGROUND_H
#include "Vertex2D/Vertex2D.h"
#include "Animation/AnimUvController.h"
#include "../GameObjectBase.h"

class BackGround : public GameObjectBase
{
public:
	/**
	 * コンストラクタ
	 * @param[in] _textureIndex 使用するテクスチャのインデックス
	 */
	BackGround(int _textureIndex);

	/**
	 * デストラクタ
	 */
	~BackGround();

	/**
	 * 制御関数
	 */
	void Update() override;

	/**
	 * 描画関数
	 */
	void Draw() override;

private:
	static const D3DXVECTOR2 m_Rect;

	Lib::AnimUvController* m_pAnimUvController;
	Lib::Vertex2D*		   m_pVertex;
	D3DXVECTOR2			   m_Pos;
	int					   m_TextureIndex;

};


#endif
