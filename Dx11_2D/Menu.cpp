#include "stdafx.h"
#include "Menu.h"

Menu::Menu()
{
	g_pTextureManager->AddTexture(L"GameText", L"GameText", L"GameText.png", L"Sprite", L"Sprite2.hlsl");
}


Menu::~Menu()
{
	for (int i = 0; i < menu.size(); i++) SAFE_DELETE(menu[i]);
	menu.clear();
}

void Menu::Init()
{
	selectFrame[4] = new Sprite(L"GameText", RECT{ 142, 190, 152 ,200 });
	selectFrame[4]->SetScale(57, 75);
	selectFrame[4]->SetPos(WINSIZEX - 250, WINSIZEY - 220);
	menu.push_back(selectFrame[4]);

	//RECT L T R B
	selectFrame[0] = new Sprite(L"GameText", RECT{ 128, 176, 136 ,185 });
	selectFrame[0]->SetScale(2, 2);
	selectFrame[0]->SetPos(WINSIZEX - 450, WINSIZEY - 20);
	menu.push_back(selectFrame[0]);

	for (int i = 1; i <= 30; i++) {
		selectFrame[1] = new Sprite(L"GameText", RECT{ 142, 176, 152 ,185 });
		selectFrame[1]->SetScale(2, 2);
		selectFrame[1]->SetPos(WINSIZEX - 450 + i * 13, WINSIZEY - 20);
		menu.push_back(selectFrame[1]);
	}

	selectFrame[2] = new Sprite(L"GameText", RECT{ 158, 176, 166 ,185 });
	selectFrame[2]->SetScale(2, 2);
	selectFrame[2]->SetPos(1233, WINSIZEY - 20);
	menu.push_back(selectFrame[2]);

	for (int i = 1; i <= 41; i++) {
		selectFrame[3] = new Sprite(L"GameText", RECT{ 128, 190, 136 ,200 });
		selectFrame[3]->SetScale(2, 2);
		selectFrame[3]->SetPos(WINSIZEX - 450, (WINSIZEY - 20) - i * 13);
		menu.push_back(selectFrame[3]);
	}

	for (int i = 1; i <= 41; i++) {
		selectFrame[5] = new Sprite(L"GameText", RECT{ 158, 190, 166 ,200 });
		selectFrame[5]->SetScale(2, 2);
		selectFrame[5]->SetPos(1233, (WINSIZEY - 20) - i * 13);
		menu.push_back(selectFrame[5]);
	}

	selectFrame[6] = new Sprite(L"GameText", RECT{ 128, 207, 136 ,215 });
	selectFrame[6]->SetScale(2, 2);
	selectFrame[6]->SetPos(WINSIZEX - 450, 160);
	menu.push_back(selectFrame[6]);

	for (int i = 1; i <= 30; i++) {
		selectFrame[7] = new Sprite(L"GameText", RECT{ 142, 207, 152 ,215 });
		selectFrame[7]->SetScale(2, 2);
		selectFrame[7]->SetPos(WINSIZEX - 450 + i * 13, 160);
		menu.push_back(selectFrame[7]);
	}

	selectFrame[8] = new Sprite(L"GameText", RECT{ 158, 207, 166 ,215 });
	selectFrame[8]->SetScale(2, 2);
	selectFrame[8]->SetPos(1233, 160);
	menu.push_back(selectFrame[8]);

	menuNum = 1;
	menuOn = true;
}

void Menu::Update()
{
	if (g_pKeyManger->isOnceKeyDown(VK_UP)) {

	}
	else if (g_pKeyManger->isOnceKeyDown(VK_DOWN)) {

	}
	else if (g_pKeyManger->isOnceKeyDown('Z')) {

	}
	else if (g_pKeyManger->isOnceKeyDown('X')) {
		menuOn = false;
		for (int i = 0; i < menu.size(); i++) SAFE_DELETE(menu[i]);
		menu.clear();
	}

	for (int i = 0; i < menu.size(); i++) menu[i]->Update();
}

void Menu::Render()
{
	for (int i = 0; i < menu.size(); i++) menu[i]->Render();
}
