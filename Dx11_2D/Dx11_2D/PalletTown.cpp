#include "stdafx.h"
#include "PalletTown.h"

PalletTown::PalletTown()
{
	g_pTextureManager->AddTexture(L"start", L"start", L"Map/Pallet Town.png", L"Sprite", L"Sprite2.hlsl");
}

PalletTown::~PalletTown()
{
	SAFE_DELETE(palletTown[Pallet::hRoom].s);
	SAFE_DELETE(palletTown[Pallet::hLiving].s);
	SAFE_DELETE(palletTown[Pallet::PalletTown].s);
	SAFE_DELETE(palletTown[Pallet::rivalHouse].s);
	SAFE_DELETE(palletTown[Pallet::OLab].s);
}

void PalletTown::HRoomInit()
{
	//주인공 방
	tagMapType stMap;

	stMap.s = new Sprite(L"start", RECT{ 32, 8, 160, 136 });	// L T R B
	stMap.scale.x = WINSIZEX, stMap.scale.y = WINSIZEY;
	stMap.pos.x = INITX, stMap.pos.y = INITY;
	stMap.s->SetConstantScale(stMap.scale.x, stMap.scale.y);
	stMap.s->SetPos(stMap.pos.x, stMap.pos.y);
	stMap.bikeRide = false;
	{	//object 영역 생성
		//컴퓨터
		stMap.stObj.r = new Rect;
		stMap.stObj.r->SetScale(160, 230);
		stMap.stObj.pos.x = 80, stMap.stObj.pos.y = WINSIZEY - 70;
		stMap.stObj.r->SetPos(stMap.stObj.pos.x, stMap.stObj.pos.y);
		stMap.stObj.explain = true;
		stMap.obj.push_back(stMap.stObj);

		//책상
		stMap.stObj.r = new Rect;
		stMap.stObj.r->SetScale(340, 100);
		stMap.stObj.pos.x = 310, stMap.stObj.pos.y = WINSIZEY - 120;
		stMap.stObj.r->SetPos(stMap.stObj.pos.x, stMap.stObj.pos.y);
		stMap.obj.push_back(stMap.stObj);

		//침대
		stMap.stObj.r = new Rect;
		stMap.stObj.r->SetScale(140, 200);
		stMap.stObj.pos.x = 80, stMap.stObj.pos.y = 80;
		stMap.stObj.r->SetPos(stMap.stObj.pos.x, stMap.stObj.pos.y);
		stMap.obj.push_back(stMap.stObj);

		//벽
		stMap.stObj.r = new Rect;
		stMap.stObj.r->SetScale(WINSIZEX, 50);
		stMap.stObj.pos.x = INITX, stMap.stObj.pos.y = WINSIZEY - 20;
		stMap.stObj.r->SetPos(stMap.stObj.pos.x, stMap.stObj.pos.y);
		stMap.obj.push_back(stMap.stObj);

		//화분
		stMap.stObj.r = new Rect;
		stMap.stObj.r->SetScale(160, 190);
		stMap.stObj.pos.x = WINSIZEX - 240, stMap.stObj.pos.y = 90;
		stMap.stObj.r->SetPos(stMap.stObj.pos.x, stMap.stObj.pos.y);
		stMap.obj.push_back(stMap.stObj);

		//게임기, 티비
		stMap.stObj.r = new Rect;
		stMap.stObj.r->SetScale(160, 185);
		stMap.stObj.pos.x = INITX- 80, stMap.stObj.pos.y = INITY - 90;
		stMap.stObj.r->SetPos(stMap.stObj.pos.x, stMap.stObj.pos.y);
		stMap.stObj.explain = true;
		stMap.obj.push_back(stMap.stObj);

		//계단
		stMap.stObj.r = new Rect;
		stMap.stObj.r->SetScale(160, 95);
		stMap.stObj.pos.x = WINSIZEX - 80, stMap.stObj.pos.y = WINSIZEY - 135;
		stMap.stObj.r->SetPos(stMap.stObj.pos.x, stMap.stObj.pos.y);
		stMap.stObj.r->SetPos(WINSIZEX - 80, WINSIZEY - 135);
		stMap.stObj.exist = 1;
		stMap.obj.push_back(stMap.stObj);
	}
	palletTown.insert(make_pair(Pallet::hRoom, stMap));
}

