#include "stdafx.h"
#include "MainGame.h"

MainGame::MainGame()
{
	gm = new GameManager;

	Init();
}

MainGame::~MainGame()
{
	SAFE_DELETE(gm);
}

void MainGame::Init()
{
	if (gm) gm->Init();
}

void MainGame::Update()
{
	if (gm) gm->Update();
}

void MainGame::Render()
{	
	if (gm) gm->Render();
	// ImGUI ·»´õ
	g_pTimeManager->Render();

	ImGui::Render();
	g_pSwapChain->Present(0, 0);
}