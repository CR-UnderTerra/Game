#include <crtdbg.h>
#include "Window/Window.h"
#include "SceneManager/SceneManager.h"
#include "Dx11/DX11Manager.h"

#define WINDOW_WIDTH 1920
#define WINDOW_HEIGHT 1080

LRESULT CALLBACK WindowProc(HWND _hwnd, UINT _message, WPARAM _wParam, LPARAM _lParam);

int WINAPI WinMain(HINSTANCE hInst, HINSTANCE hPrevInst, LPSTR szStr, INT iCmdShow)
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	//Window表示
	SINGLETON_CREATE(Lib::Window);
	SINGLETON_INSTANCE(Lib::Window).DispWindow(hInst, WINDOW_WIDTH, WINDOW_HEIGHT, "test", &WindowProc);
	const HWND hWnd = SINGLETON_INSTANCE(Lib::Window).GetWindowHandle();

	SINGLETON_CREATE(Lib::DX11Manager);
	SINGLETON_INSTANCE(Lib::DX11Manager).Init(hWnd);

	SceneManager* sceneManager = new SceneManager(SINGLETON_INSTANCE(Lib::Window).GetWindowHandle());

	MSG Msg;
	ZeroMemory(&Msg, sizeof(Msg));
	while (Msg.message != WM_QUIT)
	{
		if (PeekMessage(&Msg, NULL, 0U, 0U, PM_REMOVE))
		{
			TranslateMessage(&Msg);
			DispatchMessage(&Msg);
		}
		else
		{
			if (sceneManager->Run())
			{
				break;
			}
		}
	}

	delete sceneManager;

	SINGLETON_INSTANCE(Lib::DX11Manager).Release();
	SINGLETON_DELETE(Lib::DX11Manager);

	SINGLETON_DELETE(Lib::Window);

	return (INT)Msg.wParam;
}


LRESULT CALLBACK WindowProc(HWND _hwnd, UINT _message, WPARAM _wParam, LPARAM _lParam)
{
	switch (_message)
	{
	case WM_CLOSE:
		if (MessageBox(_hwnd, TEXT("終わりますか？"), TEXT("終了"), MB_YESNO | MB_ICONQUESTION) == IDYES)
		{
			DestroyWindow(_hwnd);
		}
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
		break;
	case WM_KEYDOWN:
		switch (static_cast<CHAR>(_wParam))
		{
		case VK_ESCAPE:
			if (MessageBox(_hwnd, TEXT("終わりますか？"), TEXT("終了"), MB_YESNO | MB_ICONQUESTION) == IDYES)
			{
				DestroyWindow(_hwnd);
			}
			break;
		}
		break;
	default: 
		return DefWindowProc(_hwnd, _message, _wParam, _lParam);
	}
	return 0;
}
