#include "SceneManager/SceneManager.h"
#include "Application/ApplicationBase.h"
#include "Window/Window.h"

#define WINDOW_WIDTH 1920
#define WINDOW_HEIGHT 1080

class App : Lib::ApplicationBase
{
public:
	App() = default;
	~App() = default;

	void Init()
	{
		SINGLETON_INSTANCE(Lib::Window).DispWindow(WINDOW_WIDTH, WINDOW_HEIGHT, TEXT("私の愛を受け取って"));
		m_pSceneManager = new SceneManager();
	};

	void Release()
	{
		delete m_pSceneManager;
		m_pSceneManager = NULL;
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
