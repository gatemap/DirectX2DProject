#pragma once
#include "GameNode.h"
#include "PlaySetting.h"

class MainGame : public GameNode
{
private:
	ID3D11Buffer*		m_pVPBuffer;	// 뷰x프로젝션 매트릭스 버퍼
	tagVPMatrix*		m_pVPMatrix;	// 뷰x프로젝션 구조

	ID3D11BlendState*	m_pNormalBlendState;
	ID3D11BlendState*	m_pAlphaBlendState;

	PlaySetting*		p;

public:
	MainGame();
	~MainGame();

	virtual void Init() override;
	virtual void Update() override;
	virtual void Render() override;
};

