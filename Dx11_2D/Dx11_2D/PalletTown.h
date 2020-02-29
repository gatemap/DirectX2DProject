#pragma once
#include "Map.h"
#include "Player.h"

enum class Pallet {
	hRoom, hLiving, PalletTown, rivalHouse, OLab
};

class PalletTown : public Map
{
	map<Pallet, tagMapType> palletTown;
	Pallet palletLocation;
	bool mapMax;

public:
	PalletTown();
	~PalletTown();

	void HRoomInit();
	void HLivingInit();
	void PalletInit();
	void RivalHouseInit();
	void OLabInit();

	void Update(Player* p);
	void Render();

	//function
	void CollisionCheck(Player* p);
	Pallet MoveLocation(int exist, Player* p);

	//Getter & Setter
	void SetInPallet(Pallet p) { palletLocation = p; }
	Pallet GetPalletLoc() { return palletLocation; }
	bool GetMapMax() { return mapMax; }
};