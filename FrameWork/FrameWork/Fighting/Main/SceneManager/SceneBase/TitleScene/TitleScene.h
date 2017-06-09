/**
 * @file TitleScene.h
 * @brief TitleSceneクラスのヘッダファイル
 * @author kotani
 */
#ifndef TITLESCENE_H
#define TITLESCENE_H
#include "..\SceneBase.h"

class TitleBackGround;
class TitleText;
class StartButton;

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

	/**
	 * 設定したキーが押されたか
	 * @return 押されたらtrue
	 */
	static bool KeyCheck();

private:
	TitleScene(const TitleScene&);
	void operator=(const TitleScene&);

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

	TitleBackGround* m_pTitleBackGround;
	TitleText*		 m_pTitleText;
	StartButton*	 m_pStartButton;

	int				 m_SoundIndex;
	int				 m_BlackOutTextureIndex;
	int				 m_BackGroundTextureIndex;
	int				 m_TextTextureIndex;

};


#endif
