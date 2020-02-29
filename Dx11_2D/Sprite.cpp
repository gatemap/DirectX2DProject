#include "stdafx.h"
#include "Sprite.h"

void Sprite::InitSprite(wstring key, float u, float v, float numU, float numV)
{
	tagTexture* pTexture = g_pTextureManager->GetTexture(key);

	m_pShader = pTexture->pShader;
	m_pTexture = pTexture->pImage->pSrv;

	m_vInitSize.x = pTexture->pImage->stInfo.Width / numU, m_vInitSize.y = pTexture->pImage->stInfo.Height / numV;

	//Create World Matrix
	m_pMatWorld = new D3DXMATRIX;
	D3DXMatrixIdentity(m_pMatWorld);

	//Create World Buffer
	{
		D3D11_BUFFER_DESC desc = { 0, };
		desc.Usage = D3D11_USAGE_DEFAULT;
		desc.ByteWidth = sizeof(D3DXMATRIX);
		desc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;

		HRESULT hr = g_pDevice->CreateBuffer(&desc, NULL, &m_pWorldBuffer);
		assert(SUCCEEDED(hr));
	}

	//Vertex information set
	m_arrVertex[0] = PTVertex(D3DXVECTOR3(-m_vInitSize.x * 0.5f, -m_vInitSize.y * 0.5f, 0.0f), D3DXVECTOR2((u + 0) / numU, (v + 1) / numV), D3DXCOLOR(0, 0, 0, m_vColor.a));
	m_arrVertex[1] = PTVertex(D3DXVECTOR3(-m_vInitSize.x * 0.5f, m_vInitSize.y * 0.5f, 0.0f), D3DXVECTOR2((u + 0) / numU, (v + 0) / numV), D3DXCOLOR(0, 0, 0, m_vColor.a));
	m_arrVertex[2] = PTVertex(D3DXVECTOR3(m_vInitSize.x * 0.5f, m_vInitSize.y * 0.5f, 0.0f), D3DXVECTOR2((u + 1) / numU, (v + 0) / numV), D3DXCOLOR(0, 0, 0, m_vColor.a));
	m_arrVertex[3] = PTVertex(D3DXVECTOR3(m_vInitSize.x * 0.5f, -m_vInitSize.y * 0.5f, 0.0f), D3DXVECTOR2((u + 1) / numU, (v + 1) / numV), D3DXCOLOR(0, 0, 0, m_vColor.a));

	// 012 023 (삼각형, 절대평면) 버텍스 셋팅
	PTVertex vertices[6] =
	{
		m_arrVertex[0],	m_arrVertex[1],	m_arrVertex[2],
		m_arrVertex[0],	m_arrVertex[2],	m_arrVertex[3],
	};

	//Create Vertex Buffer
	{
		D3D11_BUFFER_DESC desc = { 0, };
		desc.Usage = D3D11_USAGE_DEFAULT;
		desc.ByteWidth = sizeof(PTVertex) * 6;
		desc.BindFlags = D3D11_BIND_VERTEX_BUFFER;

		D3D11_SUBRESOURCE_DATA data = { 0, };
		data.pSysMem = vertices;

		HRESULT hr = g_pDevice->CreateBuffer(&desc, &data, &m_pVertexBuffer);
		assert(SUCCEEDED(hr));
	}

	m_vPos.x = INITX, m_vPos.y = INITY;

	m_vScale.x = 1.0f, m_vScale.y = 1.0f;
}

Sprite::Sprite(wstring key)
{
	m_vColor.a = 1.f;
	InitSprite(key, 0, 0, 1, 1);
}

Sprite::Sprite(wstring key, float x, float y, float maxX, float maxY)
{
	m_vColor.a = 1.f;
	InitSprite(key, x, y, maxX, maxY);
}

Sprite::Sprite(wstring key, RECT rt)
{
	tagTexture* pTexture = g_pTextureManager->GetTexture(key);

	m_pShader = pTexture->pShader;
	m_pTexture = pTexture->pImage->pSrv;

	m_vInitSize.x = rt.right - rt.left;
	m_vInitSize.y = rt.bottom - rt.top;

	fRect fR;
	fR.l = rt.left, fR.r = rt.right, fR.b = rt.bottom, fR.t = rt.top;

	SetLRBT(fR, pTexture->pImage->stInfo.Width, pTexture->pImage->stInfo.Height);

	m_vColor.a = 1.f;
	InitSpriteCo();
}

Sprite::~Sprite()
{
	//SAFE_RELEASE(m_pTexture);
	SAFE_RELEASE(m_pVertexBuffer);
	SAFE_RELEASE(m_pWorldBuffer);

	SAFE_DELETE(m_pMatWorld);
	//SAFE_DELETE(m_pShader);
}

