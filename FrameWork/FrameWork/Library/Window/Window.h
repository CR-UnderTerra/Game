/**
 * @file   Window.h
 * @brief  Windowクラスのヘッダファイル
 * @author kotani
 */
#ifndef WINDOW_H
#define WINDOW_H
#include <windows.h>
#include "..\Singleton.h"

namespace Lib
{
	/**
	 * ウィンドウの生成をしてくれるクラス
	 */
	class Window
	{
		friend Singleton<Window>;
	public:
		inline HWND GetWindowHandle() const
		{
			return m_hWnd;
		}

		inline HINSTANCE GetInstanceHandle() const
		{
			return m_hInstance;
		}

		/**
		 * ウィンドウの生成
		 * @param[in] _hInstance インスタンスハンドル
		 * @param[in] _width ウィンドウの横幅
		 * @param[in] _height ウィンドウの縦幅
		 * @param[in] _windowName ウィンドウの名前
		 * @param[in] _wndProc ウィンドウプロシージャの関数ポインタ
		 * @return 成功したらS_OK
		 */
		HRESULT DispWindow(HINSTANCE _hInstance, INT _width, INT _height, LPCTSTR _windowName,LRESULT CALLBACK _wndProc(HWND, UINT, WPARAM, LPARAM));

		/**
		 * ウィンドウの生成(アイコンあり)
		 * @param[in] _hInstance インスタンスハンドル
		 * @param[in] _width ウィンドウの横幅
		 * @param[in] _height ウィンドウの縦幅
		 * @param[in] _windowName ウィンドウの名前
		 * @param[in] _iconName アイコンのパス
		 * @param[in] _wndProc ウィンドウプロシージャの関数ポインタ
		 * @return 成功したらS_OK
		 */
		HRESULT DispWindow(HINSTANCE _hInstance, INT _width, INT _height, LPCTSTR _windowName, LPCTSTR _iconName, LRESULT CALLBACK _wndProc(HWND, UINT, WPARAM, LPARAM));

	private:
		Window() :
			m_hInstance(NULL),
			m_hWnd(NULL){};
		~Window(){};

		HINSTANCE m_hInstance;
		HWND m_hWnd;

	};
}


#endif