void PalletTown::HLivingInit()
{
	//주인공 방 밑층(1층)
	tagMapType stMap;

	stMap.s = new Sprite(L"start", RECT{ 168, 8, 297, 136 });
	stMap.scale.x = WINSIZEX, stMap.scale.y = WINSIZEY;
	stMap.pos.x = INITX, stMap.pos.y = INITY;
	stMap.s->SetConstantScale(stMap.scale.x, stMap.scale.y);
	stMap.s->SetPos(stMap.pos.x, stMap.pos.y);
	stMap.bikeRide = false;
	{
		//object 영역 생성
		//책장
		stMap.stObj.r = new Rect;
		stMap.stObj.r->SetScale(330, 190);
		stMap.stObj.pos.x = 140, stMap.stObj.pos.y = WINSIZEY - 90;
		stMap.stObj.r->SetPos(stMap.stObj.pos.x, stMap.stObj.pos.y);
		stMap.stObj.explain = true;
		stMap.obj.push_back(stMap.stObj);
		//티비
		stMap.stObj.r = new Rect;
		stMap.stObj.r->SetScale(120, 80);
		stMap.stObj.pos.x = INITX- 80, stMap.stObj.pos.y = WINSIZEY - 130;
		stMap.stObj.r->SetPos(stMap.stObj.pos.x, stMap.stObj.pos.y);
		stMap.stObj.explain = true;
		stMap.obj.push_back(stMap.stObj);
		//벽
		stMap.stObj.r = new Rect;
		stMap.stObj.r->SetScale(WINSIZEX, 50);
		stMap.stObj.pos.x = INITX, stMap.stObj.pos.y = WINSIZEY - 20;
		stMap.stObj.r->SetPos(stMap.stObj.pos.x, stMap.stObj.pos.y);
		stMap.obj.push_back(stMap.stObj);
		//책상
		stMap.stObj.r = new Rect;
		stMap.stObj.r->SetScale(290, 150);
		stMap.stObj.pos.x = INITX, stMap.stObj.pos.y = INITY - 90;
		stMap.stObj.r->SetPos(stMap.stObj.pos.x, stMap.stObj.pos.y);
		stMap.obj.push_back(stMap.stObj);
		//계단
		stMap.stObj.r = new Rect;
		stMap.stObj.r->SetScale(160, 95);
		stMap.stObj.pos.x = WINSIZEX - 80, stMap.stObj.pos.y = WINSIZEY - 135;
		stMap.stObj.r->SetPos(stMap.stObj.pos.x, stMap.stObj.pos.y);
		stMap.stObj.exist = 1;
		stMap.obj.push_back(stMap.stObj);
		//문(영역 밖)
		stMap.stObj.r = new Rect;
		stMap.stObj.r->SetScale(315, 10);
		stMap.stObj.pos.x = 475, stMap.stObj.pos.y = 0;
		stMap.stObj.r->SetPos(stMap.stObj.pos.x, stMap.stObj.pos.y);
		stMap.stObj.exist = 2;
		stMap.obj.push_back(stMap.stObj);
	}
	palletTown.insert(make_pair(Pallet::hLiving, stMap));
}

