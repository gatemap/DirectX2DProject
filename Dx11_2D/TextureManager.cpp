#include "stdafx.h"
#include "TextureManager.h"


TextureManager::TextureManager(){}

TextureManager::~TextureManager()
{
	for (auto p : m_mapShader) SAFE_DELETE(p.second);	//first �� key , second �� data(value)
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
	// data�� ã�� ���ߴٸ� end���� return ��
	if (m_mapTexture.find(textureKey) != m_mapTexture.end()) //�̹� �����ϴ� key ���̱� ������ �߰����� ����
		return;

	// ������ �߰��� �̹��� �׸� ���� ��� �̹��� �߰� �ε�
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

	// ���� �߰��� Shader �׸� ����
	if (m_mapShader.find(shaderKey) == m_mapShader.end())
	{
		// �����ǰ� UV��ǥ�� ������ ���ؽ� ���� ����
		D3D11_INPUT_ELEMENT_DESC PTLayoutDesc[] =
		{
			{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
			{ "UV", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0 },
			{ "COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 20, D3D11_INPUT_PER_VERTEX_DATA, 0}
		};
		static UINT PTElementCount = ARRAYSIZE(PTLayoutDesc);

		// ���̴� ������ ����
		wstring fullPath = L"../../_Shader/" + shaderFile;
		Shader* pShader = new Shader(PTLayoutDesc, PTElementCount, fullPath);

		m_mapShader.insert(make_pair(shaderKey, pShader));
	}

	// ���ο� �ؽ��� �߰�
	{
		tagTexture* pTexture = new tagTexture;
		pTexture->pImage = m_mapImage[imageKey];
		pTexture->pShader = m_mapShader[shaderKey];

		m_mapTexture.insert(make_pair(textureKey, pTexture));
	}
}

tagTexture * TextureManager::GetTexture(wstring key)
{
	//assert�� ���� �ÿ� ��������Ѵ�.
	assert(m_mapTexture.find(key) != m_mapTexture.end() && "No Texture");
	return m_mapTexture[key];
}
