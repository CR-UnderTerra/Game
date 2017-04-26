/**
 * @file   Vertex2D.cpp
 * @brief  Vertex2Dクラスの実装
 * @author kotani
 */
#include "Vertex2D.h"
#include <Windows.h>

const int  Lib::Vertex2D::m_VertexNum = 4;
const UINT Lib::Vertex2D::m_ColorMask = 0xffffffff;

Lib::Vertex2D::Vertex2D(ID3D11Device* _pDevice, ID3D11DeviceContext* _pDeviceContext, HWND _hWnd) :
m_pDevice(_pDevice),
m_pDeviceContext(_pDeviceContext),
m_hWnd(_hWnd),
m_pVertexShader(NULL),
m_pVertexCompiledShader(NULL),
m_pVertexLayout(NULL),
m_pPixelShader(NULL),
m_pBlendState(NULL),
m_pSamplerState(NULL),
m_pVertexBuffer(NULL),
m_pConstantBuffer(NULL),
m_pTextureResourceView(NULL),
m_ClientWidth(0),
m_ClientHeight(0)
{
}


//----------------------------------------------------------------------------------------------------
// Public Functions
//----------------------------------------------------------------------------------------------------

bool Lib::Vertex2D::Init(const D3DXVECTOR2* _pRectSize, const D3DXVECTOR2* _pUV)
{
	RECT ClientRect;
	GetClientRect(m_hWnd, &ClientRect);
	m_ClientWidth = static_cast<float>(ClientRect.right);
	m_ClientHeight = static_cast<float>(ClientRect.bottom);

	if (!InitVertexShader())
	{
		return false;
	}

	if (!InitVertexLayout())
	{
		ReleaseVertexShader();
		return false;
	}

	if (!InitPixelShader())
	{
		ReleaseVertexLayout();
		ReleaseVertexShader();
		return false;
	}

	if (!InitBlendState())
	{
		ReleasePixelShader();
		ReleaseVertexLayout();
		ReleaseVertexShader();
		return false;
	}

	if (!InitSamplerState())
	{
		ReleaseBlendState();
		ReleasePixelShader();
		ReleaseVertexLayout();
		ReleaseVertexShader();
		return false;
	}

	if (!InitVertexBuffer(_pRectSize, _pUV))
	{
		ReleaseSamplerState();
		ReleaseBlendState();
		ReleasePixelShader();
		ReleaseVertexLayout();
		ReleaseVertexShader();
		return false;
	}

	if (!InitConstantBuffer())
	{
		ReleaseVertexBuffer();
		ReleaseSamplerState();
		ReleaseBlendState();
		ReleasePixelShader();
		ReleaseVertexLayout();
		ReleaseVertexShader();
		return false;
	}

	if (!WriteConstantBuffer())
	{
		ReleaseConstantBuffer();
		ReleaseVertexBuffer();
		ReleaseSamplerState();
		ReleaseBlendState();
		ReleasePixelShader();
		ReleaseVertexLayout();
		ReleaseVertexShader();
		return false;

	}
	
	return true;
}

void Lib::Vertex2D::Release()
{
	ReleaseConstantBuffer();
	ReleaseVertexBuffer();
	ReleaseSamplerState();
	ReleaseBlendState();
	ReleasePixelShader();
	ReleaseVertexLayout();
	ReleaseVertexShader();
}

void Lib::Vertex2D::Draw()
{
	m_pDeviceContext->VSSetShader(m_pVertexShader, NULL, 0);
	m_pDeviceContext->PSSetShader(m_pPixelShader, NULL, 0);

	m_pDeviceContext->VSSetConstantBuffers(0, 1, &m_pConstantBuffer);
	m_pDeviceContext->PSSetConstantBuffers(0, 1, &m_pConstantBuffer);

	m_pDeviceContext->IASetInputLayout(m_pVertexLayout);
	m_pDeviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);

	m_pDeviceContext->PSSetSamplers(0, 1, &m_pSamplerState);
	m_pDeviceContext->PSSetShaderResources(0, 1, &m_pTextureResourceView);

	m_pDeviceContext->OMSetBlendState(m_pBlendState, NULL, m_ColorMask);

	UINT Stride = sizeof(VERTEX);
	UINT Offset = 0;
	m_pDeviceContext->IASetVertexBuffers(0, 1, &m_pVertexBuffer, &Stride, &Offset);

	m_pDeviceContext->Draw(m_VertexNum, 0);
}