void PalletTown::PalletInit()
{
	//주인공 시작 마을
	tagMapType stMap;

	stMap.s = new Sprite(L"start", RECT{ 16, 143, 448, 528 });
	stMap.scale.x = WINSIZEX * 2, stMap.scale.y = WINSIZEY * 3;
	stMap.pos.x = WINSIZEX, stMap.pos.y = 0;
	stMap.s->SetConstantScale(stMap.scale.x, stMap.scale.y);
	stMap.s->SetPos(stMap.pos.x, stMap.pos.y);
	stMap.bikeRide = true;
	{
		//object 설정
		//표지판
		stMap.stObj.r = new Rect;
		stMap.stObj.r->SetScale(45 * 2, 25 *3);
		stMap.stObj.pos.x = 615, stMap.stObj.pos.y = WINSIZEY - 315;
		stMap.stObj.r->SetPos(stMap.stObj.pos.x, stMap.stObj.pos.y);
		stMap.stObj.explain = true;
		stMap.obj.push_back(stMap.stObj);
		//울타리?
		stMap.stObj.r = new Rect;
		stMap.stObj.r->SetScale(70, WINSIZEY * 2 + 200);
		stMap.stObj.pos.x = 330, stMap.stObj.pos.y = -10;
		stMap.stObj.r->SetPos(stMap.stObj.pos.x, stMap.stObj.pos.y);
		stMap.obj.push_back(stMap.stObj);	//1

		stMap.stObj.r = new Rect;
		stMap.stObj.r->SetScale(840, 20);
		stMap.stObj.pos.x = 800, stMap.stObj.pos.y = WINSIZEY + 60;
		stMap.stObj.r->SetPos(stMap.stObj.pos.x, stMap.stObj.pos.y);
		stMap.obj.push_back(stMap.stObj);	//2

		stMap.stObj.r = new Rect;
		stMap.stObj.r->SetScale(70, 250);
		stMap.stObj.pos.x = 1180, stMap.stObj.pos.y = WINSIZEY + 230;
		stMap.stObj.r->SetPos(stMap.stObj.pos.x, stMap.stObj.pos.y);
		stMap.obj.push_back(stMap.stObj);	//3

		stMap.stObj.r = new Rect;
		stMap.stObj.r->SetScale(70, 250);
		stMap.stObj.pos.x = 1470, stMap.stObj.pos.y = WINSIZEY + 230;
		stMap.stObj.r->SetPos(stMap.stObj.pos.x, stMap.stObj.pos.y);
		stMap.obj.push_back(stMap.stObj);	//4

		stMap.stObj.r = new Rect;
		stMap.stObj.r->SetScale(740, 20);
		stMap.stObj.pos.x = 1800, stMap.stObj.pos.y = WINSIZEY + 60;
		stMap.stObj.r->SetPos(stMap.stObj.pos.x, stMap.stObj.pos.y);
		stMap.obj.push_back(stMap.stObj);	//5

		stMap.stObj.r = new Rect;
		stMap.stObj.r->SetScale(70, WINSIZEY * 2 + 200);
		stMap.stObj.pos.x = 2130, stMap.stObj.pos.y = -10;
		stMap.stObj.r->SetPos(stMap.stObj.pos.x, stMap.stObj.pos.y);
		stMap.obj.push_back(stMap.stObj);	//6

		stMap.stObj.r = new Rect;
		stMap.stObj.r->SetScale(1080, 164);
		stMap.stObj.pos.x = 1580, stMap.stObj.pos.y = -720;
		stMap.stObj.r->SetPos(stMap.stObj.pos.x, stMap.stObj.pos.y);
		stMap.obj.push_back(stMap.stObj);	//7

		//물
		stMap.stObj.r = new Rect;
		stMap.stObj.r->SetScale(388, 800);
		stMap.stObj.pos.x = 852, stMap.stObj.pos.y = -755;
		stMap.stObj.r->SetPos(stMap.stObj.pos.x, stMap.stObj.pos.y);
		stMap.stObj.water = true;
		stMap.obj.push_back(stMap.stObj);

		//건물 벽
		stMap.stObj.r = new Rect;
		stMap.stObj.r->SetScale(340, 170);
		stMap.stObj.pos.x = 870, stMap.stObj.pos.y = WINSIZEY - 200;
		stMap.stObj.r->SetPos(stMap.stObj.pos.x, stMap.stObj.pos.y);
		stMap.obj.push_back(stMap.stObj);	//자기 집
		
		stMap.stObj.r = new Rect;
		stMap.stObj.r->SetScale(340, 170);
		stMap.stObj.pos.x = 1600, stMap.stObj.pos.y = WINSIZEY - 200;
		stMap.stObj.r->SetPos(stMap.stObj.pos.x, stMap.stObj.pos.y);
		stMap.obj.push_back(stMap.stObj);	//라이벌 집

		stMap.stObj.r = new Rect;
		stMap.stObj.r->SetScale(540, 250);
		stMap.stObj.pos.x = 1510, stMap.stObj.pos.y = 60;
		stMap.stObj.r->SetPos(stMap.stObj.pos.x, stMap.stObj.pos.y);
		stMap.obj.push_back(stMap.stObj);	//오박사 연구소

		//자기 집 문
		stMap.stObj.r = new Rect;
		stMap.stObj.r->SetScale(60, 75);
		stMap.stObj.pos.x = 800, stMap.stObj.pos.y = WINSIZEY - 310;
		stMap.stObj.r->SetPos(stMap.stObj.pos.x, stMap.stObj.pos.y);
		stMap.stObj.exist = 1;
		stMap.obj.push_back(stMap.stObj);

		//라이벌네 집 문
		stMap.stObj.r = new Rect;
		stMap.stObj.r->SetScale(60, 75);
		stMap.stObj.pos.x = 1560, stMap.stObj.pos.y = WINSIZEY - 310;
		stMap.stObj.r->SetPos(stMap.stObj.pos.x, stMap.stObj.pos.y);
		stMap.stObj.exist = 2;
		stMap.obj.push_back(stMap.stObj);

		//오박사 연구소 문
		stMap.stObj.r = new Rect;
		stMap.stObj.r->SetScale(60, 75);
		stMap.stObj.pos.x = 1470, stMap.stObj.pos.y = -140;
		stMap.stObj.r->SetPos(stMap.stObj.pos.x, stMap.stObj.pos.y);
		stMap.stObj.exist = 3;
		stMap.obj.push_back(stMap.stObj);
	}

	{
		//포켓몬 전투 발생 지역
		stMap.field.r = new Rect;
		stMap.field.r->SetScale(300, 400);
		stMap.field.pos.x = 950, stMap.field.pos.y = WINSIZEY + 80;
		stMap.field.r->SetPos(stMap.field.pos.x, stMap.field.pos.y);
		stMap.battle.push_back(stMap.field);	
	}
	palletTown.insert(make_pair(Pallet::PalletTown, stMap));
	mapMax = false;
}

