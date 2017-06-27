/**
 * @file   TitleBackGround.h
 * @brief  TitleBackGroundクラスのヘッダファイル
 * @author kotani
 */
#ifndef TITLEBACKGROUND_H
#define TITLEBACKGROUND_H
#include "Vertex2D/Vertex2D.h"
#include "Animation\AnimUvController.h"

class TitleBackGround
{
public:
	/**
	 * コンストラクタ
	 */
	TitleBackGround();

	/**
	 * デストラクタ
	 */
	~TitleBackGround();

	/**
	 * 制御処理
	 * @return alpha値が1になるとtrueを返す
	 */
	bool Update();

	/**
	 * 描画処理
	 */
	void Draw();

	bool NextSceneControl();

private:
	static const D3DXVECTOR2 m_Rect;
	static const float		 m_DisplayTime; //!< 何秒で表示するか
	float					 m_Alpha;
	bool					 m_IsTransitionControl;
	float					 m_AddAlphaValue;
	D3DXVECTOR2				 m_Pos;
	int						 m_TextureIndex;
	int						 m_TextureIndex2;
	Lib::AnimUvController*	 m_pUvController;
	Lib::Vertex2D*		     m_pVertex;

};


#endif
