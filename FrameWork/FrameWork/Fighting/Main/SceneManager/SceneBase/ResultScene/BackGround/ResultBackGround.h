#ifndef RESULTBACKGROUND_H
#define RESULTBACKGROUND_H
#include "Vertex2D/Vertex2D.h"
#include "Animation\AnimUvController.h"

namespace Result
{
	class BackGround
	{
	public:
		/**
		* コンストラクタ
		* @param[in] _textureIndex 使用するテクスチャのインデックス
		*/
		BackGround(int _textureIndex);

		/**
		* デストラクタ
		*/
		~BackGround();

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
}


#endif
