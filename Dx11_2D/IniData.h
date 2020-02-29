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
	// ���̺� �� ������ �߰�
	void AddSaveData(wstring section, wstring key, wstring value);
	// ���̺�
	void Save(wstring fileName);

	// ���ڰ� �ε�
	wstring LoadStringData(wstring fileName, wstring section, wstring key);
	// ������ �ε�
	int LoadIntegerData(wstring fileName, wstring section, wstring key);

	//���̺� ���� Ȯ��
	bool saveFileExist();
};

