#include "stdafx.h"
#include "FileData.h"


char* FileData::VectorArrayCombine(vector<string> vArray)
{
	char szBuf[1024];
	ZeroMemory(szBuf, sizeof(char) * 1024);

	// strcpy_s : ���ڿ� ����
	// strcat_s : ���ڿ� ���̱�
	// strcmp_s : ���ڿ� ��
	for (int i = 0; i < vArray.size(); i++)
	{
		strcat_s(szBuf, vArray[i].c_str());

		if (i < vArray.size() - 1)	// ������ �����Ͱ� �ƴ϶��
			strcat_s(szBuf, ",");	// , �� ������ ����
	}

	return szBuf;
}

vector<string> FileData::CharArraySeparation(char charArray[])
{
	vector<string> vecArray;
	const char* separator = ",";
	char* token;
	char* remained;

	token = strtok_s(charArray, separator, &remained);

	while (token != NULL)
	{
		vecArray.push_back(token);
		token = strtok_s(NULL, separator, &remained);
	}

	return vecArray;
}

void FileData::TextSave(wstring fileName, vector<string> saveData)
{
	HANDLE hFile;
	char szBuf[1024];
	DWORD dwWrite;

	hFile = CreateFile(fileName.c_str(),
		GENERIC_WRITE, 0, NULL, CREATE_ALWAYS,
		FILE_ATTRIBUTE_NORMAL, NULL);

	strncpy_s(szBuf, 1024, VectorArrayCombine(saveData), 1024 - 2);
	WriteFile(hFile, szBuf, strlen(szBuf), &dwWrite, NULL);

	CloseHandle(hFile);
}

vector<string> FileData::TextLoad(wstring fileName)
{
	HANDLE hFile;
	char szBuf[1024];
	DWORD dwRead;

	ZeroMemory(szBuf, sizeof(char) * 1024);

	hFile = CreateFile(fileName.c_str(),
		GENERIC_READ, 0, NULL, OPEN_EXISTING,
		FILE_ATTRIBUTE_NORMAL, NULL);

	ReadFile(hFile, szBuf, 1024, &dwRead, NULL);

	CloseHandle(hFile);

	return CharArraySeparation(szBuf);
}