void Lib::Vertex2D::Draw(const D3DXVECTOR2* _pDrawPos, const D3DXVECTOR2* _pUV, float _alpha, const D3DXVECTOR2* _pScale, float _angle)
{
	VERTEX Vertex[] =
	{
		D3DXVECTOR3(static_cast<float>(m_RectSize.left), static_cast<float>(m_RectSize.top), 0.f),     D3DXVECTOR2(_pUV[0].x, _pUV[0].y),
		D3DXVECTOR3(static_cast<float>(m_RectSize.right), static_cast<float>(m_RectSize.top), 0.f),    D3DXVECTOR2(_pUV[1].x, _pUV[1].y),
		D3DXVECTOR3(static_cast<float>(m_RectSize.left), static_cast<float>(m_RectSize.bottom), 0.f),  D3DXVECTOR2(_pUV[2].x, _pUV[2].y),
		D3DXVECTOR3(static_cast<float>(m_RectSize.right), static_cast<float>(m_RectSize.bottom), 0.f), D3DXVECTOR2(_pUV[3].x, _pUV[3].y)
	};

	D3D11_BUFFER_DESC BufferDesc;
	ZeroMemory(&BufferDesc, sizeof(D3D11_BUFFER_DESC));
	BufferDesc.ByteWidth = sizeof(VERTEX) * m_VertexNum;
	BufferDesc.Usage = D3D11_USAGE_DEFAULT;
	BufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	BufferDesc.CPUAccessFlags = 0;
	BufferDesc.MiscFlags = 0;
	BufferDesc.StructureByteStride = 0;
	
	D3D11_SUBRESOURCE_DATA InitVertexData;
	ZeroMemory(&InitVertexData, sizeof(D3D11_SUBRESOURCE_DATA));
	InitVertexData.pSysMem = Vertex;
	if (FAILED(m_pDevice->CreateBuffer(&BufferDesc, &InitVertexData, &m_pVertexBuffer)))
	{
		OutputDebugString(TEXT("VertexBufferの生成に失敗しました"));
		return;
	}
	WriteConstantBuffer(_pDrawPos, &D3DXVECTOR2(_pScale->x, _pScale->y), &D3DXVECTOR2(0, 0), _angle, _alpha);

	m_pDeviceContext->VSSetShader(m_pVertexShader, NULL, 0);
	m_pDeviceContext->PSSetShader(m_pPixelShader, NULL, 0);

	m_pDeviceContext->VSSetConstantBuffers(0, 1, &m_pConstantBuffer);
	m_pDeviceContext->PSSetConstantBuffers(0, 1, &m_pConstantBuffer);

	m_pDeviceContext->IASetInputLayout(m_pVertexLayout);
	m_pDeviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);

	m_pDeviceContext->PSSetSamplers(0, 1, &m_pSamplerState);
	m_pDeviceContext->PSSetShaderResources(0, 1, &m_pTextureResourceView);
	
	m_pDeviceContext->OMSetBlendState(m_pBlendState, NULL, m_ColorMask);

	UINT Stride = sizeof(VERTEX);
	UINT Offset = 0;
	m_pDeviceContext->IASetVertexBuffers(0, 1, &m_pVertexBuffer, &Stride, &Offset);

	m_pDeviceContext->Draw(m_VertexNum, 0);
	ReleaseVertexBuffer();
}

