/**
 * @file   TimeWindow.h
 * @brief  TimeWindowクラスのヘッダファイル
 * @author kotani
 */
#ifndef TIMEWINDOW_H
#define TIMEWINDOW_H
#include "Vertex2D/Vertex2D.h"
#include "Animation/AnimUvController.h"

class TimeWindow
{
public:
	TimeWindow();
	~TimeWindow();
	
	/**
	 * 制御関数
	 */
	bool Update();

	/**
	 * 描画関数
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
	
	static const float m_DisplayTime; //!< 何秒で表示するか
	Vertex			   m_ColonVertex;
	Vertex			   m_NumVertex[4]; //!< 数字の一桁ずつの矩形
	int				   m_TextureIndex;
	D3DXVECTOR2		   m_Pos;
	int				   m_Second; //!< 秒
	int				   m_Minute; //!< 分
	float			   m_Alpha;
	float			   m_AddAlphaValue;

};


#endif
