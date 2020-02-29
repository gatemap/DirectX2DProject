#include "stdafx.h"
#include "Pikachu.h"


Pikachu::Pikachu()
{
	g_pTextureManager->AddTexture(L"PikachuEmotion", L"PikachuEmotion", L"Pikachu.png", L"Sprite", L"Sprite2.hlsl");
	g_pTextureManager->AddTexture(L"Pikachu", L"Pikachu", L"Map/Pallet Town.png", L"Sprite", L"Sprite2.hlsl");
}


Pikachu::~Pikachu()
{
	SAFE_DELETE(pEmotion);
	SAFE_DELETE(p);
}

void Pikachu::EmotionInit()
{
	pEmotion = new Animation<PikachuEmotion>;
	Clip* c;
	//Sulk(»ßÁü)
	c = new Clip(PlayMode::Once);
	c->AddFrame(new Sprite(L"PikachuEmotion", 2, 0, 6, 6), 2.f);
	c->AddFrame(new Sprite(L"PikachuEmotion", 3, 0, 6, 6), 4.f);
	pEmotion->AddClip(PikachuEmotion::Sulk, c);
	//Sad
	c = new Clip;
	c->AddFrame(new Sprite(L"PikachuEmotion", 4, 0, 6, 6), 1.f);
	c->AddFrame(new Sprite(L"PikachuEmotion", 5, 0, 6, 6), 1.f);
	pEmotion->AddClip(PikachuEmotion::Sad, c);
	//Upset
	c = new Clip;
	c->AddFrame(new Sprite(L"PikachuEmotion", 0, 1, 6, 6), 1.f / 2.f);
	c->AddFrame(new Sprite(L"PikachuEmotion", 1, 1, 6, 6), 1.f / 2.f);
	pEmotion->AddClip(PikachuEmotion::Upset, c);
	//Normal
	c = new Clip;
	c->AddFrame(new Sprite(L"PikachuEmotion", 0, 2, 6, 6), 1.f);
	c->AddFrame(new Sprite(L"PikachuEmotion", 1, 2, 6, 6), 1.f);
	pEmotion->AddClip(PikachuEmotion::Normal, c);
	//HappyLv1
	c = new Clip;
	c->AddFrame(new Sprite(L"PikachuEmotion", 2, 1, 6, 6), 1.f);
	c->AddFrame(new Sprite(L"PikachuEmotion", 3, 1, 6, 6), 1.f);
	pEmotion->AddClip(PikachuEmotion::HappyLv1, c);
	//HappyLv2
	c = new Clip;
	c->AddFrame(new Sprite(L"PikachuEmotion", 4, 2, 6, 6), 1.f);
	c->AddFrame(new Sprite(L"PikachuEmotion", 5, 2, 6, 6), 1.f);
	pEmotion->AddClip(PikachuEmotion::HappyLv2, c);
	//HappyLv3
	c = new Clip(PlayMode::Once);
	c->AddFrame(new Sprite(L"PikachuEmotion", 4, 3, 6, 6), 2.f);
	c->AddFrame(new Sprite(L"PikachuEmotion", 5, 3, 6, 6), 4.f);
	pEmotion->AddClip(PikachuEmotion::HappyLv3, c);
	//Sleep
	c = new Clip;
	c->AddFrame(new Sprite(L"PikachuEmotion", 0, 3, 6, 6), 1.f / 2.f);
	c->AddFrame(new Sprite(L"PikachuEmotion", 1, 3, 6, 6), 1.f / 2.f);
	pEmotion->AddClip(PikachuEmotion::Sleep, c);
	//Awake
	c = new Clip(PlayMode::Once);
	c->AddFrame(new Sprite(L"PikachuEmotion", 2, 3, 6, 6), 2.f);
	c->AddFrame(new Sprite(L"PikachuEmotion", 3, 3, 6, 6), 4.f);
	pEmotion->AddClip(PikachuEmotion::Awake, c);
	//Wonder
	c = new Clip;
	c->AddFrame(new Sprite(L"PikachuEmotion", 2, 2, 6, 6), 1.f / 2.f);
	c->AddFrame(new Sprite(L"PikachuEmotion", 3, 2, 6, 6), 1.f / 2.f);
	pEmotion->AddClip(PikachuEmotion::Wonder, c);
	//Surprised
	c = new Clip(PlayMode::Once);
	c->AddFrame(new Sprite(L"PikachuEmotion", 3, 4, 6, 6), 2.f);
	c->AddFrame(new Sprite(L"PikachuEmotion", 4, 4, 6, 6), 4.f);
	pEmotion->AddClip(PikachuEmotion::Surprised, c);

	pEmotion->SetRateScale(10.f, 10.f);
	pEmotion->SetPos(INITX, INITY);
	pEmotion->Play(PikachuEmotion::Upset);
}

