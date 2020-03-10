#pragma once
// DXComponent
#include <d3d11.h>
#include <d3dx11.h>
#include <d3dX10.h>
#include <d3dx10math.h>

#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "d3dx11.lib")
#pragma comment(lib, "d3dx10.lib")

#include "Shader.h"

// Dx11 ���� ����
extern IDXGISwapChain* g_pSwapChain;
extern ID3D11Device* g_pDevice;
extern ID3D11DeviceContext* g_pDeviceContext;
extern ID3D11RenderTargetView* g_pRTV;

struct tagVPMatrix
{
	D3DXMATRIX View;
	D3DXMATRIX Projection;
};

// ������ ����, Į�� ������ ���� ���ؽ� ����ü
const struct PTVertex
{
	D3DXVECTOR3	Position;
	D3DXVECTOR2	Texture;

	PTVertex() {}
	PTVertex(D3DXVECTOR3 p, D3DXVECTOR2 t) : Position(p), Texture(t) {}
};

// === ���� ���� �Լ��� ===================================================
// Create Constant Buffer
inline void CreateConstantBuffer(ID3D11Buffer** ppBuffer, UINT ByteWidth, const void *pSystem)
{
	D3D11_BUFFER_DESC desc = { 0, };
	desc.Usage = D3D11_USAGE_DEFAULT;
	desc.ByteWidth = ByteWidth;
	desc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;

	D3D11_SUBRESOURCE_DATA data = { 0, };
	data.pSysMem = pSystem;

	HRESULT hr = g_pDevice->CreateBuffer(&desc, &data, ppBuffer);
	assert(SUCCEEDED(hr));
}
// ���ؽ� ����
inline void CreateVertexBuffer(ID3D11Buffer** ppBuffer, UINT ByteWidth, const void *pSystem)
{
	D3D11_BUFFER_DESC desc = { 0, };
	desc.Usage = D3D11_USAGE_IMMUTABLE;
	desc.ByteWidth = ByteWidth;
	desc.BindFlags = D3D11_BIND_VERTEX_BUFFER;

	D3D11_SUBRESOURCE_DATA data = { 0, };
	data.pSysMem = pSystem;

	HRESULT hr = g_pDevice->CreateBuffer(&desc, &data, ppBuffer);
	assert(SUCCEEDED(hr));
}
// �ε��� ����
inline void CreateIndexBuffer(ID3D11Buffer** ppBuffer, UINT ByteWidth, const void *pSystem)
{
	D3D11_BUFFER_DESC desc = { 0, };
	desc.Usage = D3D11_USAGE_IMMUTABLE;
	desc.ByteWidth = ByteWidth;
	desc.BindFlags = D3D11_BIND_INDEX_BUFFER;

	D3D11_SUBRESOURCE_DATA data = { 0, };
	data.pSysMem = pSystem;

	HRESULT hr = g_pDevice->CreateBuffer(&desc, &data, ppBuffer);
	assert(SUCCEEDED(hr));
}