void Sprite::Update()
{
	m_arrVertex[0].Color.a = m_vColor.a, m_arrVertex[1].Color.a = m_vColor.a, m_arrVertex[2].Color.a = m_vColor.a, m_arrVertex[3].Color.a = m_vColor.a;
	//m_arrVertex[0].Color.r = m_vColor.r, m_arrVertex[1].Color.r = m_vColor.r, m_arrVertex[2].Color.r = m_vColor.r, m_arrVertex[3].Color.r = m_vColor.r;
	PTVertex vertices[6] =
	{
		m_arrVertex[0],	m_arrVertex[1],	m_arrVertex[2],
		m_arrVertex[0],	m_arrVertex[2],	m_arrVertex[3],
	};
	g_pDeviceContext->UpdateSubresource(m_pVertexBuffer, 0, 0, vertices, sizeof(vertices) * 6, 0);

	D3DXMATRIX S, T;
	D3DXMatrixScaling(&S, m_vScale.x, m_vScale.y, 1);
	D3DXMatrixTranslation(&T, m_vPos.x, m_vPos.y, 0);
	

	*m_pMatWorld = S * T;
	D3DXMatrixTranspose(m_pMatWorld, m_pMatWorld);
	g_pDeviceContext->UpdateSubresource(m_pWorldBuffer, 0, 0, m_pMatWorld, 0, 0);
}

void Sprite::Render()
{
	m_pShader->SetShader();

	g_pDeviceContext->VSSetConstantBuffers(1, 1, &m_pWorldBuffer);
	g_pDeviceContext->PSSetShaderResources(0, 1, &m_pTexture);

	UINT stride = sizeof(PTVertex);
	UINT offset = 0;

	g_pDeviceContext->IASetVertexBuffers(0, 1, &m_pVertexBuffer, &stride, &offset);

	g_pDeviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	g_pDeviceContext->Draw(6, 0);
}

void Sprite::UpdateAndRender()
{
	Update();
	Render();
}

void Sprite::SetConstantScale(float x, float y)
{
	m_vScale.x = 1 / m_vInitSize.x * x;
	m_vScale.y = 1 / m_vInitSize.y * y;
}

D3DXVECTOR2 Sprite::GetSize()
{
	return D3DXVECTOR2(m_vInitSize.x * m_vScale.x, m_vInitSize.y * m_vScale.y);
	//return D3DXVECTOR2(m_vScale.x, m_vScale.y);
}

void Sprite::InitSpriteCo()
{

	// 월드 매트릭스 생성
	m_pMatWorld = new D3DXMATRIX;
	D3DXMatrixIdentity(m_pMatWorld);

	// 월드 버퍼 생성
	{
		D3D11_BUFFER_DESC desc = { 0, };
		desc.Usage = D3D11_USAGE_DEFAULT;
		desc.ByteWidth = sizeof(D3DXMATRIX);
		desc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;

		HRESULT hr = g_pDevice->CreateBuffer(&desc, NULL, &m_pWorldBuffer);
		assert(SUCCEEDED(hr));
	}

	// 버텍스 정보 설정
	m_arrVertex[0] = PTVertex(D3DXVECTOR3(-m_vInitSize.x * 0.5f,-m_vInitSize.y * 0.5f, 0.0f), D3DXVECTOR2(fRt.l, fRt.b), D3DXCOLOR(0, 0, 0, m_vColor.a));	//LB
	m_arrVertex[1] = PTVertex(D3DXVECTOR3(-m_vInitSize.x * 0.5f, m_vInitSize.y * 0.5f, 0.0f), D3DXVECTOR2(fRt.l, fRt.t), D3DXCOLOR(0, 0, 0, m_vColor.a));	//LT
	m_arrVertex[2] = PTVertex(D3DXVECTOR3( m_vInitSize.x * 0.5f, m_vInitSize.y * 0.5f, 0.0f), D3DXVECTOR2(fRt.r, fRt.t), D3DXCOLOR(0, 0, 0, m_vColor.a));	//RT
	m_arrVertex[3] = PTVertex(D3DXVECTOR3( m_vInitSize.x * 0.5f,-m_vInitSize.y * 0.5f, 0.0f), D3DXVECTOR2(fRt.r, fRt.b), D3DXCOLOR(0, 0, 0, m_vColor.a));	//RB

	// 012 023 (삼각형, 절대평면) 버텍스 셋팅
	PTVertex vertices[6] =
	{
		m_arrVertex[0],	m_arrVertex[1],	m_arrVertex[2],
		m_arrVertex[0],	m_arrVertex[2],	m_arrVertex[3],
	};

	// 버텍스 버퍼 생성
	{
		D3D11_BUFFER_DESC desc = { 0, };
		desc.Usage = D3D11_USAGE_DEFAULT;
		desc.ByteWidth = sizeof(PTVertex) * 6;
		desc.BindFlags = D3D11_BIND_VERTEX_BUFFER;

		D3D11_SUBRESOURCE_DATA data = { 0, };
		data.pSysMem = vertices;

		HRESULT hr = g_pDevice->CreateBuffer(&desc, &data, &m_pVertexBuffer);
		assert(SUCCEEDED(hr));
	}

	m_vPos.x = INITX, m_vPos.y = INITY;

	m_vScale.x = 1.0f, m_vScale.y = 1.0f;
}

void Sprite::SetLRBT(fRect rt, float width, float height)
{
	fRt.l = rt.l * 1 / width, fRt.r = rt.r * 1 / width;
	fRt.b = rt.b * 1 / height, fRt.t = rt.t * 1 / height;
}

void Sprite::SetLBPos(float x, float y)
{
	m_vPos.x = x + m_vInitSize.x * m_vScale.x * 0.5f;
	m_vPos.y = y + m_vInitSize.y * m_vScale.y * 0.5f;
}