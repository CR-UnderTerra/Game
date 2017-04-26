#include "TextureLoader.h"

ID3D11Device* Lib::TextureLoader::m_pDevice = NULL;


//----------------------------------------------------------------------------------------------------
// Public Functions
//----------------------------------------------------------------------------------------------------

ID3D11ShaderResourceView* Lib::TextureLoader::Load(LPCTSTR _pFileName)
{
	/* 削除予定 */
	ID3D11ShaderResourceView* pResourceView = NULL;
	if (FAILED(D3DX11CreateShaderResourceViewFromFile(
		m_pDevice,
		_pFileName,
		NULL,
		NULL,
		&pResourceView,
		NULL)))
	{
		OutputDebugString(TEXT("テクスチャの読み込みに失敗しました\n"));
	}

	return pResourceView;
}