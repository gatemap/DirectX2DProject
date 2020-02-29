#pragma once
#include "SingletonBase.h"

#define g_pFileData FileData::GetInstance()

class FileData : public SingletonBase<FileData>
{
private:
	// ���Ϳ� ��� �������� �����͸� �ϳ��� ���ڿ��� ��ȯ
	char* VectorArrayCombine(vector<string> vArray);
	// �ϳ��� ���ڿ��� ������ �����ͷ� �и��Ͽ� ���Ϳ� ��Ƽ� ��ȯ
	vector<string> CharArraySeparation(char charArray[]);

public:
	void TextSave(wstring fileName, vector<string> saveData);
	vector<string> TextLoad(wstring fileName);
};

