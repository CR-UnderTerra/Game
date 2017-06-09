#ifndef SCOREBASE_H
#define SCOREBASE_H
#include "Vertex2D/Vertex2D.h"
#include "Animation/AnimUvController.h"
#include "../../../GameDataManager/GameDataManager.h"

class CountDisplayBase
{
public:
	CountDisplayBase(D3DXVECTOR2* _pos, LPCTSTR _animName, int _textureIndex);
	virtual ~CountDisplayBase();

	virtual bool Update() = 0;
	void Draw(float _alpha);

protected:
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
	int				   m_TextureIndex;
	Vertex			   m_Vertex;
	Vertex			   m_NumSymbolVertex;
	Vertex			   m_NumVertex[2]; //!< 何回かを表示する数字

};


#endif
