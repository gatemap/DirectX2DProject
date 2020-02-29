#pragma once
#include "SingletonBase.h"

#define g_pTextureManager TextureManager::GetInstance()

typedef Shader*						LPShader;
typedef ID3D11ShaderResourceView*	LPSrv;

typedef struct tagImage
{
	LPSrv				pSrv;
	D3DX11_IMAGE_INFO	stInfo;
} *LPImage;

typedef struct tagTexture
{
	LPShader			pShader;
	LPImage				pImage;
} *LPTexture;

//struct tagTexture
//{
//	LPShader			pShader;
//	LPImage				pImage;
//};
//
//typedef tagTexture*		LPTexture;

class TextureManager : public SingletonBase<TextureManager>
{
private:
	map<wstring, LPShader>		m_mapShader;
	map<wstring, LPImage>		m_mapImage;
	map<wstring, LPTexture>		m_mapTexture;

public:
	TextureManager();
	~TextureManager();

	void AddTexture(wstring textureKey, wstring imageKey, wstring imageFile,
					wstring shaderKey, wstring shaderFile);
	LPTexture GetTexture(wstring key);
};

