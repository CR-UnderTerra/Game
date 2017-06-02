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
#include "JudgeGaugeUI/JudgeGaugeUI.h"
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
	void SetKnifeBar(float _distance, float _velocity,int _index);

	/**
	 * ナイフゲージの有効かを設定する
	 * @param[in] _index 止めるナイフバーのインデックス
	 * @param[in] _IsEnable 有効ならtrue
	 */
	void SetKnifeBarIsEnable(int _index, bool _IsEnable);

	JudgeGaugeUI::JUDGE KnifeJadge(int _index);

private:
	static const D3DXVECTOR2 m_Rect;
	D3DXVECTOR2				 m_Pos;
	int					     m_TextureIndex;
	int						 m_DistanceGaugeTextureIndex;
	std::vector<KnifeBar*>   m_pKnifeBar;
	Lib::AnimUvController*   m_pUvController;
	Lib::Vertex2D*		     m_pVertex;
	JudgeGaugeUI*			 m_pJudgeGaugeUI;

};


#endif