void Lib::Vertex2D::Draw(const D3DXVECTOR2* _pDrawPos, const RECT* _pRectDiff, const D3DXVECTOR2* _pUV, float _alpha, const D3DXVECTOR2* _pScale, float _angle)
{
	VERTEX Vertex[] =
	{
		D3DXVECTOR3(static_cast<float>(m_RectSize.left + _pRectDiff->left), static_cast<float>(m_RectSize.top + _pRectDiff->top), 0.f), D3DXVECTOR2(_pUV[0].x, _pUV[0].y),
		D3DXVECTOR3(static_cast<float>(m_RectSize.right + _pRectDiff->right), static_cast<float>(m_RectSize.top + _pRectDiff->top), 0.f), D3DXVECTOR2(_pUV[1].x, _pUV[1].y),
		D3DXVECTOR3(static_cast<float>(m_RectSize.left + _pRectDiff->left), static_cast<float>(m_RectSize.bottom + _pRectDiff->bottom), 0.f), D3DXVECTOR2(_pUV[2].x, _pUV[2].y),
		D3DXVECTOR3(static_cast<float>(m_RectSize.right + _pRectDiff->right), static_cast<float>(m_RectSize.bottom + _pRectDiff->bottom), 0.f), D3DXVECTOR2(_pUV[3].x, _pUV[3].y)
	};

	D3D11_BUFFER_DESC BufferDesc;
	ZeroMemory(&BufferDesc, sizeof(D3D11_BUFFER_DESC));
	BufferDesc.ByteWidth = sizeof(VERTEX) * m_VertexNum;
	BufferDesc.Usage = D3D11_USAGE_DEFAULT;
	BufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	BufferDesc.CPUAccessFlags = 0;
	BufferDesc.MiscFlags = 0;
	BufferDesc.StructureByteStride = 0;

	D3D11_SUBRESOURCE_DATA InitVertexData;
	ZeroMemory(&InitVertexData, sizeof(D3D11_SUBRESOURCE_DATA));
	InitVertexData.pSysMem = Vertex;
	if (FAILED(m_pDevice->CreateBuffer(&BufferDesc, &InitVertexData, &m_pVertexBuffer)))
	{
		OutputDebugString(TEXT("VertexBufferの生成に失敗しました"));
		return;
	}
	WriteConstantBuffer(_pDrawPos, &D3DXVECTOR2(_pScale->x, _pScale->y), &D3DXVECTOR2(0, 0), _angle, _alpha);

	m_pDeviceContext->VSSetShader(m_pVertexShader, NULL, 0);
	m_pDeviceContext->PSSetShader(m_pPixelShader, NULL, 0);

	m_pDeviceContext->VSSetConstantBuffers(0, 1, &m_pConstantBuffer);
	m_pDeviceContext->PSSetConstantBuffers(0, 1, &m_pConstantBuffer);

	m_pDeviceContext->IASetInputLayout(m_pVertexLayout);
	m_pDeviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);

	m_pDeviceContext->PSSetSamplers(0, 1, &m_pSamplerState);
	m_pDeviceContext->PSSetShaderResources(0, 1, &m_pTextureResourceView);

	m_pDeviceContext->OMSetBlendState(m_pBlendState, NULL, m_ColorMask);

	UINT Stride = sizeof(VERTEX);
	UINT Offset = 0;
	m_pDeviceContext->IASetVertexBuffers(0, 1, &m_pVertexBuffer, &Stride, &Offset);

	m_pDeviceContext->Draw(m_VertexNum, 0);
	ReleaseVertexBuffer();
}


bool Lib::Vertex2D::WriteConstantBuffer(const D3DXVECTOR2* _pDrawPos, const D3DXVECTOR2* _pScale, const D3DXVECTOR2* _pTexScroll, float _angle, float _alpha)
{
	D3DXMATRIX MatWorld, MatTranslate, MatRotate;
	D3DXMatrixIdentity(&MatWorld);
	D3DXMatrixScaling(&MatWorld, _pScale->x, _pScale->y, 1.0f);
	D3DXMatrixRotationZ(&MatRotate, _angle);
	D3DXMatrixMultiply(&MatWorld, &MatWorld, &MatRotate);
	D3DXMatrixTranslation(&MatTranslate, _pDrawPos->x, _pDrawPos->y, 0);
	D3DXMatrixMultiply(&MatWorld, &MatWorld, &MatTranslate);

	D3D11_MAPPED_SUBRESOURCE MappedResource;
	SHADER_CONSTANT_BUFFER ConstantBuffer;
	if (SUCCEEDED(m_pDeviceContext->Map(m_pConstantBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &MappedResource)))
	{
		ConstantBuffer.MatWorld = MatWorld;
		D3DXMatrixTranspose(&ConstantBuffer.MatWorld, &ConstantBuffer.MatWorld);

		ConstantBuffer.WindowSize.x = m_ClientWidth;
		ConstantBuffer.WindowSize.y = m_ClientHeight;
		ConstantBuffer.TexScroll.x = _pTexScroll->x;
		ConstantBuffer.TexScroll.y = _pTexScroll->y;
		ConstantBuffer.Color.a = _alpha;

		memcpy_s(MappedResource.pData, MappedResource.RowPitch, reinterpret_cast<void*>(&ConstantBuffer), sizeof(ConstantBuffer));
		m_pDeviceContext->Unmap(m_pConstantBuffer, 0);

		return true;
	}

	return false;
}


//----------------------------------------------------------------------------------------------------
// Private Functions
//----------------------------------------------------------------------------------------------------

