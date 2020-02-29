#pragma once

class Sprite
{
private:
	struct PTVertex
	{
		D3DXVECTOR3	Position;
		D3DXVECTOR2 UV;
		D3DXCOLOR Color;

		PTVertex() {}
		PTVertex(D3DXVECTOR3 p, D3DXVECTOR2 uv, D3DXCOLOR c) : Position(p), UV(uv), Color(c) {}
	};

	struct fRect {
		float l, r, t, b;
	};

private:
	Shader*						m_pShader;

	D3DXMATRIX*					m_pMatWorld;
	ID3D11Buffer*				m_pWorldBuffer;
	ID3D11Buffer*				m_pVertexBuffer;
	ID3D11ShaderResourceView*	m_pTexture; // m_pSRV

	D3DXVECTOR2					m_vPos;
	D3DXVECTOR2					m_vScale;
	D3DXVECTOR2					m_vInitSize;
	D3DXCOLOR					m_vColor;
	fRect						fRt;

	PTVertex					m_arrVertex[4];

	void InitSprite(wstring key, float u, float v, float numU, float numV);

	void InitSpriteCo();
	void SetLRBT(fRect rt, float width, float height);

public:
	Sprite(wstring key);		//파일 전체를 하나의 이미지로 읽어오기
	Sprite(wstring key, float u, float v, float maxU, float maxV);		//이미지를 부분적으로 사용하기
	Sprite(wstring key, RECT rt); // 이미지 부분적 사용(좌표값)
	~Sprite();

	void Update();
	void Render();

	//function
	void UpdateAndRender();

	// Getter & Setter
	void SetLBPos(float x, float y);
	void SetPos(float x, float y) { m_vPos.x = x; m_vPos.y = y; }
	void SetScale(float x, float y) { m_vScale.x = x; m_vScale.y = y; }
	float GetPosY() { return m_vPos.y; }
	float GetPosX() { return m_vPos.x; }
	
	void SetAlpha(float a) { m_vColor.a = a; }
	float GetAlpha() { return m_vColor.a; }

	void SetRed(float r) { m_vColor.r = r; }

	void SetConstantScale(float x, float y);

	D3DXVECTOR2 GetSize();
};

