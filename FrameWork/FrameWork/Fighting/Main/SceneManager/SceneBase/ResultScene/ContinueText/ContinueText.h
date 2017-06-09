/**
 * @file   ContinueText.h
 * @brief  ContinueTextクラスのヘッダファイル
 * @author kotani
 */
#ifndef CONTINUETEXT_H
#define CONTINUETEXT_H
#include "Vertex2D/Vertex2D.h"
#include "Animation\AnimUvController.h"

class ContinueText
{
public:
	/**
	 * コンストラクタ
	 * @param[in] _textureIndex 使用するテクスチャのインデックス
	 */
	ContinueText(int _textureIndex);

	/**
	 * デストラクタ
	 */
	~ContinueText();

	/**
	 * 制御処理
	 * @return alpha値が1になったらtrue
	 */
	bool Update();

	/**
	 * 描画処理
	 */
	void Draw();

	inline void SetIsSelect(bool _isSelect)
	{
		m_IsSelect = _isSelect;
	}

	inline bool GetIsSelect()
	{
		return m_IsSelect;
	}

private:
	static const D3DXVECTOR2 m_Rect;
	static const float		 m_DisplayTime; //!< 何秒で表示するか
	float					 m_Alpha;
	float					 m_AddAlphaValue;
	D3DXVECTOR2				 m_Pos;
	int						 m_TextureIndex;
	Lib::AnimUvController*	 m_pUvController;
	Lib::Vertex2D*		     m_pVertex;
	bool					 m_IsSelect;
	bool					 m_IsAddAlpha;  //!< アルファ値を足すか?
	bool					 m_IsButtonEnable;

};


#endif
