// Dx11_2D.cpp : 응용 프로그램에 대한 진입점을 정의합니다.
//

#include "stdafx.h"
#include "Dx11_2D.h"
#include "MainGame.h"

#define MAX_LOADSTRING 100

// 전역 변수:
HINSTANCE	g_hInst;											// 현재 인스턴스입니다.
HWND		g_hWnd;												// 윈도우 핸들

WCHAR		szTitle[MAX_LOADSTRING] = L"게임을 만들어 보자~";		// 제목 표시줄 텍스트입니다.
MainGame*	pMainGame;
POINT		ptAdjWinSize;

// Dx11 전역 변수:
IDXGISwapChain* g_pSwapChain;			// 렌더 버퍼(모든 윈도우) 관리 변수 : 클리어, 비긴, 엔드, 프레젠트
ID3D11Device* g_pDevice;				// 하나의 장치(창)에 대한 버퍼, 텍스쳐 등 생성 관리를 위한 인터페이스 (CPU)
ID3D11DeviceContext* g_pDeviceContext;	// 생성 된 리소스를 관리하기 위한 인터페이스 (GPU -> 텍스쳐 렌더링)
ID3D11RenderTargetView* g_pRTV;			// 렌더타겟 지정 포인터

// 이 코드 모듈에 포함된 함수의 선언을 전달합니다:
ATOM                MyRegisterClass(HINSTANCE hInstance);
void                InitInstance(HINSTANCE, int);
void				InitDirectX(HINSTANCE);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    // 전역 문자열을 초기화합니다.
    MyRegisterClass(hInstance);
    // 응용 프로그램 초기화를 수행합니다:
	InitInstance(hInstance, nCmdShow);
	// DirectX 초기화
	InitDirectX(hInstance);

	pMainGame = new MainGame;
	pMainGame->Init();
	ImGui::Create(g_hWnd, g_pDevice, g_pDeviceContext);	// ImGui 생성
	ImGui::StyleColorsDark();	// 스타일 선택

	g_pKeyManger->Init();
	g_pTimeManager->Init();

    MSG msg;

	while (true)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			if (msg.message == WM_QUIT)
				break;

			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else
		{
			g_pTimeManager->Update(60.0f);
			g_pSoundManager->Update();
			ImGui::Update();

			pMainGame->Update();
			pMainGame->Render();
		}
	}

	ImGui::Delete(); // ImGui 해제
	SAFE_DELETE(pMainGame);

	g_pKeyManger->ReleaseInstance();
	g_pTimeManager->ReleaseInstance();
	g_pTextureManager->ReleaseInstance();
	g_pSoundManager->ReleaseInstance();

	SAFE_RELEASE(g_pSwapChain);
	SAFE_RELEASE(g_pDevice);
	SAFE_RELEASE(g_pDeviceContext);
	SAFE_RELEASE(g_pRTV);

    return (int) msg.wParam;
}



//
//  함수: MyRegisterClass()
//
//  용도: 창 클래스를 등록합니다.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;	//WNDCLASS : 윈도우의 정보를 저장하기 위한 구조체

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = CS_HREDRAW | CS_VREDRAW;									// 윈도우 스타일
    wcex.lpfnWndProc    = WndProc;													// 윈도우 프로시져
    wcex.cbClsExtra     = NULL;														// 클래스 여분 메모리
    wcex.cbWndExtra     = NULL;														// 윈도우 여분 메모리
    wcex.hInstance      = hInstance;												// 인스턴스
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_DX112D));			// 아이콘
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);							// 커서
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);									// 백그라운드
    wcex.lpszMenuName   = NULL;														// 메뉴 이름(NULL 메유 없앰)
    wcex.lpszClassName  = szTitle;													// 클래스 이름
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));		// 작은 아이콘

    return RegisterClassExW(&wcex);	// 윈도우 클래스 등록
}

//
//   함수: InitInstance(HINSTANCE, int)
//
//   용도: 인스턴스 핸들을 저장하고 주 창을 만듭니다.
//
//   주석:
//
//        이 함수를 통해 인스턴스 핸들을 전역 변수에 저장하고
//        주 프로그램 창을 만든 다음 표시합니다.
//
void InitInstance(HINSTANCE hInstance, int nCmdShow)
{
	g_hInst = hInstance; // 인스턴스 핸들을 전역 변수에 저장합니다.

   // 화면 해상도 얻기
	int nResolutionX = GetSystemMetrics(SM_CXSCREEN);
	int nResolutionY = GetSystemMetrics(SM_CYSCREEN);
	// 창 화면 중앙 배치 위치 계산
	int nWinPosX = nResolutionX / 2 - WINSIZEX / 2;
	int nWinPosY = nResolutionY / 2 - WINSIZEY / 2 - 40;

	HWND hWnd = CreateWindowW(
		szTitle,				// 윈도우 클래스 이름
		szTitle,				// 타이틀바에 띠울 이름
		WS_OVERLAPPEDWINDOW,	// 윈도우 스타일
		nWinPosX,				// 윈도우 화면 좌표 x
		nWinPosY,				// 윈도우 화면 좌표 y
		WINSIZEX,				// 윈도우 가로 사이즈
		WINSIZEY,				// 윈도우 세로 사이즈
		nullptr,				// 부모 윈도우
		nullptr,				// 메뉴 핸들
		hInstance,				// 인스턴스 지정
		nullptr);				// 자식 윈도우를 생성하면 지정해주고 그렇지 않으면 NULL

	assert(hWnd);

	g_hWnd = hWnd;				// 윈도우 핸들을 전역 변수에 저장

	// 윈도우 사이즈 조정 (타이틀바 및 메뉴 사이즈 실 사이즈에서 제외)
	RECT rt = { nWinPosX, nWinPosY, nWinPosX + WINSIZEX, nWinPosY + WINSIZEY };
	AdjustWindowRect(&rt, WS_OVERLAPPEDWINDOW, false);
	ptAdjWinSize.x = rt.right - rt.left;
	ptAdjWinSize.y = rt.bottom - rt.top;
	MoveWindow(g_hWnd, nWinPosX, nWinPosY, ptAdjWinSize.x, ptAdjWinSize.y, TRUE);

	ShowWindow(hWnd, nCmdShow);	// 화면에 창을 보여준다.
	UpdateWindow(hWnd);			// 창 업데이트
}

