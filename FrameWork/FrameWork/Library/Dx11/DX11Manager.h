﻿/**
 * @file   DX11Manager.h
 * @brief  DX11Managerクラスのヘッダファイル
 * @author kotani
 */
#ifndef DX11MANAGER_H
#define DX11MANAGER_H
#include <D3D11.h>
#include <Windows.h>
#include "..\Singleton.h"

namespace Lib
{
	class DX11Manager
	{
		friend Singleton<DX11Manager>;
	public:
		/**
		 * スクリーンの設定を切り替える関数
		 */
		inline void SetFullScreenState(bool _isFullScreen)
		{
			m_pDXGISwapChain->SetFullscreenState(_isFullScreen, NULL);
		}

		/**
		 * DX11Managerクラスの初期化関数
		 * @param[in] _hWnd DX11Managerが対応するウィンドウのハンドル
		 * @return 初期化に成功したらtrue
		 */
		bool Init(HWND _hWnd);

		/**
		 * DX11Managerクラスの解放関数
		 */
		void Release();

		/**
		 * 描画前処理を行う関数
		 */
		void BeginScene();

		/**
		 * 描画後処理を行う関数
		 */
		void EndScene();

		/**
		 * 深度テストのオンオフを切り替える関数
		 * @param[in] _isStencil 深度テストを使用するかのフラグ
		 */
		void SetDepthStencilTest(bool _isStencil);

		/**
		 * DirectX11デバイスを取得する関数
		 * @return DirectX11デバイス
		 */
		inline ID3D11Device* GetDevice() const
		{
			return m_pDevice;
		}

		/**
		 * DirectX11デバイスコンテキストを取得する関数
		 * @return DirectX11デバイスコンテキスト
		 */
		inline ID3D11DeviceContext* GetDeviceContext() const
		{
			return m_pDeviceContext;
		}

	private:
		/**
		 * DX11Managerクラスのコンストラクタ
		 */
		DX11Manager();

		/**
		 * DX11Managerクラスのデストラクタ
		 */
		~DX11Manager(){};

		/**
		 * デバイスの初期化関数
		 * @return 初期化に成功したらtrue
		 */
		bool InitDevice();

		/**
		 * ディスプレイ系の初期化関数
		 * @return 初期化に成功したらtrue
		 */
		bool InitDisplay();

		/**
		 * デバイスの解放関数
		 */
		void ReleaseDevice();

		/**
		 * ディスプレイ系の解放関数
		 */
		void ReleaseDisplay();

		static DX11Manager*		m_pDX11Manager;
		static float			m_ClearColor[4];
		ID3D11Device*			m_pDevice;
		ID3D11DeviceContext*	m_pDeviceContext;
		IDXGIDevice1*			m_pDXGI;
		IDXGIAdapter*			m_pAdapter;
		IDXGIFactory*			m_pDXGIFactory;
		IDXGISwapChain*			m_pDXGISwapChain;
		DXGI_SWAP_CHAIN_DESC	m_DXGISwapChainDesc;
		ID3D11Texture2D*		m_pBackBuffer;
		ID3D11RenderTargetView* m_pRenderTargetView;
		ID3D11Texture2D*		m_pDepthStencilBuffer;
		D3D11_TEXTURE2D_DESC	m_DepthDesc;
		ID3D11DepthStencilView* m_pDepthStencilView;
		D3D11_VIEWPORT			m_ViewPort;
		ID3D11RasterizerState*  m_pRasterizerState;
		D3D11_RASTERIZER_DESC	m_RasterizerDesc;
		HWND					m_hWnd;
		RECT					m_WindowRect;

	};
}

#endif
