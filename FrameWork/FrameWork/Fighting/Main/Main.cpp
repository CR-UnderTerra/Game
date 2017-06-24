#include "SceneManager/SceneManager.h"
#include "Application/ApplicationBase.h"
#include "Window/Window.h"
#include "Helper/Helper.h"

#define WINDOW_WIDTH 1920
#define WINDOW_HEIGHT 1080

class App : Lib::ApplicationBase
{
public:
	App() :
		ApplicationBase(TEXT("私の愛を受け取って"), WINDOW_WIDTH, WINDOW_HEIGHT)
	{};
	~App() = default;

	void Init()
	{
		m_pSceneManager = new SceneManager();
	};

	void Release()
	{
		Lib::SafeDelete<SceneManager>(m_pSceneManager);
	};

	bool MainLoop()
	{
		if (m_pSceneManager->Run())
		{
			return true;
		}
		return false;
	};

private:
	SceneManager* m_pSceneManager;

};

App app;
