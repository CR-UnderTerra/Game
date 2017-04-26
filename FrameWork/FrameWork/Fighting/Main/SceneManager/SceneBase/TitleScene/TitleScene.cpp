/**
 * @file TitleScene.cpp
 * @brief TitleSceneクラス実装
 * @author kotani
 */
#include "TitleScene.h"


TitleScene::TitleScene() :
SceneBase(SCENE_TITLE)
{
}

TitleScene::~TitleScene()
{
}

SceneBase::SceneID TitleScene::Update()
{
	SceneID NextSceneID = m_SceneID;

	NextSceneID = SCENE_GAME;
	return NextSceneID;
}

void TitleScene::Draw()
{
}
