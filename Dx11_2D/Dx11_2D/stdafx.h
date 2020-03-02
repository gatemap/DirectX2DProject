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
#include <list>
#include <map>
using namespace std;

// 전역 디파인
#define WINSIZEX 1280
#define WINSIZEY 720
#define INITX 640
#define INITY 360
#define CONSTANT_FPS 60.0f

#define SAFE_DELETE(p)			{ if(p) { delete(p); (p) = NULL; } }
#define SAFE_DELETE_ARRAY(p)	{ if(p) { delete[] (p); (p) = NULL; } }
#define SAFE_RELEASE(p)			{ if(p) { (p)->Release(); (p) = NULL; } }

#define GRAVITY 9.78f

// 전역 변수
extern HINSTANCE	g_hInst;
extern HWND			g_hWnd;

#include "DXComponent.h"
#include "GameComponant.h"

// 매니져 클래스
#include "KeyManager.h"
#include "TimeManager.h"
#include "TextureManager.h"
#include "SoundManager.h"
#include "Camera.h"

// ImGui 헤더 및 라이브러라 추가
#include <imGui/imgui.h>
#include <imGui/imguiDx11.h>
#pragma comment(lib, "imGui/imgui.lib")

// 전역 클래스
#include "Rect.h"
#include "Sprite.h"
#include "Clip.h"
#include "Animation.h"