void InitDirectX(HINSTANCE hInstance)
{
	//Create g_pDevice and g_pDeviceContext, g_pSwapChain
	{
		DXGI_MODE_DESC bufferDesc;
		ZeroMemory(&bufferDesc, sizeof(DXGI_MODE_DESC));	// DXGI 다이렉트X 그래픽 인터페이스

		bufferDesc.Width = WINSIZEX;
		bufferDesc.Height = WINSIZEY;
		bufferDesc.RefreshRate.Numerator = 10;
		bufferDesc.RefreshRate.Denominator = 0;
		bufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
		bufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
		bufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;


		DXGI_SWAP_CHAIN_DESC desc;
		ZeroMemory(&desc, sizeof(DXGI_SWAP_CHAIN_DESC));

		desc.BufferDesc = bufferDesc;
		desc.SampleDesc.Count = 1;
		desc.SampleDesc.Quality = 0;
		desc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
		desc.BufferCount = 1;
		desc.OutputWindow = g_hWnd;
		desc.Windowed = TRUE;
		desc.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;

		HRESULT hr = D3D11CreateDeviceAndSwapChain
		(
			NULL, D3D_DRIVER_TYPE_HARDWARE, NULL, NULL, NULL, NULL,
			D3D11_SDK_VERSION, &desc, &g_pSwapChain, &g_pDevice, NULL, &g_pDeviceContext
		);
		assert(SUCCEEDED(hr));
	}

	//Create BackBuffer
	{
		HRESULT hr;

		ID3D11Texture2D* BackBuffer;
		hr = g_pSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (void**)&BackBuffer);
		assert(SUCCEEDED(hr));

		// 백버퍼의 렌더타겟 뷰를 생성
		hr = g_pDevice->CreateRenderTargetView(BackBuffer, NULL, &g_pRTV); // 뷰에서 엑세스 하는 리소스, 렌더 타겟 뷰의 정의, 렌더 타겟 뷰를 받아올 변수
		assert(SUCCEEDED(hr));
		BackBuffer->Release();

		// 렌더타겟 뷰를 Output-Merger의 렌더 타겟으로 설정
		g_pDeviceContext->OMSetRenderTargets(1, &g_pRTV, NULL); // 렌더타겟수, 렌더타겟 뷰의 배열, 렌더링 파이프 라인에 넘겨주는 깊이/스텐실 뷰의 포인터(깊이/스텐실 버퍼 설정 x)
	}

	//Create Viewport
	{
		D3D11_VIEWPORT viewport = { 0 };

		viewport.TopLeftX = 0;
		viewport.TopLeftY = 0;
		viewport.Width = WINSIZEX;
		viewport.Height = WINSIZEY;

		g_pDeviceContext->RSSetViewports(1, &viewport);
	}

	// Disable DepthStencil
	{
		D3D11_DEPTH_STENCIL_DESC desc = { 0, };

		ID3D11DepthStencilState* depthStencilState;
		g_pDevice->CreateDepthStencilState(&desc, &depthStencilState);

		g_pDeviceContext->OMSetDepthStencilState(depthStencilState, 0xFF);
		SAFE_RELEASE(depthStencilState);
	}

	// Disable CullMode
	{
		D3D11_RASTERIZER_DESC desc;
		ZeroMemory(&desc, sizeof(D3D11_RASTERIZER_DESC));

		desc.CullMode = D3D11_CULL_NONE;
		desc.FillMode = D3D11_FILL_SOLID;

		ID3D11RasterizerState* rasterizerState;
		g_pDevice->CreateRasterizerState(&desc, &rasterizerState);

		g_pDeviceContext->RSSetState(rasterizerState);
		SAFE_RELEASE(rasterizerState);
	}
}

//
//  함수: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  용도: 주 창의 메시지를 처리합니다.
//
//  WM_COMMAND  - 응용 프로그램 메뉴를 처리합니다.
//  WM_PAINT    - 주 창을 그립니다.
//  WM_DESTROY  - 종료 메시지를 게시하고 반환합니다.
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	if (ImGui::WndProc(hWnd, message, wParam, lParam))
		return true;

    switch (message)
    {
	case WM_GETMINMAXINFO: // 창의 최소 최대 크기 고정
		((MINMAXINFO*)lParam)->ptMaxTrackSize.x = ptAdjWinSize.x;
		((MINMAXINFO*)lParam)->ptMaxTrackSize.y = ptAdjWinSize.y;
		((MINMAXINFO*)lParam)->ptMinTrackSize.x = ptAdjWinSize.x;
		((MINMAXINFO*)lParam)->ptMinTrackSize.y = ptAdjWinSize.y;
		break;
	case WM_KEYDOWN:
		if (wParam == VK_ESCAPE)
		{
			DestroyWindow(hWnd);
		}
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}