/**
 * @file   ResultScene.h
 * @brief  ResultSceneクラスのヘッダファイル
 * @author kotani
 */
#ifndef RESULTSCENE_H
#define RESULTSCENE_H
#include "../SceneBase.h"

class ResultScene : public SceneBase
{
public:
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

private:
	/**
	 * ライブラリの初期化
	 */
	void InitLibrary();

	/**
	 * ライブラリの解放
	 */
	void ReleaseLibrary();

};


#endif
