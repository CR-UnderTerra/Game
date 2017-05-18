/**
 * @file   TimerUI.h
 * @brief  TimerUIクラスのヘッダファイル
 * @author kotani
 */
#ifndef SCOREUI_H
#define SCOREUI_H
#include "../UIBase.h"
#include "Animation/AnimUvController.h"
#include "Vertex2D/Vertex2D.h"

class TimerUI : public UIBase
{
public:
	/**
	 * コンストラクタ
	 */
	TimerUI();

	/**
	 * デストラクタ
	 */
	~TimerUI();

	/**
	 * 制御関数
	 */
	void Update() override;

	/**
	 * 描画関数
	 */
	void Draw() override;

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

	Vertex		m_FrameVertex;
	Vertex		m_ColonVertex;
	Vertex		m_NumVertex[4]; //!< 数字の一桁ずつの矩形
	int			m_TextureIndex;
	D3DXVECTOR2 m_Pos;
	int			m_Count;  //!< 一秒をカウントする
	int			m_Second; //!< 秒
	int			m_Minute; //!< 分

};


#endif
