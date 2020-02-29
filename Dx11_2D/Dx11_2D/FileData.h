#pragma once
#include "SingletonBase.h"

#define g_pFileData FileData::GetInstance()

class FileData : public SingletonBase<FileData>
{
private:
	// 벡터에 담긴 여러개의 데이터를 하나의 문자열로 변환
	char* VectorArrayCombine(vector<string> vArray);
	// 하나의 문자열을 각각의 데이터로 분리하여 벡터에 담아서 반환
	vector<string> CharArraySeparation(char charArray[]);

public:
	void TextSave(wstring fileName, vector<string> saveData);
	vector<string> TextLoad(wstring fileName);
};

