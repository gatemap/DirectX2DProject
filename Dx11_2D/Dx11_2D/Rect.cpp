#include "stdafx.h"
#include "Rect.h"

Rect::Rect()
{
	// ���̴� ���� : ���̴����� ������ ����� ������ ���� �Ӽ��� �����ϰ�
	//              ���̴� �ڵ� ������ �о�ͼ� ���̴��� ������ �ش�.
	{
		// �����ǰ� ������ ������ ���ؽ� ���� ����
		D3D11_INPUT_ELEMENT_DESC PCLayoutDesc[] =
		{
			{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
			{ "COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		};
		static UINT PCElementCount = ARRAYSIZE(PCLayoutDesc);

		m_pShader = new Shader(PCLayoutDesc, PCElementCount,
			L"../../_Shader/Rect.hlsl");
	}

	// ���� ���� ��ǥ ���� �����ϰ� ���ؽ� ���۸� ���� �Ѵ�.
	{
		m_arrVertex[0] = PCVertex(D3DXVECTOR3(-0.5f,-0.5f, 0.0f), D3DXCOLOR(1, 0, 0, 1));
		m_arrVertex[1] = PCVertex(D3DXVECTOR3(-0.5f, 0.5f, 0.0f), D3DXCOLOR(1, 0, 0, 1));
		m_arrVertex[2] = PCVertex(D3DXVECTOR3( 0.5f, 0.5f, 0.0f), D3DXCOLOR(1, 0, 0, 1));
		m_arrVertex[3] = PCVertex(D3DXVECTOR3( 0.5f,-0.5f, 0.0f), D3DXCOLOR(1, 0, 0, 1));
		m_arrVertex[4] = PCVertex(D3DXVECTOR3(-0.5f,-0.5f, 0.0f), D3DXCOLOR(1, 0, 0, 1));

		PCVertex vertices[6] =
		{
			m_arrVertex[0],	m_arrVertex[1],	m_arrVertex[2],
			m_arrVertex[0],	m_arrVertex[2],	m_arrVertex[3],
		};

		// CreateVertexBuffer : m_pVertexBuffer
		{
			D3D11_BUFFER_DESC desc = { 0, };
			desc.Usage = D3D11_USAGE_DEFAULT;
			desc.ByteWidth = sizeof(PCVertex) * 6;
			desc.BindFlags = D3D11_BIND_VERTEX_BUFFER;

			D3D11_SUBRESOURCE_DATA data = { 0, };
			data.pSysMem = vertices;

			HRESULT hr = g_pDevice->CreateBuffer(&desc, &data, &m_pVertexBuffer);
			assert(SUCCEEDED(hr));
		}
		// CreateBorderBuffer : m_pBorderBuffer
		{
			D3D11_BUFFER_DESC desc = { 0, };
			desc.Usage = D3D11_USAGE_DEFAULT;
			desc.ByteWidth = sizeof(PCVertex) * 5;
			desc.BindFlags = D3D11_BIND_VERTEX_BUFFER;

			D3D11_SUBRESOURCE_DATA data = { 0, };
			data.pSysMem = m_arrVertex;

			HRESULT hr = g_pDevice->CreateBuffer(&desc, &data, &m_pBorderBuffer);
			assert(SUCCEEDED(hr));
		}
	}

	// ���� ��Ʈ���� �ʱ�ȭ �� ���� ��Ʈ���� ���� ����
	{
		m_pMatWorld = new D3DXMATRIX;
		D3DXMatrixIdentity(m_pMatWorld);

		// Create WorldBuffer
		{
			D3D11_BUFFER_DESC desc = { 0, };
			desc.Usage = D3D11_USAGE_DEFAULT;
			desc.ByteWidth = sizeof(D3DXMATRIX);
			desc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;

			HRESULT hr = g_pDevice->CreateBuffer(&desc, NULL, &m_pWorldBuffer);
			assert(SUCCEEDED(hr));
		}
		g_pDeviceContext->UpdateSubresource(m_pWorldBuffer, 0, NULL, m_pMatWorld, 0, 0);
	}

	// ũ��, ȸ��, ��ġ ���� ����
	m_vScaling.x = m_vScaling.y = 50;
	m_vRotation.x = m_vRotation.y = m_vRotation.z = 0.0f;
	m_vTranslation.x = m_vTranslation.y = 50;
}

Rect::~Rect()
{
	SAFE_RELEASE(m_pWorldBuffer);
	SAFE_DELETE(m_pMatWorld);
	SAFE_RELEASE(m_pVertexBuffer);
	SAFE_DELETE(m_pShader);
}

void Rect::Update()
{
	// World ��Ʈ���� ������Ʈ (SRT) : ũ�� ���� ��, ȸ����, �̵����� ����Ͽ� ��ȯ ��Ʈ���� ����
	// ������ ��ȯ ��Ʈ���� �������� ���� ��Ʈ������ ���� ����Ѵ�. (WorldMatrix == SRT Matrix)
	D3DXMATRIX S, RX, RY, RZ, T;
	D3DXMatrixScaling(&S, m_vScaling.x, m_vScaling.y, 1);
	D3DXMatrixRotationX(&RX, m_vRotation.x);
	D3DXMatrixRotationY(&RY, m_vRotation.y);
	D3DXMatrixRotationZ(&RZ, m_vRotation.z);
	D3DXMatrixTranslation(&T, m_vTranslation.x, m_vTranslation.y, 0);
	*m_pMatWorld = S * RX * RY * RZ * T;
	// ���̴����� ����ϴ� ��Ʈ������ ��� ���� ������ �ݴ�α� ������ Ʈ������� �����ش�.
	D3DXMatrixTranspose(m_pMatWorld, m_pMatWorld);

	// ���� �� ���� ��Ʈ���� ������ ���� ���ۿ� �����Ѵ�.
	g_pDeviceContext->UpdateSubresource(m_pWorldBuffer, 0, NULL, m_pMatWorld, 0, 0);
}

void Rect::Render()
{
	// ��� �� ���̴��� �����Ѵ�.
	m_pShader->SetShader();

	// ���� ���۸� �����Ѵ�. : (VS)���ؽ� ���̴����� ���
	g_pDeviceContext->VSSetConstantBuffers(1, 1, &m_pWorldBuffer);

	// ȭ�鿡 �׸���.(����)
	{
		UINT stride = sizeof(PCVertex);
		UINT offset = 0;

		// ���ؽ� ���۸� �����Ѵ�.
		g_pDeviceContext->IASetVertexBuffers(0, 1, &m_pVertexBuffer, &stride, &offset);
		// �׸� ������ �ɼ� ���� (�ﰢ�� ����Ʈ)
		g_pDeviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);
		// ��ο�(����)
		g_pDeviceContext->Draw(6, 0);
	}
}

void Rect::Render_Border()
{
	// ��� �� ���̴��� �����Ѵ�.
	m_pShader->SetShader();

	// ���� ���۸� �����Ѵ�. : (VS)���ؽ� ���̴����� ���
	g_pDeviceContext->VSSetConstantBuffers(1, 1, &m_pWorldBuffer);

	// ȭ�鿡 �׸���.(����)
	{
		UINT stride = sizeof(PCVertex);
		UINT offset = 0;

		// ���ؽ� ���۸� �����Ѵ�.
		g_pDeviceContext->IASetVertexBuffers(0, 1, &m_pBorderBuffer, &stride, &offset);
		// �׸� ������ �ɼ� ���� (���� ��Ʈ��)
		g_pDeviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_LINESTRIP);
		// ��ο�(����)
		g_pDeviceContext->Draw(5, 0);
	}
}