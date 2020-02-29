#include "stdafx.h"
#include "PlaySetting.h"

PlaySetting::PlaySetting()
{
	player = new Player;
}


PlaySetting::~PlaySetting()
{
	SAFE_DELETE(player);
}

void PlaySetting::MapSetting()
{
	switch (curLoc)
	{
	case PlayerLocation::Pallet_hRoom:
		pTown = new PalletTown;
		pTown->SetInPallet(Pallet::hRoom);
		pTown->HRoomInit();
		break;
	case PlayerLocation::Pallet_hLiving:
		pTown = new PalletTown;
		pTown->SetInPallet(Pallet::hLiving);
		pTown->HLivingInit();
		break;
	case PlayerLocation::Pallet_PalletTown:
		pTown = new PalletTown;
		pTown->SetInPallet(Pallet::PalletTown);
		pTown->PalletInit();
		break;
	case PlayerLocation::Pallet_rivalHouse:
		pTown = new PalletTown;
		pTown->SetInPallet(Pallet::rivalHouse);
		pTown->RivalHouseInit();
		break;
	case PlayerLocation::Pallet_OLab:
		pTown = new PalletTown;
		pTown->SetInPallet(Pallet::OLab);
		pTown->OLabInit();
		break;
	}
}

void PlaySetting::MapMoveCheck()
{
	if (pTown->GetPalletLoc() == Pallet::hRoom)
		curLoc = PlayerLocation::Pallet_hRoom;
	else if (pTown->GetPalletLoc() == Pallet::hLiving)
		curLoc = PlayerLocation::Pallet_hLiving;
	else if (pTown->GetPalletLoc() == Pallet::PalletTown)
		curLoc = PlayerLocation::Pallet_PalletTown;
	else if (pTown->GetPalletLoc() == Pallet::rivalHouse)
		curLoc = PlayerLocation::Pallet_rivalHouse;
	else if (pTown->GetPalletLoc() == Pallet::OLab)
		curLoc = PlayerLocation::Pallet_OLab;
}

void PlaySetting::Init()
{
	if (player) player->Init();
	curLoc = PlayerLocation::Pallet_hRoom;
	MapSetting();
}

void PlaySetting::Update()
{
	if (pTown) {
		prevLoc = curLoc;
		pTown->CollisionCheck(player);
		MapMoveCheck();
		if (prevLoc != curLoc)
		{
			SAFE_DELETE(pTown);
			MapSetting();
		}
		if (curLoc == PlayerLocation::Pallet_PalletTown)
		{
			if(!pTown->GetMapMax())		player->SetPlayerSpeed(0);
			else player->SetPlayerSpeed(SPEED);
		}
		else player->SetPlayerSpeed(SPEED);
		pTown->Update(player);
	}
	if (player) player->Update();
}

void PlaySetting::Render()
{
	if (pTown) pTown->Render();
	if (player) player->Render();
}