void PalletTown::RivalHouseInit()
{
	//라이벌 집
	tagMapType stMap;

	stMap.s = new Sprite(L"start", RECT{ 304, 8, 433, 136 });
	stMap.scale.x = WINSIZEX, stMap.scale.y = WINSIZEY;
	stMap.pos.x = INITX, stMap.pos.y = INITY;
	stMap.s->SetConstantScale(stMap.scale.x, stMap.scale.y);
	stMap.s->SetPos(stMap.pos.x, stMap.pos.y);
	stMap.bikeRide = false;
	{
		//책장

		//그림

		//책상

		//화분

		//문(영역 밖)

	}
	palletTown.insert(make_pair(Pallet::rivalHouse, stMap));
}

void PalletTown::OLabInit()
{
	//오박사 연구소
	tagMapType stMap;

	stMap.s = new Sprite(L"start", RECT{ 23, 544, 183, 736 });	// L T R B
	stMap.scale.x = WINSIZEX, stMap.scale.y = WINSIZEY;
	stMap.pos.x = INITX, stMap.pos.y = INITY;
	stMap.s->SetConstantScale(stMap.scale.x, stMap.scale.y);
	stMap.s->SetPos(stMap.pos.x, stMap.pos.y);
	stMap.bikeRide = false;
	{
		//책장

		//타운 맵

		//컴퓨터

		//책상

		//휴지통?

		//출입구(영역 밖)
	}
	palletTown.insert(make_pair(Pallet::OLab, stMap));
}

void PalletTown::Update(Player* p)
{
	if (palletLocation == Pallet::PalletTown)
	{
		int speed = 230;
		if (g_pKeyManger->isStayKeyDown(VK_UP) && !p->GetMenuOn()) {
			if (palletTown[Pallet::PalletTown].pos.y > -350) 
			{
				mapMax = false;
				palletTown[palletLocation].pos.y -= speed * g_pTimeManager->GetDeltaTime();
				for (int i = 0; i < palletTown[palletLocation].obj.size(); i++)	
					palletTown[palletLocation].obj[i].pos.y -= speed * g_pTimeManager->GetDeltaTime();
			}
			else  mapMax = true;
		}
		else if (g_pKeyManger->isStayKeyDown(VK_DOWN) && !p->GetMenuOn()) {
			if (palletTown[Pallet::PalletTown].pos.y < WINSIZEY + 350)
			{
				mapMax = false;
				palletTown[palletLocation].pos.y += speed * g_pTimeManager->GetDeltaTime();
				for (int i = 0; i < palletTown[palletLocation].obj.size(); i++)
					palletTown[palletLocation].obj[i].pos.y += speed * g_pTimeManager->GetDeltaTime();
			}
			else  mapMax = true;
		}
		else if (g_pKeyManger->isStayKeyDown(VK_LEFT) && !p->GetMenuOn()) {
			if (palletTown[Pallet::PalletTown].pos.x < WINSIZEX)
			{
				mapMax = false;
				palletTown[palletLocation].pos.x += speed * g_pTimeManager->GetDeltaTime();
				for (int i = 0; i < palletTown[palletLocation].obj.size(); i++)
					palletTown[palletLocation].obj[i].pos.x += speed * g_pTimeManager->GetDeltaTime();
			}
			else mapMax = true;
		}
		else if (g_pKeyManger->isStayKeyDown(VK_RIGHT) && !p->GetMenuOn()) {
			if (palletTown[Pallet::PalletTown].pos.x > 0)
			{
				mapMax = false;
				palletTown[palletLocation].pos.x -= speed * g_pTimeManager->GetDeltaTime();
				for (int i = 0; i < palletTown[palletLocation].obj.size(); i++)
					palletTown[palletLocation].obj[i].pos.x -= speed * g_pTimeManager->GetDeltaTime();
			}
			else mapMax = true;
		}
		palletTown[palletLocation].s->SetPos(palletTown[palletLocation].pos.x, palletTown[palletLocation].pos.y);
		for (int i = 0; i < palletTown[palletLocation].obj.size(); i++)
			palletTown[palletLocation].obj[i].r->SetPos(palletTown[palletLocation].obj[i].pos.x, palletTown[palletLocation].obj[i].pos.y);
	}
	palletTown[palletLocation].s->Update();
	for (int i = 0; i < palletTown[palletLocation].obj.size(); i++)
		palletTown[palletLocation].obj[i].r->Update();
}

