/**
 * @file   SceneManager.cpp
 * @brief  SceneManagerクラスの実装
 * @author kotani
 */
#include "SceneManager.h"
#include "SceneBase\SceneBase.h"
#include "SceneFactory\SceneFactory.h"
#include "DebugTool/DebugTimer.h"


SceneManager::SceneManager(HWND _hwnd) :
m_pScene(NULL),
m_State(SCENE_CREATE),
m_NextSceneID(SceneBase::SCENE_TITLE),
m_hWnd(_hwnd),
m_IsGameEnd(false)
{
}

SceneManager::~SceneManager()
{
	delete m_pScene;
}


//----------------------------------------------------------------------------------------------------
// Public Functions
//----------------------------------------------------------------------------------------------------

bool SceneManager::Run()
{
	Update();
	Draw();
	return m_IsGameEnd;
}

void SceneManager::Update()
{
	SceneBase::SceneID CurrentSceneID;

	switch (m_State)
	{
	case SCENE_CREATE:
		if (m_NextSceneID == SceneBase::FIN)
		{
			m_IsGameEnd = true;
			return;
		}
		else
		{
			m_pScene = SceneFactory::CreateScene(m_NextSceneID);
			m_State = SCENE_PROC;
		}
		break;
	case SCENE_PROC:
		CurrentSceneID = m_pScene->GetSceneID();
		m_NextSceneID = m_pScene->Update();

		if (m_NextSceneID != CurrentSceneID)
		{
			m_State = SCENE_RELEASE;
		}
		break;
	case SCENE_RELEASE:
		delete m_pScene;
		m_pScene = NULL;

		m_State = SCENE_CREATE;
		break;
	}
}

void SceneManager::Draw()
{
	if (m_State == SCENE_PROC)
	{
		m_pScene->Draw();
	}
}

