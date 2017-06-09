/**
 * @file   ScoreWindow.h
 * @brief  ScoreWindowクラスのヘッダファイル
 * @author kotani
 */
#ifndef RESULTSCOREWINDOW_H
#define RESULTSCOREWINDOW_H
#include "Vertex2D/Vertex2D.h"
#include "Animation/AnimUvController.h"

namespace Result
{
	class ScoreWindow
	{
	public:
		ScoreWindow();
		~ScoreWindow();

		/**
		 * 制御関数
		 * @return スケールが最大になるとtrue
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

		static const float		 m_DisplayTime; //!< 何秒で表示するか
		static const D3DXVECTOR2 m_Rect; //!< 何秒で表示するか
		Vertex					 m_NumVertex[5]; //!< 数字の一桁ずつの矩形
		int						 m_TextureIndex;
		D3DXVECTOR2				 m_Pos;
		float					 m_Scale;
		float					 m_AddScaleValue;
		int						 m_Score;

	};
}


#endif
