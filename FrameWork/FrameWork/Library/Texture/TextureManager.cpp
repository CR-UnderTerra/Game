#include "TextureManager.h"

Lib::TextureManager::~TextureManager()
{
	SINGLETON_DELETE(TextureContainer);
}

void Lib::TextureManager::Init(ID3D11Device* _pDevice)
{
	SINGLETON_CREATE(TextureContainer);
	TextureLoader::Init(_pDevice);
}

bool Lib::TextureManager::Load(LPCTSTR _pFileName, int* _index)
{
	ID3D11ShaderResourceView* pTexture = TextureLoader::Load(_pFileName);
	if (pTexture == NULL)
	{
		return false;
	}
	SINGLETON_INSTANCE(TextureContainer).
		Add(pTexture, _index);
	return true;
}
