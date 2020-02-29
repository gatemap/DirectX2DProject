#include "stdafx.h"
#include "MainGame.h"

MainGame::MainGame()
{
	// Create VPBuffer
	{
		D3D11_BUFFER_DESC desc = { 0, };
		desc.Usage = D3D11_USAGE_DEFAULT;
		desc.ByteWidth = sizeof(tagVPMatrix);
		desc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;

		HRESULT hr = g_pDevice->CreateBuffer(&desc, NULL, &m_pVPBuffer);
		assert(SUCCEEDED(hr));
	}

	// Matrix Setting
	{
		m_pVPMatrix = new tagVPMatrix;

		// View
		D3DXVECTOR3 eye(0, 0, -1);
		D3DXVECTOR3 lookAt(0, 0, 0);
		D3DXVECTOR3 up(0, 1, 0);
		D3DXMatrixLookAtLH(&m_pVPMatrix->View, &eye, &lookAt, &up);
		D3DXMatrixTranspose(&m_pVPMatrix->View, &m_pVPMatrix->View);

		// Projection
		D3DXMatrixOrthoOffCenterLH(&m_pVPMatrix->Projection, 0, (float)WINSIZEX, 0, (float)WINSIZEY, -1, 1);
		D3DXMatrixTranspose(&m_pVPMatrix->Projection, &m_pVPMatrix->Projection);
	}

	// 喉坊靛 可记 积己
	{
		D3D11_BLEND_DESC desc;
		ZeroMemory(&desc, sizeof(D3D11_BLEND_DESC));

		desc.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;
		g_pDevice->CreateBlendState(&desc, &m_pNormalBlendState);

		desc.RenderTarget[0].BlendEnable = true;
		desc.RenderTarget[0].DestBlend = D3D11_BLEND_INV_SRC_ALPHA;
		desc.RenderTarget[0].SrcBlend = D3D11_BLEND_SRC_ALPHA;
		desc.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;
		desc.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_ZERO;
		desc.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_ZERO;
		desc.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_ADD;
		g_pDevice->CreateBlendState(&desc, &m_pAlphaBlendState);
	}

	p = new PlaySetting;

	Init();
}


MainGame::~MainGame()
{
	SAFE_DELETE(p);

	SAFE_RELEASE(m_pVPBuffer);
	SAFE_DELETE(m_pVPMatrix);
}

void MainGame::Init()
{
	if (p) p->Init();

	g_pSoundManager->Play("bgm");

}

void MainGame::Update()
{
	if (p) p->Update();
}

void MainGame::Render()
{
	D3DXCOLOR background = D3DXCOLOR(0, 0, 0, 1);
	g_pDeviceContext->ClearRenderTargetView(g_pRTV, (float *)background);
	{
		// Set VPMatrix Buffer
		g_pDeviceContext->UpdateSubresource(m_pVPBuffer, 0, NULL, m_pVPMatrix, 0, 0);
		g_pDeviceContext->VSSetConstantBuffers(0, 1, &m_pVPBuffer);
	}

	g_pDeviceContext->OMSetBlendState(m_pAlphaBlendState, NULL, 0xFF);

	if (p) p->Render();

	g_pDeviceContext->OMSetBlendState(m_pNormalBlendState, NULL, 0xFF);

	// ImGUI 坊歹
	g_pTimeManager->Render();

	ImGui::Render();
	g_pSwapChain->Present(0, 0);
}