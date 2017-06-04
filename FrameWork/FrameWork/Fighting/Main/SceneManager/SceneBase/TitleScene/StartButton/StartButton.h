/**
 * @file   StartButton.h
 * @brief  StartButtonクラスのヘッダファイル
 * @author kotani
 */
#ifndef STARTBUTTON_H
#define STARTBUTTON_H
#include "Vertex2D/Vertex2D.h"
#include "Animation\AnimUvController.h"

class StartButton
{
public:
	/**
	 * コンストラクタ
	 */
	StartButton(int _textureIndex);

	/**
	 * デストラクタ
	 */
	~StartButton();

	/**
	 * 制御関数
	 * @return 一度alpha値が1になるとtrueを返す
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
	bool					 m_IsAddAlpha;  //!< アルファ値を足すか?
	bool					 m_IsButtonEnable;
	D3DXVECTOR2				 m_Pos;
	int						 m_TextureIndex;
	Lib::AnimUvController*	 m_pUvController;
	Lib::Vertex2D*		     m_pVertex;

};


#endif
