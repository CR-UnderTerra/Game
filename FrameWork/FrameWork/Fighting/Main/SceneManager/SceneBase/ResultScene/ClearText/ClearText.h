/**
 * @file   ClearText.h
 * @brief  ClearTextクラスのヘッダファイル
 * @author kotani
 */
#ifndef CLEARTEXT_H
#define CLEARTEXT_H
#include "Vertex2D/Vertex2D.h"
#include "Animation\AnimUvController.h"

class ClearText
{
public:
	/**
	 * コンストラクタ
	 */
	ClearText(int _textureIndex);

	/**
	 * デストラクタ
	 */
	~ClearText();

	/**
	 * 制御処理
	 */
	bool Update();

	/**
	 * 描画処理
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
