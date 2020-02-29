#include "stdafx.h"
#include "TextureManager.h"


TextureManager::TextureManager(){}

TextureManager::~TextureManager()
{
	for (auto p : m_mapShader) SAFE_DELETE(p.second);	//first 는 key , second 가 data(value)
	m_mapShader.clear();
	for (auto p : m_mapImage)
	{
		SAFE_RELEASE(p.second->pSrv);
		SAFE_DELETE(p.second);
	}
	m_mapImage.clear();
	for (auto p : m_mapTexture) SAFE_DELETE(p.second);
	m_mapTexture.clear();
}

void TextureManager::AddTexture(wstring textureKey, wstring imageKey, wstring imageFile, wstring shaderKey, wstring shaderFile)
{
	// data를 찾지 못했다면 end값을 return 함
	if (m_mapTexture.find(textureKey) != m_mapTexture.end()) //이미 존재하는 key 값이기 때문에 추가하지 않음
		return;

	// 이전에 추가한 이미지 항목에 없을 경우 이미지 추가 로드
	if (m_mapImage.find(imageKey) == m_mapImage.end())
	{
		wstring imageFullPath = L"../../_Textures/" + imageFile;
		HRESULT hr;

		tagImage* pImage = new tagImage;

		D3DX11CreateShaderResourceViewFromFile(g_pDevice, imageFullPath.c_str(), NULL, NULL, &pImage->pSrv, &hr);
		assert(SUCCEEDED(hr));

		D3DX11GetImageInfoFromFile(imageFullPath.c_str(), NULL, &pImage->stInfo, &hr);
		assert(SUCCEEDED(hr));

		m_mapImage.insert(make_pair(imageKey, pImage));
	}

	// 전에 추가한 Shader 항목에 없음
	if (m_mapShader.find(shaderKey) == m_mapShader.end())
	{
		// 포지션과 UV좌표를 가지는 버텍스 포맷 지정
		D3D11_INPUT_ELEMENT_DESC PTLayoutDesc[] =
		{
			{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
			{ "UV", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0 },
			{ "COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 20, D3D11_INPUT_PER_VERTEX_DATA, 0}
		};
		static UINT PTElementCount = ARRAYSIZE(PTLayoutDesc);

		// 쉐이더 포인터 생성
		wstring fullPath = L"../../_Shader/" + shaderFile;
		Shader* pShader = new Shader(PTLayoutDesc, PTElementCount, fullPath);

		m_mapShader.insert(make_pair(shaderKey, pShader));
	}

	// 새로운 텍스쳐 추가
	{
		tagTexture* pTexture = new tagTexture;
		pTexture->pImage = m_mapImage[imageKey];
		pTexture->pShader = m_mapShader[shaderKey];

		m_mapTexture.insert(make_pair(textureKey, pTexture));
	}
}

tagTexture * TextureManager::GetTexture(wstring key)
{
	//assert는 배포 시에 지워줘야한다.
	assert(m_mapTexture.find(key) != m_mapTexture.end() && "No Texture");
	return m_mapTexture[key];
}
