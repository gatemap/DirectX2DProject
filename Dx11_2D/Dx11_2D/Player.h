#pragma once
#include "Menu.h"
#define SPEED 170

enum class PlayerState {
	Ready = -1, Up, Down, Left, Right, FaceIdle, LeftIdle, RightIdle, BackIdle
};

enum class PlayerCollision {
	Normal = -1, UpCollision, DownCollision, LeftCollision, RightCollision
};

class Player
{
	Animation<PlayerState>* p;
	D3DXVECTOR2 pos;
	D3DXVECTOR2 scaleRate;
	D3DXVECTOR2 scale;
	PlayerCollision collisionCheck;
	
	Rect*		tmpR;

	int			money;
	float		speed;
	bool		menuOn;

	Menu*		menu;

public:
	Player();
	~Player();

	void Init();
	void Update();
	void Render();

	//Getter & Setter
	void SetPlayerPos(float x, float y) { pos.x = x, pos.y = y; }
	void SetPlayerCollision(PlayerCollision col) { collisionCheck = col; }
	void SetPlayerMoney(int m) { money = m; }
	void SetPlayerSpeed(int s) { speed = s; }
	void SetMenuOn(bool b) { menuOn = b; }

	D3DXVECTOR2 GetPlayerPos() { return pos; }
	D3DXVECTOR2 GetPlayerScale() { return scale; }
	float	GetPlayerSpeed() { return speed; }
	PlayerCollision GetPlayerCollision() { return collisionCheck; }
	int GetPlayerMoney() { return money; }
	bool GetMenuOn() { return menuOn; }
};