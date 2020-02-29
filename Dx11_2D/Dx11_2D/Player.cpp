#include "stdafx.h"
#include "Player.h"

Player::Player()
{
	g_pTextureManager->AddTexture(L"Player", L"Player", L"Map/Pallet Town.png", L"Sprite", L"Sprite2.hlsl");
}

Player::~Player()
{
	SAFE_DELETE(p);
}

void Player::Init()
{
	p = new Animation<PlayerState>;
	Clip* c;

	//Up
	c = new Clip;
	c->AddFrame(new Sprite(L"Player", 10, 28, 25, 35), 1.f / 4.f);
	c->AddFrame(new Sprite(L"Player", 12, 28, 25, 35), 1.f / 4.f);
	p->AddClip(PlayerState::Up, c);
	//BackIdle
	c = new Clip;
	c->AddFrame(new Sprite(L"Player", 11, 28, 25, 35), 1.f);
	p->AddClip(PlayerState::BackIdle, c);
	//Down
	c = new Clip;
	c->AddFrame(new Sprite(L"Player", 10, 27, 25, 35), 1.f / 4.f);
	c->AddFrame(new Sprite(L"Player", 12, 27, 25, 35), 1.f / 4.f);
	p->AddClip(PlayerState::Down, c);
	//FaceIdle
	c = new Clip;
	c->AddFrame(new Sprite(L"Player", 11, 27, 25, 35), 1.f);
	p->AddClip(PlayerState::FaceIdle, c);
	//LEFT
	c = new Clip;
	c->AddFrame(new Sprite(L"Player", 10, 25, 25, 35), 1.f / 4.f);
	c->AddFrame(new Sprite(L"Player", 11, 25, 25, 35), 1.f / 4.f);
	p->AddClip(PlayerState::Left, c);
	//LeftIdle
	c = new Clip;
	c->AddFrame(new Sprite(L"Player", 11, 25, 25, 35), 1.f);
	p->AddClip(PlayerState::LeftIdle, c);
	//Right
	c = new Clip;
	c->AddFrame(new Sprite(L"Player", 10, 26, 25, 35), 1.f / 4.f);
	c->AddFrame(new Sprite(L"Player", 11, 26, 25, 35), 1.f / 4.f);
	p->AddClip(PlayerState::Right, c);
	//RightIdle
	c = new Clip;
	c->AddFrame(new Sprite(L"Player", 11, 26, 25, 35), 1.f);
	p->AddClip(PlayerState::RightIdle, c);

	pos.x = 400, pos.y = 300;
	scaleRate.x = 7.f, scaleRate.y = 7.f;
	p->SetRateScale(scaleRate.x, scaleRate.y);
	p->SetPos(pos.x, pos.y);
	money = 0;
	speed = SPEED;
	menuOn = false;
	collisionCheck = PlayerCollision::Normal;

	tmpR = new Rect;
	tmpR->SetPos(pos.x, pos.y);

	p->Play(PlayerState::FaceIdle);
}

void Player::Update()
{
	if (g_pKeyManger->isStayKeyDown(VK_UP) && !menu) {
		p->Play(PlayerState::Up);
		pos.y += speed * g_pTimeManager->GetDeltaTime();
		if (pos.y + fabs(p->GetSize().y*0.5) > WINSIZEY || collisionCheck == PlayerCollision::UpCollision)
			pos.y -= (speed-5) * g_pTimeManager->GetDeltaTime();
	}
	else if (g_pKeyManger->isStayKeyDown(VK_DOWN) && !menu) {
		p->Play(PlayerState::Down);
		pos.y -= speed * g_pTimeManager->GetDeltaTime();
		if (pos.y - fabs(p->GetSize().y*0.5) < 0 || collisionCheck == PlayerCollision::DownCollision)
			pos.y += (speed + 5) * g_pTimeManager->GetDeltaTime();
	}
	else if (g_pKeyManger->isStayKeyDown(VK_LEFT) && !menu) {
		p->Play(PlayerState::Left);
		pos.x -= speed * g_pTimeManager->GetDeltaTime();
		if (pos.x - (fabs(p->GetSize().x)*0.5) < 0 || collisionCheck == PlayerCollision::LeftCollision)
			pos.x += (speed + 5) * g_pTimeManager->GetDeltaTime();
	}
	else if (g_pKeyManger->isStayKeyDown(VK_RIGHT) && !menu) {
		p->Play(PlayerState::Right);
		pos.x += speed * g_pTimeManager->GetDeltaTime();
		if (pos.x + (fabs(p->GetSize().x)*0.5) > WINSIZEX || collisionCheck == PlayerCollision::RightCollision)
			pos.x -= (speed - 5) * g_pTimeManager->GetDeltaTime();
	}
	else if (g_pKeyManger->isStayKeyDown(VK_RETURN)) {
		menuOn = true;
		if (menuOn) {
			menu = new Menu;
			menu->Init();
		}
	}

	if (g_pKeyManger->isOnceKeyDown(VK_UP) && !menu) {
		p->Play(PlayerState::BackIdle);
	}
	else if (g_pKeyManger->isOnceKeyDown(VK_DOWN) && !menu) {
		p->Play(PlayerState::FaceIdle);
	}
	else if (g_pKeyManger->isOnceKeyDown(VK_LEFT) && !menu) {
		p->Play(PlayerState::LeftIdle);
	}
	else if (g_pKeyManger->isOnceKeyDown(VK_RIGHT) && !menu) {
		p->Play(PlayerState::RightIdle);
	}

	if (g_pKeyManger->isOnceKeyUp(VK_UP) && !menu) {
		p->Play(PlayerState::BackIdle);
	}
	else if (g_pKeyManger->isOnceKeyUp(VK_DOWN) && !menu) {
		p->Play(PlayerState::FaceIdle);
	}
	else if (g_pKeyManger->isOnceKeyUp(VK_LEFT) && !menu) {
		p->Play(PlayerState::LeftIdle);
	}
	else if (g_pKeyManger->isOnceKeyUp(VK_RIGHT) && !menu) {
		p->Play(PlayerState::RightIdle);
	}

	scale.x = p->GetSize().x, scale.y = p->GetSize().y;

	p->SetPos(pos.x, pos.y);
	p->Update();

	tmpR->SetScale(scale.x - 50, scale.y - 50);
	tmpR->SetPos(pos.x, pos.y);
	tmpR->Update();
	if (menu)
	{
		menu->Update();
		if (!menu->GetMenuOn())
		{
			menuOn = false;
			SAFE_DELETE(menu);
		}
	}
}

void Player::Render()
{
	p->Render();
	//tmpR->Render_Border();
	if (menu) menu->Render();
}