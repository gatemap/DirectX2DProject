#pragma once
#include "SingletonBase.h"

#define g_pIniData IniData::GetInstance()

class IniData : public SingletonBase<IniData>
{
private:
	struct tagIniData
	{
		wstring section;
		wstring key;
		wstring value;
	};

private:
	vector<tagIniData> m_vecIniData;

public:
	// 세이브 할 데이터 추가
	void AddSaveData(wstring section, wstring key, wstring value);
	// 세이브
	void Save(wstring fileName);

	// 문자값 로드
	wstring LoadStringData(wstring fileName, wstring section, wstring key);
	// 정수값 로드
	int LoadIntegerData(wstring fileName, wstring section, wstring key);

	//세이브 파일 확인
	bool saveFileExist();
};

