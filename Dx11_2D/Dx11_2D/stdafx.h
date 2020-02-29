// stdafx.h : 자주 사용하지만 자주 변경되지는 않는
// 표준 시스템 포함 파일 또는 프로젝트 특정 포함 파일이 들어 있는
// 포함 파일입니다.
//

#pragma once

#include "targetver.h"

#define WIN32_LEAN_AND_MEAN             // 거의 사용되지 않는 내용을 Windows 헤더에서 제외합니다.
// Windows 헤더 파일
#include <windows.h>

// C 런타임 헤더 파일입니다.
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>

// 여기서 프로그램에 필요한 추가 헤더를 참조합니다.
#include <assert.h>
#include <string>
#include <vector>
#include <time.h>
#include <map>
using namespace std;

// 전역 디파인
#define WINSIZEX 1280
#define WINSIZEY 720

#define INITX 640
#define INITY 360

#define SAFE_DELETE(p)			{ if(p) { delete(p); (p) = NULL; } }
#define SAFE_DELETE_ARRAY(p)	{ if(p) { delete[] (p); (p) = NULL; } }
#define SAFE_RELEASE(p)			{ if(p) { (p)->Release(); (p) = NULL; } }

#define GRAVITY 9.78f

// 전역 변수
extern HINSTANCE	g_hInst;
extern HWND			g_hWnd;

// 전역 함수
inline bool AABB(float x1, float y1, int sx1, int sy1,			//x, y = 중점, sx, sy = scale값
				float x2, float y2, int sx2, int sy2)
{
	float L1 = x1 - sx1 * 0.5f;
	float R1 = x1 + sx1 * 0.5f;
	float T1 = y1 + sy1 * 0.5f;
	float B1 = y1 - sy1 * 0.5f;

	float L2 = x2 - sx2 * 0.5f;
	float R2 = x2 + sx2 * 0.5f;
	float T2 = y2 + sy2 * 0.5f;
	float B2 = y2 - sy2 * 0.5f;

	if (((L2 > L1 && L2 < R1) || (R2 > L1 && R2 < R1)) &&
		((B2 > B1 && B2 < T1) || (T2 > B1 && T2 < T1)))
		return true;

	return false;
}

inline bool CircleCollision(float x1, float y1, int sx1, int sy1,
							float x2, float y2, int sx2, int sy2)
{
	float disX = x1 - x2;
	float disY = y1 - y2;
	float distance = sqrtf(disX * disX + disY * disY);

	int radius1 = (sx1 + sy1) * 0.25f;
	int radius2 = (sx2 + sy2) * 0.25f;

	if (distance < radius1 + radius2)
		return true;

	return false;
}

inline bool Collision(int b1, int h1, float x1, float y1, int b2, int h2, float x2, float y2) 
{
	bool isCol = false;

	float c1 = sqrtf(b1*b1*0.25f + h1 * h1*0.25f);
	float c2 = sqrtf(b2*b2*0.25f + h2 * h2*0.25f);
	float distanceXY = sqrtf((x2 - x1)*(x2 - x1) + (y2 - y1)*(y2 - y1));
	if (c1 + c2 >= distanceXY) isCol = true;

	return isCol;
}

#include "DXComponent.h"

// 매니져 클래스
#include "KeyManager.h"
#include "TimeManager.h"
#include "TextureManager.h"
#include "SoundManager.h"

// ImGui 헤더 및 라이브러라 추가
#include <imGui/imgui.h>
#include <imGui/imguiDx11.h>
#pragma comment(lib, "imGui/imgui.lib")

// 전역 클래스
#include "Rect.h"
#include "Sprite.h"
#include "Clip.h"
#include "Animation.h"