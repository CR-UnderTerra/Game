/**
 * @file   TextureContainer.cpp
 * @brief  TextureContainerクラスの実装
 * @author kotani
 */
#include "TextureContainer.h"


//----------------------------------------------------------------------------------------------------
// Public Functions
//----------------------------------------------------------------------------------------------------

void Lib::TextureContainer::Add(ID3D11ShaderResourceView* _pTextureResourceView, int* _index)
{
	*_index = m_pTextureResourceView.size();
	m_pTextureResourceView.push_back(_pTextureResourceView);
}

void Lib::TextureContainer::ReleaseTexture(int _index)
{
	if (m_pTextureResourceView[_index] != NULL)
	{
		m_pTextureResourceView[_index]->Release();
		m_pTextureResourceView[_index] = NULL;
	}
}
