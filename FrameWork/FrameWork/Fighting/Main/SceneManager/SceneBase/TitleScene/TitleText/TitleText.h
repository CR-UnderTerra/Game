/**
 * @file   TitleText.h
 * @brief  TitleTextクラスのヘッダファイル
 * @author kotani
 */
#ifndef TITLETEXT_H
#define TITLETEXT_H
#include "Vertex2D/Vertex2D.h"
#include "Animation\AnimUvController.h"

class TitleText
{
public:
	/**
	 * コンストラクタ
	 */
	TitleText(int _textureIndex);
	
	/**
	 * デストラクタ
	 */
	~TitleText();

	/**
	 * 制御関数
	 * @return alpha値が1になるとtrueを返す
	 */
	bool Update();

	/**
	 * 描画関数
	 */
	void Draw();

private:
	static const D3DXVECTOR2 m_Rect;
	static const float		 m_DisplayTime; //!< 何秒で表示するか
	float					 m_Alpha;
	float					 m_AddAlphaValue;
	D3DXVECTOR2				 m_Pos;
	int						 m_TextureIndex;
	Lib::AnimUvController*	 m_pUvController;
	Lib::Vertex2D*		     m_pVertex;

};


#endif
