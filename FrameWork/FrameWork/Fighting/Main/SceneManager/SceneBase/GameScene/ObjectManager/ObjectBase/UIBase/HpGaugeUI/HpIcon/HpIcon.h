/**
 * @file   HpIcon.h
 * @brief  HpIconクラスのヘッダファイル
 * @author kotani
 */
#ifndef HPICON_H
#define HPICON_H
#include "../../UIBase.h"
#include "Vertex2D/Vertex2D.h"
#include "Animation/AnimUvController.h"

class HpIcon : public UIBase
{
public:
	/**
	 * コンストラクタ
	 * @param[in] _textureIndex 使用するテクスチャのインデックス
	 * @param[in] _pos 描画する座標
	 */
	HpIcon(int _textureIndex, D3DXVECTOR2* _pos);

	/**
	 * デストラクタ
	 */
	~HpIcon();
	
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
	D3DXVECTOR2				 m_Pos;
	int						 m_TextureIndex;
	Lib::AnimUvController*   m_pUvController;
	Lib::Vertex2D*		     m_pVertex;

};


#endif
