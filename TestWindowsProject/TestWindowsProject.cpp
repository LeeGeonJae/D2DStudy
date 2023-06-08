// TestWindowsProject.cpp : 애플리케이션에 대한 진입점을 정의합니다.
//

#include "framework.h"
#include "TestWindowsProject.h"

#include "../TestStaticLib/MyClass.h"
#include <d2d1.h>
#include <d2d1_1helper.h>
#include <dwrite.h>

#define MAX_LOADSTRING 100

// 전역 변수:
HINSTANCE g_hInst;                                // 현재 인스턴스입니다.
HWND g_hWnd;
WCHAR szTitle[MAX_LOADSTRING];                  // 제목 표시줄 텍스트입니다.
WCHAR szWindowClass[MAX_LOADSTRING];            // 기본 창 클래스 이름입니다.

// 기본 D2D사용을 위한 Factory의 인터페이스 포인터
ID2D1Factory* g_pD2D1Factory;
ID2D1HwndRenderTarget* g_pD2DRenderTarget;

// 렌더 타겟에서 생성한 브러쉬의 인터페이스 포인터
ID2D1SolidColorBrush* g_pGrayBrush;
ID2D1SolidColorBrush* g_pBlackBrush;

// 텍스트 출력을 위한 객체 인터페이스 포인터
IDWriteFactory* g_pWriteFactory;
IDWriteTextFormat* g_pWriteTextFormat;

// 이 코드 모듈에 포함된 함수의 선언을 전달합니다:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

// 렌더 타겟을 쓰기 위한 전처리 과정
bool InitD2D()
{
    HRESULT hr;

    // COM사용
    hr = CoInitialize(NULL);
    if (FAILED(hr))
        return false;

    // 렌더타겟을 만들 수 있는 팩토리 객체를 생성하고 인터페이스 포인터를 얻어온다.
    hr = D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, &g_pD2D1Factory);
    if (FAILED(hr))
        return false;

    // 이미 윈도우가 만들어진 상태에서 윈도우 사이즈를 구한다.
    RECT rc;
    GetClientRect(g_hWnd, &rc);

    D2D1_SIZE_U size = D2D1::SizeU(
        static_cast<UINT>(rc.right - rc.left),
        static_cast<UINT>(rc.bottom - rc.top)
    );

    // 팩토리로 윈도우 핸들, 사이즈를 넘겨 렌더타겟을 만든다.
    hr = g_pD2D1Factory->CreateHwndRenderTarget(
        D2D1::RenderTargetProperties(), 
        D2D1::HwndRenderTargetProperties(g_hWnd, size),
        &g_pD2DRenderTarget
    );
    if (FAILED(hr))
        return false;

    hr = g_pD2DRenderTarget->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::Gray), &g_pGrayBrush);
    if (FAILED(hr))
        return false;

    hr = g_pD2DRenderTarget->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::Black), &g_pBlackBrush);
    if (FAILED(hr))
        return false;

    hr = DWriteCreateFactory(
        DWRITE_FACTORY_TYPE_SHARED,
        __uuidof(g_pWriteFactory),
        reinterpret_cast<IUnknown**>(&g_pWriteFactory)
    );
    if (FAILED(hr))
        return false;

    hr = g_pWriteFactory->CreateTextFormat(
        L"Agency FB",
        NULL,
        DWRITE_FONT_WEIGHT_NORMAL,
        DWRITE_FONT_STYLE_NORMAL,
        DWRITE_FONT_STRETCH_NORMAL,
        50.f,
        L"", //locale
        &g_pWriteTextFormat
    );
    if (FAILED(hr))
        return false;

    // Center the text horizontally and vertically.
    g_pWriteTextFormat->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_LEADING);
    g_pWriteTextFormat->SetParagraphAlignment(DWRITE_PARAGRAPH_ALIGNMENT_CENTER);

    return true;
}

void Uninitialize()
{
    // 만드는 순서 거꾸로 릴리즈
    g_pWriteFactory->Release();
    g_pWriteTextFormat->Release();

    g_pGrayBrush->Release();
    g_pBlackBrush->Release();

    // 해제
    g_pD2DRenderTarget->Release();
    g_pD2D1Factory->Release();

    //COM사용끝
    CoUninitialize();
}

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: 여기에 코드를 입력합니다.

    // 전역 문자열을 초기화합니다.
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_TESTWINDOWSPROJECT, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // 애플리케이션 초기화를 수행합니다:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    InitD2D();

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_TESTWINDOWSPROJECT));

    MSG msg;

    // 기본 메시지 루프입니다:

    while (true)
    {
        if(PeekMessage(&msg, g_hWnd, 0, 0, PM_REMOVE))
        {
            if (msg.message == WM_QUIT)
                break;

            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
        else
        {
            // 그리기 시작 알린다.
            g_pD2DRenderTarget->BeginDraw();

            D2D1::ColorF color(D2D1::ColorF::Red);

            g_pD2DRenderTarget->Clear(color);

            D2D1_RECT_F rect;
            rect.left = 100;
            rect.right = rect.left + 300;
            rect.top = 100;
            rect.bottom = rect.top +300;

            g_pD2DRenderTarget->FillRectangle(rect, g_pGrayBrush);

            rect.left = 400;
            rect.right = rect.left + 300;
            rect.top = 400;
            rect.bottom = rect.top + 300;

            g_pD2DRenderTarget->DrawRectangle(rect, g_pBlackBrush);

            static const WCHAR sc_helloWorld[] = L"Hello, World!";
            D2D1_SIZE_F renderTargetSize = g_pD2DRenderTarget->GetSize();

            g_pD2DRenderTarget->DrawText(
                sc_helloWorld,
                ARRAYSIZE(sc_helloWorld) - 1,
                g_pWriteTextFormat,
                D2D1::RectF(0, 0, renderTargetSize.width, renderTargetSize.height),
                g_pBlackBrush
            );
            


            // 그리기 끝
            g_pD2DRenderTarget->EndDraw();
        }
    }

    Uninitialize();
    return (int) msg.wParam;
}



//
//  함수: MyRegisterClass()
//
//  용도: 창 클래스를 등록합니다.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_TESTWINDOWSPROJECT));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_TESTWINDOWSPROJECT);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
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
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   g_hInst = hInstance; // 인스턴스 핸들을 전역 변수에 저장합니다.

   g_hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

   if (!g_hWnd)
   {
      return FALSE;
   }

   ShowWindow(g_hWnd, nCmdShow);
   UpdateWindow(g_hWnd);

   return TRUE;
}

//
//  함수: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  용도: 주 창의 메시지를 처리합니다.
//
//  WM_COMMAND  - 애플리케이션 메뉴를 처리합니다.
//  WM_PAINT    - 주 창을 그립니다.
//  WM_DESTROY  - 종료 메시지를 게시하고 반환합니다.
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_COMMAND:
        {
            int wmId = LOWORD(wParam);
            // 메뉴 선택을 구문 분석합니다:
            switch (wmId)
            {
            case IDM_ABOUT:
                DialogBox(g_hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
                break;
            case IDM_EXIT:
                DestroyWindow(hWnd);
                break;
            default:
                return DefWindowProc(hWnd, message, wParam, lParam);
            }
        }
        break;
    case WM_PAINT:
        {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hWnd, &ps);
            // TODO: 여기에 hdc를 사용하는 그리기 코드를 추가합니다...
            EndPaint(hWnd, &ps);
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

// 정보 대화 상자의 메시지 처리기입니다.
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
        return (INT_PTR)TRUE;

    case WM_COMMAND:
        if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
        {
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        }
        break;
    }
    return (INT_PTR)FALSE;
}
