#pragma once
#include "SingletonBase.h"

#define g_pTextManager TextManager::GetInstance()

class TextManager : public SingletonBase<TextManager>
{
private:
	Sprite*			m_pNumber[10];
	Sprite*			m_pUpperLetter[26];
	Sprite*			m_pLowerLetter[26];
	Sprite*			consonant[19];			//자음
	Sprite*			vowel[21];				//모음

	int start[3] = { 0x1100, 0x1161, 0x11A8 - 1 };
	int value, cho, jung, jong;
	bool extract(wchar_t *str);
	void test(int argc, _TCHAR* agv[]);
	
	void HangulSet(wchar_t* str);
public:
	void Init();
	void ReleaseAll();

	void IntRender(int num, int x, int y, int size);
	void TextRender(const char* str, int x, int y, int size);
	void HangulRender(wchar_t* str, int x, int y, int size);
};

