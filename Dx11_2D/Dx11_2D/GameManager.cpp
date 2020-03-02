#include "stdafx.h"
#include "GameManager.h"

GameManager::GameManager()
{
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
}

GameManager::~GameManager()
{
	SAFE_DELETE(p);

	g_pCamera->ReleaseInstance();
}

void GameManager::Init()
{
	g_pCamera->Init();

	if (p) p->Init();

	//g_pSoundManager->Play("bgm");
}

void GameManager::Update()
{
	g_pCamera->Update();
	if (p) p->Update();
}

void GameManager::Render()
{
	D3DXCOLOR background = D3DXCOLOR(0, 0, 0, 1);
	g_pDeviceContext->ClearRenderTargetView(g_pRTV, (float *)background);

	g_pDeviceContext->OMSetBlendState(m_pAlphaBlendState, NULL, 0xFF);
	
	if (p) p->Render();

	g_pDeviceContext->OMSetBlendState(m_pNormalBlendState, NULL, 0xFF);
}