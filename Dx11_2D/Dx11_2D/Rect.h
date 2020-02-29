#pragma once

class Rect
{
private:
	struct PCVertex	// 포지션 정보, 색상 정보를 갖는 Vertex 구조체
	{
		D3DXVECTOR3	Position;
		D3DXCOLOR	Color;

		PCVertex() {}
		PCVertex(D3DXVECTOR3 p, D3DXCOLOR c) : Position(p), Color(c) {}
	};

private:
	Shader*				m_pShader;

	D3DXMATRIX*			m_pMatWorld;
	ID3D11Buffer*		m_pWorldBuffer;
	ID3D11Buffer*		m_pVertexBuffer;
	ID3D11Buffer*		m_pBorderBuffer;

	PCVertex			m_arrVertex[5];		// 로컬 기준 포지션 정보
	D3DXVECTOR2			m_vScaling;			// 크기
	D3DXVECTOR3			m_vRotation;		// 회전
	D3DXVECTOR2			m_vTranslation;		// 이동

public:
	Rect();
	~Rect();

	void Update();
	void Render();

	void Render_Border();

	// 겟터셋터 작성
	D3DXVECTOR2 GetPos() { return m_vTranslation; }
	void SetPos(float x, float y) { m_vTranslation.x = x; m_vTranslation.y = y; }
	D3DXVECTOR2 GetScaling() { return m_vScaling; }
	void SetScale(D3DXVECTOR2 v) { m_vScaling = v; }
	void SetScale(float x, float y) { m_vScaling.x = x; m_vScaling.y = y; }
};

