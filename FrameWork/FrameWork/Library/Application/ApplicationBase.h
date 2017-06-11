/**
 * @file   ApplicationBase.h
 * @brief  ApplicationBaseクラスのヘッダファイル
 * @author kotani
 */
#ifndef APPLICATIONBASE_H
#define APPLICATIONBASE_H
#define ENTRY_POINT int WINAPI WinMain(HINSTANCE hInst, HINSTANCE hPrevInst, LPSTR szStr, INT iCmdShow)
#include <Windows.h>

namespace Lib
{
	/**
	 * このクラスがメイン
	 * この抽象クラスを実装することでウィンドウが表示される
	 */
	class ApplicationBase
	{
	public:
		ApplicationBase();
		virtual ~ApplicationBase();

		static inline ApplicationBase* GetInstance()
		{
			return m_pInstance;
		}

		/**
		 * ライブラリの初期化
		 */
		void InitLib();

		/**
		 * ライブラリの解放
		 */
		void ReleaseLib();

		/**
		 * 初期化処理
		 *
		 * ライブラリで自動に呼ばれる
		 */
		virtual void Init() = 0;

		/**
		 * 開放処理
		 *
		 * ライブラリで自動に呼ばれる
		 */
		virtual void Release() = 0;

		/**
		 * この関数が毎フレーム呼ばれる
		 * @return trueが変えると終了する
		 */
		virtual bool MainLoop() = 0;

		int Boot(int _windowWidth, int _windowHeight,LPCTSTR _windowName);

	private:
		static ApplicationBase* m_pInstance;

	};

	inline int Boot(int _windowWidth, int _windowHeight, LPCTSTR _windowName)
	{
		return ApplicationBase::GetInstance()->Boot(_windowWidth, _windowHeight, _windowName);
	};
}


#endif
