#include "stdafx.h"
#include "Rect.h"

Rect::Rect()
{
	// 셰이더 생성 : 셰이더에서 렌더에 사용할 정점의 정보 속성을 지정하고
	//              셰이더 코드 파일을 읽어와서 셰이더를 생성해 준다.
	{
		// 포지션과 정점을 가지는 버텍스 포맷 지정
		D3D11_INPUT_ELEMENT_DESC PCLayoutDesc[] =
		{
			{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
			{ "COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		};
		static UINT PCElementCount = ARRAYSIZE(PCLayoutDesc);

		m_pShader = new Shader(PCLayoutDesc, PCElementCount,
			L"../../_Shader/Rect.hlsl");
	}

	// 로컬 영역 좌표 값을 설정하고 버텍스 버퍼를 생성 한다.
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

	// 월드 매트릭스 초기화 및 월드 매트릭스 버퍼 생성
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

	// 크기, 회전, 위치 값을 설정
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
	// World 매트릭스 업데이트 (SRT) : 크기 변경 값, 회전량, 이동량을 사용하여 변환 매트릭스 생성
	// 각각의 변환 매트릭스 조합으로 월드 매트릭스를 값을 계산한다. (WorldMatrix == SRT Matrix)
	D3DXMATRIX S, RX, RY, RZ, T;
	D3DXMatrixScaling(&S, m_vScaling.x, m_vScaling.y, 1);
	D3DXMatrixRotationX(&RX, m_vRotation.x);
	D3DXMatrixRotationY(&RY, m_vRotation.y);
	D3DXMatrixRotationZ(&RZ, m_vRotation.z);
	D3DXMatrixTranslation(&T, m_vTranslation.x, m_vTranslation.y, 0);
	*m_pMatWorld = S * RX * RY * RZ * T;
	// 셰이더에서 사용하는 매트릭스의 행과 열의 방향이 반대로기 때문에 트랜스포즈를 시켜준다.
	D3DXMatrixTranspose(m_pMatWorld, m_pMatWorld);

	// 변경 된 월드 매트릭스 정보를 월드 버퍼에 갱신한다.
	g_pDeviceContext->UpdateSubresource(m_pWorldBuffer, 0, NULL, m_pMatWorld, 0, 0);
}

void Rect::Render()
{
	// 사용 할 셰이더를 설정한다.
	m_pShader->SetShader();

	// 월드 버퍼를 셋팅한다. : (VS)버텍스 셰이더에서 사용
	g_pDeviceContext->VSSetConstantBuffers(1, 1, &m_pWorldBuffer);

	// 화면에 그린다.(렌더)
	{
		UINT stride = sizeof(PCVertex);
		UINT offset = 0;

		// 버텍스 버퍼를 셋팅한다.
		g_pDeviceContext->IASetVertexBuffers(0, 1, &m_pVertexBuffer, &stride, &offset);
		// 그릴 도형의 옵션 선택 (삼각형 리스트)
		g_pDeviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);
		// 드로우(렌더)
		g_pDeviceContext->Draw(6, 0);
	}
}

void Rect::Render_Border()
{
	// 사용 할 셰이더를 설정한다.
	m_pShader->SetShader();

	// 월드 버퍼를 셋팅한다. : (VS)버텍스 셰이더에서 사용
	g_pDeviceContext->VSSetConstantBuffers(1, 1, &m_pWorldBuffer);

	// 화면에 그린다.(렌더)
	{
		UINT stride = sizeof(PCVertex);
		UINT offset = 0;

		// 버텍스 버퍼를 셋팅한다.
		g_pDeviceContext->IASetVertexBuffers(0, 1, &m_pBorderBuffer, &stride, &offset);
		// 그릴 도형의 옵션 선택 (라인 스트립)
		g_pDeviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_LINESTRIP);
		// 드로우(렌더)
		g_pDeviceContext->Draw(5, 0);
	}
}