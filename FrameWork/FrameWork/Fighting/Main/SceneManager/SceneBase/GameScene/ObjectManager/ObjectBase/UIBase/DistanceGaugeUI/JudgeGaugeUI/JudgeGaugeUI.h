/**
 * @file   JudgeGaugeUI.h
 * @brief  JudgeGaugeUIクラスのヘッダファイル
 * @author kotani
 */
#ifndef JUDGEGAUGEUI_H
#define JUDGEGAUGEUI_H
#include "../../UIBase.h"

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
	 */
	JudgeGaugeUI();

	/**
	 * デストラクタ
	 */
	~JudgeGaugeUI();

	/**
	 * 制御関数
	 */
	void Update() override;

	/**
	 * 描画関数
	 */
	void Draw() override;

	/**
	 * 判断する
	 */
	JUDGE Judge(float _distance);

private:
	void InitVertex();

	int TextureIndex;
	Lib::Vertex2D*		     m_pGoodJudgeVertex;
	Lib::Vertex2D*		     m_pAmagingJudgeVertex;
	Lib::Vertex2D*		     m_pFantasticJudgeVertex;

};


#endif
