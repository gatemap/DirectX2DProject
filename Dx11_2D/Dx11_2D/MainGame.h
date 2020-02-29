#pragma once
#include "GameNode.h"
#include "PlaySetting.h"

class MainGame : public GameNode
{
private:
	ID3D11Buffer*		m_pVPBuffer;	// ��x�������� ��Ʈ���� ����
	tagVPMatrix*		m_pVPMatrix;	// ��x�������� ����

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

