#include "stdafx.h"
#include "IniData.h"


void IniData::AddSaveData(wstring section, wstring key, wstring value)
{
	tagIniData stData;
	stData.section = section;
	stData.key = key;
	stData.value = value;

	m_vecIniData.push_back(stData);
}

void IniData::Save(wstring fileName)
{
	// 경로 지정
	wstring fullPath = wstring(L"../../_Save/");
	fullPath += fileName;

	// 파일에 쓰기
	for (int i = 0; i < m_vecIniData.size(); i++)
	{
		WritePrivateProfileString(m_vecIniData[i].section.c_str(),
			m_vecIniData[i].key.c_str(), m_vecIniData[i].value.c_str(),
			fullPath.c_str());
	}
	m_vecIniData.clear();
}

wstring IniData::LoadStringData(wstring fileName, wstring section, wstring key)
{
	// 경로 지정
	wstring fullPath = wstring(L"../../_Save/");
	fullPath += fileName;

	LPWSTR pData = new WCHAR[256];
	GetPrivateProfileString(section.c_str(), key.c_str(), L"", pData, 256,
		fullPath.c_str());

	return pData;
}

int IniData::LoadIntegerData(wstring fileName, wstring section, wstring key)
{
	// 경로 지정
	wstring fullPath = wstring(L"../../_Save/");
	fullPath += fileName;

	return GetPrivateProfileInt(section.c_str(), key.c_str(), 0, fullPath.c_str());
}

bool IniData::saveFileExist()
{
	/*string fileName = "../../_Save/temp.sav";
	
	if (FILE* f = fopen(fileName.c_str(), "r")) {
		fclose(f);
		return true;
	}
	else	*/return false;
}
