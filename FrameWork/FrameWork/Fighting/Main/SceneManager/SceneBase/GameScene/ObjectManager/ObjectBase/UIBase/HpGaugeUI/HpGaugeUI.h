/**
 * @file   HpGaugeUI.h
 * @brief  HpGaugeUIクラスのヘッダファイル
 * @author kotani
 */
#ifndef HPGAUGEUI_H
#define HPGAUGEUI_H
#include <array>
#include "../UIBase.h"
#include "Vertex2D/Vertex2D.h"
#include "Animation/AnimUvController.h"

class HpIcon;

class HpGaugeUI : public UIBase
{
public:
	/**
	 * コンストラクタ
	 * @param[in] _textureIndex 使用するテクスチャのインデックス
	 */
	HpGaugeUI(int _textureIndex);

	/**
	 * デストラクタ
	 */
	~HpGaugeUI();

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
	std::array<HpIcon*, 6>	 m_pHpIcon;
	D3DXVECTOR2				 m_Pos;
	int						 m_TextureIndex;
	Lib::AnimUvController*   m_pUvController;
	Lib::Vertex2D*		     m_pVertex;

};


#endif