void PalletTown::Render()
{
	palletTown[palletLocation].s->Render();
	for (int i = 0; i < palletTown[palletLocation].obj.size(); i++)
		palletTown[palletLocation].obj[i].r->Render_Border();

}

void PalletTown::CollisionCheck(Player* p)
{
	for (int i = 0; i < palletTown[palletLocation].obj.size(); i++) 
	{
		if (AABB(p->GetPlayerPos().x, p->GetPlayerPos().y, p->GetPlayerScale().x, p->GetPlayerScale().y,
			palletTown[palletLocation].obj[i].r->GetPos().x, palletTown[palletLocation].obj[i].r->GetPos().y, palletTown[palletLocation].obj[i].r->GetScaling().x -50, palletTown[palletLocation].obj[i].r->GetScaling().y - 50)) {
			if (palletTown[palletLocation].obj[i].exist)
			{
				if (g_pKeyManger->isStayKeyDown(VK_UP) && palletLocation == Pallet::PalletTown)
				{
					palletLocation = MoveLocation(palletTown[palletLocation].obj[i].exist, p);
					p->SetPlayerCollision(PlayerCollision::Normal);
					break;
				}
				else
				{
					palletLocation = MoveLocation(palletTown[palletLocation].obj[i].exist, p);
					p->SetPlayerCollision(PlayerCollision::Normal);
					break;
				}
			}
			if (g_pKeyManger->isStayKeyDown(VK_RIGHT)) {
				p->SetPlayerCollision(PlayerCollision::RightCollision);
				break;
			}
			//좌측 충돌
			else if (g_pKeyManger->isStayKeyDown(VK_LEFT)) {
				p->SetPlayerCollision(PlayerCollision::LeftCollision);
				break;
			}
			//위 충돌
			else if (g_pKeyManger->isStayKeyDown(VK_UP)) {
				p->SetPlayerCollision(PlayerCollision::UpCollision);
				break;
			}
			//아래 충돌
			else if (g_pKeyManger->isStayKeyDown(VK_DOWN)) {
				p->SetPlayerCollision(PlayerCollision::DownCollision);
				break;
			}
		}
		else p->SetPlayerCollision(PlayerCollision::Normal);		
	}
}

Pallet PalletTown::MoveLocation(int exist, Player* p)
{
	if (palletLocation == Pallet::hRoom) 
	{
		if (exist == 1)
		{
			p->SetPlayerPos(WINSIZEX - 300, WINSIZEY - 100);
			return Pallet::hLiving;
		}
	}
	else if (palletLocation == Pallet::hLiving)
	{
		if (exist == 1)
		{
			p->SetPlayerPos(WINSIZEX - 200, WINSIZEY - 300);
			return Pallet::hRoom;
		}
		else if(exist == 2)
		{
			p->SetPlayerPos(800, INITY - 50);
			return Pallet::PalletTown;
		}
	}
	else if (palletLocation == Pallet::PalletTown)
	{
		if (exist == 1)
		{
			p->SetPlayerPos(INITX + 70, 80);
			return Pallet::hLiving;
		}
		else if (exist == 2)
		{
			p->SetPlayerPos(600, 120);
			return Pallet::rivalHouse;
		}
		else if (exist == 3)
		{
			p->SetPlayerPos(600, 120);
			return Pallet::OLab;
		}
	}
}