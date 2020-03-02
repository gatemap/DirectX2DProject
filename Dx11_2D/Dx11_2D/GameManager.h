#pragma once
#include "GameNode.h"
#include "PlaySetting.h"

class GameManager : public GameNode
{
	ID3D11BlendState*	m_pNormalBlendState;
	ID3D11BlendState*	m_pAlphaBlendState;

	PlaySetting*		p;

public:
	GameManager();
	~GameManager();

	virtual void Init() override;
	virtual void Update() override;
	virtual void Render() override;
};

