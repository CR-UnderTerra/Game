#ifndef TEXTUREMANAGER_H
#define TEXTUREMANAGER_H
#include "..\Singleton.h"
#include "TextureContainer.h"
#include "TextureLoader.h"

class TextureLoader;
class TextureContainer;

namespace Lib
{
	class TextureManager
	{
		friend Singleton<TextureManager>;
	public:
		/**
		 * 初期化処理
		 * @param[in] _pDevice Directx11のデバイス
		 */
		void Init(ID3D11Device* _pDevice);

		/**
		 * テクスチャの読み込み
		 * @param[in] _pFileName 読み込むテクスチャのパス
		 * @param[out] _index 読み込んだテクスチャへのインデックスが入る
		 * @return 成功すればtrue
		 */
		bool Load(LPCTSTR _pFileName,int* _index);

		/**
		 * 格納しているテクスチャを取得する関数
		 * @param[in] _index 取得したいテクスチャのインデックス
		 * @return テクスチャのリソースビュー
		 */
		inline ID3D11ShaderResourceView* GetTexture(int _index) const
		{
			return SINGLETON_INSTANCE(TextureContainer).GetTexture(_index);
		}

		/**
		 * テクスチャの開放
		 * @param[in] _index 開放するテクスチャのインデックス
		 */
		inline void ReleaseTexture(int _index)
		{
			SINGLETON_INSTANCE(TextureContainer).ReleaseTexture(_index);
		}

		/**
		 * 開放処理
		 */
		inline void Release()
		{
			SINGLETON_INSTANCE(TextureContainer).ClearBuffer();
		}

	private:
		TextureManager(){};
		~TextureManager();

	};
}


#endif
