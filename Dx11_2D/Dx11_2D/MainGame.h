#pragma once
#include "GameNode.h"
#include "GameManager.h"

class MainGame : public GameNode
{
private:
	GameManager* gm;

public:
	MainGame();
	~MainGame();

	virtual void Init() override;
	virtual void Update() override;
	virtual void Render() override;
};

