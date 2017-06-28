/**
 * @file   BackGround.h
 * @brief  BackGroundクラスのヘッダファイル
 * @author kotani
 */
#ifndef BACKGROUND_H
#define BACKGROUND_H
#include "Vertex2D/Vertex2D.h"
#include "Animation/AnimUvController.h"
#include "../GameObjectBase.h"
#include "../../../../../GameDataManager/GameDataManager.h"

class BackGround : public GameObjectBase
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
	 * 制御関数
	 */
	void Update() override;

	/**
	 * 描画関数
	 */
	void Draw() override;

private:
	static const D3DXVECTOR2 m_Rect;

	Lib::AnimUvController* m_pAnimUvController;
	Lib::Vertex2D*		   m_pVertex;
	Lib::Vertex2D*		   m_pVertex2;
	D3DXVECTOR2			   m_Pos;
	int					   m_TextureIndex;

	int					   m_BlueSky;
	int					   m_PurpleSky;
	int					   m_OrangeSky;
	int					   m_RedSky;

	int					   m_EnemyLine;
	float				   m_Alfa;
	float				   m_Alfa2;
	float				   m_Alfa3;
	float				   m_Alfa4;
	float				   m_Alfa5;
};

#endif
