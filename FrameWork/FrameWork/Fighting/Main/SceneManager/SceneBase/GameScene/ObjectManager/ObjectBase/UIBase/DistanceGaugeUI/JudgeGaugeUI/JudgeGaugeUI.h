/**
 * @file   JudgeGaugeUI.h
 * @brief  JudgeGaugeUIクラスのヘッダファイル
 * @author kotani
 */
#ifndef JUDGEGAUGEUI_H
#define JUDGEGAUGEUI_H
#include "../../UIBase.h"
#include "Vertex2D/Vertex2D.h"
#include "Animation/AnimUvController.h"

class JudgeGaugeUI : public UIBase
{
public:
	enum JUDGE
	{
		GOOD_JUDGE,
		AMAZING_JUDGE,
		FANTASTIC_JUDGE,
		FAILED_JUDGE
	};

	/**
	 * コンストラクタ
	 * @param[in] 使用するテクスチャのインデックス
	 * @param[in] 距離ゲージの下の座標
	 */
	JudgeGaugeUI(int _textureIndex,D3DXVECTOR2* _distanceGaugeButtomPos);

	/**
	 * デストラクタ
	 */
	~JudgeGaugeUI();

	/**
	 */
	void Update() override;

	/**
	 * 描画関数
	 */
	void Draw() override;

	/**
	 * 判断する
	 */
	JUDGE Judge(D3DXVECTOR2 _KnifeBarPos);

private:
	struct JudgeVertex
	{
		Lib::Vertex2D*		   pVertex;
		Lib::AnimUvController* pUvController;
		D3DXVECTOR2			   Rect;
		D3DXVECTOR2			   Pos;
	};


	/**
	 * judgeVertexの初期化処理
	 * @param[in,out] _pJudgeVertex 初期化するJudgeVertex
	 * @param[in] _pos 描画する座標
	 * @param[in] _rect 描画する矩形
	 * @rapam[in] _animName 読み込むアニメーションの名前
	 */
	void InitJudgeVertex(JudgeVertex* _pJudgeVertex, D3DXVECTOR2* _pos, D3DXVECTOR2* _rect, LPCTSTR _animName);

	/**
	 * judgeVertexの解放処理
	 * @param[in] _pJudgeVertex 解放するJudgeVertex
	 */
	void ReleaseJudgeVertex(JudgeVertex* _pJudgeVertex);

	int						 m_TextureIndex;
	D3DXVECTOR2				 m_DistanceGaugeButtomPos;
	JudgeVertex				 m_GoodJudgeVertex;
	JudgeVertex				 m_AmazingJudgeVertex;
	JudgeVertex				 m_FantasticJudgeVertex;

};


#endif
