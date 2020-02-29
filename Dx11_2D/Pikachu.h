#pragma once
#include "Player.h"

enum class PikachuEmotion {
	Ready = -1, Sulk, Upset, Normal, HappyLv1, HappyLv2, HappyLv3, Elated,
	Sleep, Awake, Wonder, Surprised, Sad, Cold
};

enum class PikachuState {
	Ready = -1, Up, Down, Left, Right, FaceIdle, LeftIdle, RightIdle, BackIdle
};
class Pikachu
{
	Animation<PikachuState>*	p;
	Animation<PikachuEmotion>*	pEmotion;
	D3DXVECTOR2 pos;
	D3DXVECTOR2 scaleRate;
	PikachuEmotion emotion;
	float		speed;
	bool		exist;

	Player* player;
public:
	Pikachu();
	~Pikachu();

	void EmotionInit();
	void Init();
	void Update();
	void Render();

	//Getter& Setter
	void SetPikachu(bool b) { exist = b; }

	bool GetPikaChu() { return exist; }
};