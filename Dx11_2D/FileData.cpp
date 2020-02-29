#include "stdafx.h"
#include "FileData.h"


char* FileData::VectorArrayCombine(vector<string> vArray)
{
	char szBuf[1024];
	ZeroMemory(szBuf, sizeof(char) * 1024);

	// strcpy_s : 문자열 복사
	// strcat_s : 문자열 붙이기
	// strcmp_s : 문자열 비교
	for (int i = 0; i < vArray.size(); i++)
	{
		strcat_s(szBuf, vArray[i].c_str());

		if (i < vArray.size() - 1)	// 마지막 데이터가 아니라면
			strcat_s(szBuf, ",");	// , 로 데이터 구분
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
