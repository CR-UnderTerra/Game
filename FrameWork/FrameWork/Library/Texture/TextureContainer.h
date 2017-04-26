/**
 * @file   TextureContainer.h
 * @brief  TextureContainerクラスのヘッダファイル
 * @author kotani
 */
#ifndef TEXTURECONTAINER_H
#define TEXTURECONTAINER_H
#include <D3DX11.h>
#include <vector>
#include "..\Singleton.h"

namespace Lib
{
	/**
	 * テクスチャのデータを入れておく
	 */
	class TextureContainer
	{
		friend Singleton<TextureContainer>;
	public:
		/**
		 * テクスチャのリソースを追加
		 * @param[in] _pTextureResourceView 読み込んだテクスチャ
		 * @param[out] _index 読み込んだテクスチャのインデックス
		 */
		void Add(ID3D11ShaderResourceView* _pTextureResourceView, int* _index);

		/**
		 * 格納しているテクスチャを取得する関数
		 * @param[in] _index 取得したいテクスチャのインデックス
		 * @return テクスチャのリソースビュー
		 */
		inline ID3D11ShaderResourceView* GetTexture(int _index) const
		{
			return m_pTextureResourceView[_index];
		}

		/**
		 * 格納しているテクスチャを解放する関数
		 * @param[in] _index 解放したいテクスチャのインデックス
		 */
		void ReleaseTexture(int _index);

		/**
		 * テクスチャを確保しているバッファをクリアする
		 *
		 * vectorを使用しているのでバッファ領域は解放されない。\n
		 * バッファ領域はTextureManagerのDelete()が呼ばれて破棄されたときに解放される。
		 */
		inline void ClearBuffer()
		{
			m_pTextureResourceView.clear();
		}

	private:
		TextureContainer(){};
		~TextureContainer(){};

		std::vector<ID3D11ShaderResourceView*>		m_pTextureResourceView;

	};
}


#endif
