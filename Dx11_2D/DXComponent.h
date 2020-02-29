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

// Dx11 전역 변수
extern IDXGISwapChain* g_pSwapChain;
extern ID3D11Device* g_pDevice;
extern ID3D11DeviceContext* g_pDeviceContext;
extern ID3D11RenderTargetView* g_pRTV;

struct tagVPMatrix
{
	D3DXMATRIX View;
	D3DXMATRIX Projection;
};