bool Lib::Vertex2D::InitVertexShader()
{
	ID3DBlob* pErrors = NULL;
	if (FAILED(D3DX11CompileFromFile(
		TEXT("Effect\\Vertex2D.fx"),
		NULL,
		NULL,
		"VS",
		"vs_5_0",
		D3D10_SHADER_DEBUG | D3D10_SHADER_SKIP_OPTIMIZATION,
		0,
		NULL,
		&m_pVertexCompiledShader,
		&pErrors,
		NULL)))
	{
		OutputDebugString(TEXT("VertexShaderのコンパイルに失敗"));
		pErrors->Release();
		return false;
	}

	m_pDevice->CreateVertexShader(
		m_pVertexCompiledShader->GetBufferPointer(),
		m_pVertexCompiledShader->GetBufferSize(),
		NULL,
		&m_pVertexShader);

	return true;
}

bool Lib::Vertex2D::InitVertexLayout()
{
	D3D11_INPUT_ELEMENT_DESC InputElementDesc[] =
	{
		{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0,					  D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT,	  0, sizeof(D3DXVECTOR3), D3D11_INPUT_PER_VERTEX_DATA, 0 },
	};

	if (FAILED(m_pDevice->CreateInputLayout(
		InputElementDesc,
		sizeof(InputElementDesc) / sizeof(InputElementDesc[0]),
		m_pVertexCompiledShader->GetBufferPointer(),
		m_pVertexCompiledShader->GetBufferSize(),
		&m_pVertexLayout)))
	{
		OutputDebugString(TEXT("CreateInputLayoutに失敗"));
		return false;
	}

	return true;
}

bool Lib::Vertex2D::InitPixelShader()
{
	ID3DBlob* pCompiledShader = NULL;
	ID3DBlob* pErrors = NULL;
	if (FAILED(D3DX11CompileFromFile(
		TEXT("Effect\\Vertex2D.fx"),
		NULL,
		NULL,
		"PS",
		"ps_5_0",
		D3D10_SHADER_DEBUG | D3D10_SHADER_SKIP_OPTIMIZATION,
		0,
		NULL,
		&pCompiledShader,
		&pErrors,
		NULL)))
	{
		OutputDebugString(TEXT("PixelShaderのコンパイルに失敗"));
		pErrors->Release();
		return false;
	}

	m_pDevice->CreatePixelShader(
		pCompiledShader->GetBufferPointer(), 
		pCompiledShader->GetBufferSize(), 
		NULL, 
		&m_pPixelShader);
	
	pCompiledShader->Release();

	return true;
}

bool Lib::Vertex2D::InitBlendState()
{
	D3D11_BLEND_DESC BlendDesc;
	ZeroMemory(&BlendDesc, sizeof(D3D11_BLEND_DESC));
	BlendDesc.AlphaToCoverageEnable = false;
	BlendDesc.IndependentBlendEnable = false;
	BlendDesc.RenderTarget[0].BlendEnable = true;
	BlendDesc.RenderTarget[0].SrcBlend = D3D11_BLEND_SRC_ALPHA;
	BlendDesc.RenderTarget[0].DestBlend = D3D11_BLEND_INV_SRC_ALPHA;
	BlendDesc.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;
	BlendDesc.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_ONE;
	BlendDesc.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_ZERO;
	BlendDesc.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_ADD;
	BlendDesc.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;

	if (FAILED(m_pDevice->CreateBlendState(&BlendDesc, &m_pBlendState)))
	{
		OutputDebugString(TEXT("CreateBlendStateに失敗しました"));
		return false;
	}

	return true;
}

bool Lib::Vertex2D::InitSamplerState()
{
	D3D11_SAMPLER_DESC SamplerDesc;
	ZeroMemory(&SamplerDesc, sizeof(D3D11_SAMPLER_DESC));
	SamplerDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
	SamplerDesc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
	SamplerDesc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
	SamplerDesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;

	if (FAILED(m_pDevice->CreateSamplerState(&SamplerDesc, &m_pSamplerState)))
	{
		OutputDebugString(TEXT("CreateSamplerStateに失敗しました"));
		return false;
	}

	return true;
}

