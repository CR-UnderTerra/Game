/**
 * @file   AmazingText.h
 * @brief  AmazingTextクラスのヘッダファイル
 * @author kotani
 */
#ifndef AMAZINGTEXT_H
#define AMAZINGTEXT_H
#include "Vertex2D/Vertex2D.h"
#include "Animation/AnimUvController.h"

class AmazingText
{
public:
	/**
	 * コンストラクタ
	 */
	AmazingText(int _textureIndex, D3DXVECTOR2* _pos);

	/**
	 * デストラクタ
	 */
	~AmazingText();

	/**
	 * 制御処理
	 */
	void Update();

	/**
	 * 描画処理
	 */
	void Draw();

private:
	struct Vertex
	{
		D3DXVECTOR2			   Pos;
		D3DXVECTOR2			   Rect;
		Lib::AnimUvController* pUvController;
		Lib::Vertex2D*		   pVertex;
	};

	/**
	 * Vertexの初期化
	 * @param[in] _pos 座標
	 * @param[in] _rect 矩形
	 * @param[in] _animName 読み込むアニメーションの名前
	 * @param[out] _vertex 初期化するVertex構造体
	 */
	void InitVertex(D3DXVECTOR2* _pos, D3DXVECTOR2* _rect, LPCTSTR _animName, Vertex* _vertex);

	/**
	 * Vertexの開放
	 * @param[in] 開放するvertex構造体
	 */
	void ReleaseVertex(Vertex* _vertex);

	int		m_TextureIndex;
	Vertex	m_Vertex;
	Vertex  m_NumVertex[2]; //!< 何回かを表示する数字

};


#endif
