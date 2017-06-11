/**
 * @file   Window.h
 * @brief  Windowクラスのヘッダファイル
 * @author kotani
 */
#ifndef WINDOW_H
#define WINDOW_H
#include <windows.h>
#include "..\Singleton.h"
#define WINAPI_ENTRY int WINAPI WinMain(HINSTANCE hInst, HINSTANCE hPrevInst, LPSTR szStr, INT iCmdShow)

namespace Lib
{
	/**
	 * ウィンドウの生成をしてくれるクラス
	 *
	 * ライブラリが自動で生成と解放をしてくれる
	 */
	class Window
	{
		friend Singleton<Window>;
	public:
		inline void Init(HINSTANCE _hInstance)
		{
			m_hInstance = _hInstance;
		}

		inline HWND GetWindowHandle() const
		{
			return m_hWnd;
		}

		inline HINSTANCE GetInstanceHandle() const
		{
			return m_hInstance;
		}

		inline RECT GetWindowSize()
		{
			return m_WindowSize;
		}

		/**
		 * ウィンドウの生成
		 * @param[in] _width ウィンドウの横幅
		 * @param[in] _height ウィンドウの縦幅
		 * @param[in] _windowName ウィンドウの名前
		 * @return 成功したらS_OK
		 */
		HRESULT DispWindow(INT _width, INT _height, LPCTSTR _windowName);

		/**
		 * ウィンドウの生成(アイコンあり)
		 * @param[in] _width ウィンドウの横幅
		 * @param[in] _height ウィンドウの縦幅
		 * @param[in] _windowName ウィンドウの名前
		 * @param[in] _iconName アイコンのパス
		 * @return 成功したらS_OK
		 */
		HRESULT DispWindow(INT _width, INT _height, LPCTSTR _windowName, LPCTSTR _iconName);

		void ChangeWindowSize(int _width,int _hight);

	private:
		Window() :
			m_hInstance(NULL),
			m_hWnd(NULL){};
		~Window(){};
		RECT	m_WindowSize;
		HINSTANCE m_hInstance;
		HWND m_hWnd;

	};
}


#endif
