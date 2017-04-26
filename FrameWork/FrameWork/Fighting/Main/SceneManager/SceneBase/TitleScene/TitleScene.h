/**
 * @file TitleScene.h
 * @brief TitleSceneクラスのヘッダファイル
 * @author kotani
 */
#ifndef TITLESCENE_H
#define TITLESCENE_H
#include "..\SceneBase.h"


/**
 * タイトルシーンを管理するクラス
 */
class TitleScene : public SceneBase
{
public:
	/**
	 * コンストラクタ
	 */
	TitleScene();

	/**
	 * デストラクタ
	 */
	virtual ~TitleScene();

	/**
	 * 制御関数
	 * @return 遷移先のシーンID
	 */
	SceneID Update() override;

	/**
	 * 描画関数
	 */
	void Draw() override;

private:
	TitleScene(const TitleScene&);
	void operator=(const TitleScene&);

	int m_SoundIndex;

};


#endif
