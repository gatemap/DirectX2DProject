#pragma once
#include "Player.h"
#include "PalletTown.h"

enum class PlayerLocation {
	Pallet_hRoom, Pallet_hLiving, Pallet_PalletTown, Pallet_rivalHouse, Pallet_OLab
};

class PlaySetting
{
	Player* player;
	PlayerLocation prevLoc;
	PlayerLocation curLoc;

	//Map
	PalletTown* pTown;

	void MapSetting();
	void MapMoveCheck();
public:
	PlaySetting();
	~PlaySetting();

	void Init();
	void Update();
	void Render();

	//Setter & Getter

};