bool Lib::Vertex2D::InitVertexBuffer(const D3DXVECTOR2* _pRectSize, const D3DXVECTOR2* _pUV)
{
	m_RectSize.top = static_cast<LONG>(-_pRectSize->y / 2);
	m_RectSize.bottom = static_cast<LONG>(_pRectSize->y / 2);
	m_RectSize.left = static_cast<LONG>(-_pRectSize->x / 2);
	m_RectSize.right = static_cast<LONG>(_pRectSize->x / 2);

	VERTEX Vertex[] =
	{
		D3DXVECTOR3(static_cast<float>(m_RectSize.left), static_cast<float>(m_RectSize.top), 0.f), D3DXVECTOR2(_pUV[0].x, _pUV[0].y),
		D3DXVECTOR3(static_cast<float>(m_RectSize.right), static_cast<float>(m_RectSize.top), 0.f), D3DXVECTOR2(_pUV[1].x, _pUV[1].y),
		D3DXVECTOR3(static_cast<float>(m_RectSize.left), static_cast<float>(m_RectSize.bottom), 0.f), D3DXVECTOR2(_pUV[2].x, _pUV[2].y),
		D3DXVECTOR3(static_cast<float>(m_RectSize.right), static_cast<float>(m_RectSize.bottom), 0.f), D3DXVECTOR2(_pUV[3].x, _pUV[3].y)
	};

	D3D11_BUFFER_DESC BufferDesc;
	ZeroMemory(&BufferDesc, sizeof(D3D11_BUFFER_DESC));
	BufferDesc.ByteWidth = sizeof(VERTEX) * m_VertexNum;
	BufferDesc.Usage = D3D11_USAGE_DEFAULT;
	BufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	BufferDesc.CPUAccessFlags = 0;
	BufferDesc.MiscFlags = 0;
	BufferDesc.StructureByteStride = 0;

	D3D11_SUBRESOURCE_DATA InitVertexData;
	ZeroMemory(&InitVertexData, sizeof(D3D11_SUBRESOURCE_DATA));
	InitVertexData.pSysMem = Vertex;
	if (FAILED(m_pDevice->CreateBuffer(&BufferDesc, &InitVertexData, &m_pVertexBuffer)))
	{
		OutputDebugString(TEXT("VertexBufferの生成に失敗しました"));
		return false;
	}

	return true;
}

bool Lib::Vertex2D::InitConstantBuffer()
{
	D3D11_BUFFER_DESC ConstantBufferDesc;
	ZeroMemory(&ConstantBufferDesc, sizeof(D3D11_BUFFER_DESC));
	ConstantBufferDesc.ByteWidth = sizeof(SHADER_CONSTANT_BUFFER);
	ConstantBufferDesc.Usage = D3D11_USAGE_DYNAMIC;
	ConstantBufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	ConstantBufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	ConstantBufferDesc.MiscFlags = 0;
	ConstantBufferDesc.StructureByteStride = 0;

	if (FAILED(m_pDevice->CreateBuffer(&ConstantBufferDesc, NULL, &m_pConstantBuffer)))
	{
		OutputDebugString(TEXT("ConstantBufferの生成に失敗しました"));
		return false;
	}

	return true;
}

void Lib::Vertex2D::ReleaseVertexShader()
{
	if (m_pVertexShader != NULL)
	{
		m_pVertexShader->Release();
		m_pVertexShader = NULL;
	}

	if (m_pVertexCompiledShader != NULL)
	{
		m_pVertexCompiledShader->Release();
		m_pVertexCompiledShader = NULL;
	}
}

void Lib::Vertex2D::ReleaseVertexLayout()
{
	if (m_pVertexLayout != NULL)
	{
		m_pVertexLayout->Release();
		m_pVertexLayout = NULL;
	}
}

void Lib::Vertex2D::ReleasePixelShader()
{
	if (m_pPixelShader != NULL)
	{
		m_pPixelShader->Release();
		m_pPixelShader = NULL;
	}
}

void Lib::Vertex2D::ReleaseBlendState()
{
	if (m_pBlendState != NULL)
	{
		m_pBlendState->Release();
		m_pBlendState = NULL;
	}
}

void Lib::Vertex2D::ReleaseSamplerState()
{
	if (m_pSamplerState != NULL)
	{
		m_pSamplerState->Release();
		m_pSamplerState = NULL;
	}
}

void Lib::Vertex2D::ReleaseVertexBuffer()
{
	if (m_pVertexBuffer != NULL)
	{
		m_pVertexBuffer->Release();
		m_pVertexBuffer = NULL;
	}
}

void Lib::Vertex2D::ReleaseConstantBuffer()
{
	if (m_pConstantBuffer != NULL)
	{
		m_pConstantBuffer->Release();
		m_pConstantBuffer = NULL;
	}
}
