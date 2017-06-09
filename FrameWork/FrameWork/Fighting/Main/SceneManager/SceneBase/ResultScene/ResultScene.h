﻿/**
 * @file   ResultScene.h
 * @brief  ResultSceneクラスのヘッダファイル
 * @author kotani
 */
#ifndef RESULTSCENE_H
#define RESULTSCENE_H
#include "../SceneBase.h"
#include "BackGround/ResultBackGround.h"
#include "ScoreWindow/ResultScoreWindow.h"

class ClearText;
class ContinueText;
class ReturnTitleText;
class TimeWindow;
class JudgeCountWindow;

class ResultScene : public SceneBase
{
public:
	enum BUTTON
	{
		CONTINUE_BUTTON,
		RETURN_TITLE_BUTTON
	};

	/**
	 * コンストラクタ
	 */
	ResultScene();

	/**
	 * デストラクタ
	 */
	virtual ~ResultScene();

	/**
	 * 制御関数
	 * @return 遷移先のシーンID
	 */
	SceneID Update() override;

	/**
	 * 描画処理
	 */
	void Draw() override;
	
	/**
	 * 設定したキーが押されたか
	 * @return 押されたらtrue
	 */
	static bool KeyCheck();

private:
	/**
	 * ライブラリの初期化
	 */
	void InitLibrary();

	/**
	 * ライブラリの解放
	 */
	void ReleaseLibrary();

	/**
	 * キーボードの状態更新
	 */
	void KeyUpdate();


	int				     m_BackGroundTextureIndex;
	int				     m_TextTextureIndex;
	int					 m_TextureIndex;
	Result::BackGround*  m_pBackGround;
	Result::ScoreWindow* m_pScoreWindow;
	ClearText*		     m_pClearText;
	ContinueText*	     m_pContinueText;
	ReturnTitleText*     m_pReturnTitleText;
	JudgeCountWindow*	 m_pJudgeCountWindow;
	TimeWindow*			 m_pTimeWindow;


};


#endif
