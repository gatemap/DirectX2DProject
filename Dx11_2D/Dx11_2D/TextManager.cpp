#include "stdafx.h"
#include "TextManager.h"

void TextManager::Init()
{
	//�ѱ� �̹��� �߰�
	g_pTextureManager->AddTexture(L"Hangul", L"Hangul", L"HangulText.png", L"Sprite", L"Sprite.hlsl");

	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 5; j++) {
			if (5 * i + j > 18) break;
			consonant[5*i + j] = new Sprite(L"Hangul", j, i, 10, 5);
		}
	}

	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 5; j++) {
			if (5 * i + j > 20) break;
			vowel[5 * i + j] = new Sprite(L"Hangul", 5 + j, i, 10, 5);
		}
	}
	/*
	// ���� �̹��� �߰�
	g_pTextureManager->AddTexture(L"Number", L"Number", L"UIImages/GoldNumber.png", L"Sprite", L"Sprite.hlsl");
	// ���� ��������Ʈ ����
	for (int i = 0; i < 10; i++)
		m_pNumber[i] = new Sprite(L"Number", i, 0, 10, 1);

	// �빮�� �̹��� �߰�
	g_pTextureManager->AddTexture(L"UpperLetter", L"UpperLetter", L"UIImages/UpperLetter.png",		L"Sprite", L"Sprite.hlsl");
	// �ҹ��� �̹��� �߰�
	g_pTextureManager->AddTexture(L"LowerLetter", L"LowerLetter", L"UIImages/UpperLetter.png",		L"Sprite", L"Sprite.hlsl");

	// ���ĺ� ��������Ʈ ����
	for (int i = 0; i < 26; i++)
	{
		m_pUpperLetter[i] = new Sprite(L"UpperLetter", i, 0, 26, 1);
		
		m_pLowerLetter[i] = new Sprite(L"LowerLetter", i, 0, 26, 1);
	}
	*/
}

void TextManager::ReleaseAll()
{
	//int* data;
	//data = new int[10];

	//SAFE_DELETE_ARRAY(data);

	for (int i = 0; i < 10; i++)
		SAFE_DELETE(m_pNumber[i]);

	for (int i = 0; i < 26; i++)
	{
		SAFE_DELETE(m_pUpperLetter[i]);
		SAFE_DELETE(m_pLowerLetter[i]);
	}

	for (int i = 0; i < 19; i++) SAFE_DELETE(consonant[i]);
	for (int i = 0; i < 21; i++)SAFE_DELETE(vowel[i]);
}

void TextManager::IntRender(int num, int x, int y, int size)
{
	// 123456789 -> 1 2 3 4 5 6 7 8 9 0 : %, / ������ Ȱ��

	vector<int> vecNumber;
	vecNumber.push_back(num % 10);

	while (num > 9)
	{
		// 123456789 / 10 = 12345678.9 => 12345678
		num /= 10;
		vecNumber.push_back(num % 10);
	}

	for (int i = vecNumber.size() - 1; i >= 0; i--)
	{
		m_pNumber[vecNumber[i]]->SetConstantScale(size, size);
		m_pNumber[vecNumber[i]]->SetLBPos(x + (vecNumber.size() - 1 - i) * size * 0.7f, y - size);
		m_pNumber[vecNumber[i]]->UpdateAndRender();
	}
}

void TextManager::TextRender(const char* str, int x, int y, int size)
{
	float posX = x;

	for (int i = 0; i < strlen(str); i++)
	{
		int index = str[i] - 65;

		if (index >= 0 && index <= 25)
		{
			m_pUpperLetter[index]->SetConstantScale(size, size);
			m_pUpperLetter[index]->SetLBPos(posX, y - size);
			m_pUpperLetter[index]->UpdateAndRender();

			posX += size * 0.9f;
		}
		else if (index - 32 >= 0 && index - 32 <= 25)
		{
			m_pLowerLetter[index - 32]->SetConstantScale(size * 0.7f, size * 0.7f);
			m_pLowerLetter[index - 32]->SetLBPos(posX, y - size);
			m_pLowerLetter[index - 32]->UpdateAndRender();

			posX += size * 0.5f;
		}
		else
		{
			posX += size * 0.5f;
		}
	}
}
void TextManager::HangulSet(wchar_t * str)
{
	
}

void TextManager::HangulRender(wchar_t * str, int x, int y, int size)
{
	if (wcslen(str) == 1) {

	}
	else if (wcslen(str) == 2) {

	}
	else if (wcslen(str) == 3) {

	}
	else if (wcslen(str) == 4) {

	}
}

bool TextManager::extract(wchar_t * str)
{
	//���� �ʱ�ȭ
	value = cho = jung = jong = 0;

	//�ѱ۸� �ԷµǾ����� �˻�
	for (int i = 0; i < wcslen(str); i++) {
		//�����ڵ� �ѱ� ���ڿ� ���� �˻�(0xAC00 ~ -0xD7A3)
		if (str[i] < 0xAC00 || str[i] > 0xD7A3) {
			if (str[i] == 0x20) continue;	//0x20 : ����
			return false;
		}
	}
	for (int i = 0; i < wcslen(str); i++){
		//���� �˻�
		if (str[i] == 0x20) {
			wprintf(L" ");
			continue;
		}
		value = str[i] - 0xAC00;
		jong = value % 28;
		jung = ((value - jong) / 28) % 21;
		cho = ((value - jong) / 28) / 21;

		if (jong == 0x11A8) jong = 0;
		cho += start[0], jung += start[1], jong += start[2];

		wprintf(L"%c %c %c", cho, jung, (jong == 0x11A8 - 1) ? NULL : jong);
	}

	return true;
}

void TextManager::test(int argc, _TCHAR * agv[])
{
	setlocale(LC_ALL, "Korean");

	wchar_t str[] = L"�׽�Ʈ";
	wprintf(L"�Է� : %s\n��ȯ : ", str);
	
	if (!extract(str)) printf("�ѱ� ���ڸ� �Է� ����\n");
}
