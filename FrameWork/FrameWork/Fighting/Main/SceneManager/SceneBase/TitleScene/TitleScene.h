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
	 * キーボードの状態更新
	 */
	void KeyUpdate();

	TitleBackGround* m_pTitleBackGround;
	TitleText*		 m_pTitleText;
	StartButton*	 m_pStartButton;

	int				 m_SoundIndex;
	static int		 m_ButtonSoundIndex;
	int				 m_BlackOutTextureIndex;
	int				 m_BackGroundTextureIndex;
	int				 m_BackGroundTextureIndex2;
	int				 m_TextTextureIndex;
	bool			 m_IsNextSceneControl;

};


#endif
