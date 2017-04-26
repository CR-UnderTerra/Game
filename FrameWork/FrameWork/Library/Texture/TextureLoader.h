#ifndef TEXTURELOADER_H
#define TEXTURELOADER_H
#include "..\Singleton.h" 
#include <D3DX11.h>

namespace Lib
{
	/**
	 * テクスチャを読み込むクラス
	 */
	class TextureLoader
	{
	public:
		static void Init(ID3D11Device* _pDevice)
		{
			m_pDevice = _pDevice;
		}

		/**
		 * テクスチャを読み込む関数
		 * @param[in] _pFileName 読み込むテクスチャファイルのパス
		 * @return テクスチャの読み込みに失敗したらnull
		 */
		static ID3D11ShaderResourceView* Load(LPCTSTR _pFileName);

	private:
		TextureLoader(){};
		~TextureLoader(){};
		static ID3D11Device* m_pDevice;

	};
}



#endif
