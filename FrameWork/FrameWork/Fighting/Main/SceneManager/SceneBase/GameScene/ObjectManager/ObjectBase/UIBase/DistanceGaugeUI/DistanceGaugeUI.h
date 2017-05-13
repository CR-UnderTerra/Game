/**
 * @file   DistanceGaugeUI.h
 * @brief  DistanceGaugeUIクラスのヘッダファイル
 * @author kotani
 */
#ifndef DISTANCEGAUGEUI_H
#define DISTANCEGAUGEUI_H
#include "../UIBase.h"
#include "Vertex2D/Vertex2D.h"
#include "Animation/AnimUvController.h"
#include <vector>
class KnifeBar;

/**
 * 距離のメーターを管理するクラス
 */
class DistanceGaugeUI : public UIBase
{
public:
	/**
	 * コンストラクタ
	 * @param[in] _textureIndex 使用するテクスチャのインデックス
	 */
	DistanceGaugeUI(int _textureIndex);

	/**
	 * デストラクタ
	 */
	~DistanceGaugeUI();

	/**
	 * 制御関数
	 */
	void Update() override;

	/**
	 * 描画関数
	 */
	void Draw() override;

	/**
	 * KnifeBarをセットする
	 */
	void SetKnifeBar(float _distance, float _velocity);

private:
	static const D3DXVECTOR2 m_Rect;
	D3DXVECTOR2				 m_Pos;
	int					     m_TextureIndex;
	std::vector<KnifeBar*>   m_pKnifeBar;
	Lib::AnimUvController*   m_pUvController;
	Lib::Vertex2D*		     m_pVertex;

};


#endif