void Pikachu::Init()
{
	p = new Animation<PikachuState>;
	Clip * c;

	//Up
	c = new Clip;
	for (int i = 16; i < 19; i++)	c->AddFrame(new Sprite(L"Pikachu", i, 33, 25, 35), 1.f);
	p->AddClip(PikachuState::Up, c);
	//BackIdle
	c = new Clip;
	c->AddFrame(new Sprite(L"Pikachu", 17, 33, 25, 35), 1.f);
	p->AddClip(PikachuState::BackIdle, c);
	//Down
	c = new Clip;
	for (int i = 16; i < 19; i++)	c->AddFrame(new Sprite(L"Pikachu", i, 32, 25, 35), 1.f);
	p->AddClip(PikachuState::Down, c);
	//FaceIdle
	c = new Clip;
	c->AddFrame(new Sprite(L"Pikachu", 17, 32, 25, 35), 1.f);
	p->AddClip(PikachuState::FaceIdle, c);
	//LEFT
	c = new Clip;
	for (int i = 16; i < 19; i++)	c->AddFrame(new Sprite(L"Pikachu", i, 30, 25, 35), 1.f);
	p->AddClip(PikachuState::Left, c);
	//LeftIdle
	c = new Clip;
	c->AddFrame(new Sprite(L"Pikachu", 17, 30, 25, 35), 1.f);
	p->AddClip(PikachuState::LeftIdle, c);
	//Right
	c = new Clip;
	for (int i = 16; i < 19; i++)	c->AddFrame(new Sprite(L"Pikachu", i, 31, 25, 35), 1.f);
	p->AddClip(PikachuState::Right, c);
	//RightIdle
	c = new Clip;
	c->AddFrame(new Sprite(L"Pikachu", 17, 31, 25, 35), 1.f);
	p->AddClip(PikachuState::RightIdle, c);

	scaleRate.x = 8.f, scaleRate.y = 8.f;
	p->SetRateScale(scaleRate.x, scaleRate.y);
	pos.x = player->GetPlayerPos().x, pos.y = player->GetPlayerPos().y - 50.f;
	p->SetPos(pos.x, pos.y);
}

void Pikachu::Update()
{
	if (g_pKeyManger->isStayKeyDown(VK_UP)) {
		p->Play(PikachuState::Up);
		if (player->GetPlayerCollision() != PlayerCollision::UpCollision)
			pos.y -= player->GetPlayerSpeed()*g_pTimeManager->GetDeltaTime();
	}
	else if (g_pKeyManger->isStayKeyDown(VK_DOWN)) {
		p->Play(PikachuState::Down);
		if (player->GetPlayerCollision() != PlayerCollision::DownCollision)
			pos.y += player->GetPlayerSpeed()*g_pTimeManager->GetDeltaTime();

	}
	else if (g_pKeyManger->isStayKeyDown(VK_LEFT)) {
		p->Play(PikachuState::Left);
		if (player->GetPlayerCollision() != PlayerCollision::LeftCollision)
			pos.x -= player->GetPlayerSpeed()*g_pTimeManager->GetDeltaTime();
	}
	else if (g_pKeyManger->isStayKeyDown(VK_RIGHT)) {
		p->Play(PikachuState::Right);
		if (player->GetPlayerCollision() != PlayerCollision::RightCollision)
			pos.x += player->GetPlayerSpeed()*g_pTimeManager->GetDeltaTime();
	}

	if (g_pKeyManger->isOnceKeyUp(VK_UP)) p->Play(PikachuState::BackIdle);
	else if(g_pKeyManger->isOnceKeyDown(VK_DOWN)) p->Play(PikachuState::FaceIdle);
	else if (g_pKeyManger->isOnceKeyDown(VK_LEFT)) p->Play(PikachuState::LeftIdle);
	else if (g_pKeyManger->isOnceKeyDown(VK_RIGHT)) p->Play(PikachuState::RightIdle);

	p->SetPos(pos.x, pos.y);
	p->Update();
	if (pEmotion) pEmotion->Update();
}

void Pikachu::Render()
{
	p->Render();
	if (pEmotion) pEmotion->Render();
}
