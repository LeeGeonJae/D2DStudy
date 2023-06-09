// TestWindowsProject.cpp : 애플리케이션에 대한 진입점을 정의합니다.
//

#include "framework.h"
#include "TestWindowsProject.h"

#include "../TestStaticLib/MyClass.h"
#include <d2d1.h>
#include <d2d1_1helper.h>
#include <dwrite.h>
#include <wincodec.h>
#include <comdef.h>

#define MAX_LOADSTRING 100

// 전역 변수:
HINSTANCE g_hInst;                                // 현재 인스턴스입니다.
HWND g_hWnd;
WCHAR szTitle[MAX_LOADSTRING];                  // 제목 표시줄 텍스트입니다.
WCHAR szWindowClass[MAX_LOADSTRING];            // 기본 창 클래스 이름입니다.

// 기본 D2D사용을 위한 Factory의 인터페이스 포인터
ID2D1Factory* g_pD2D1Factory = NULL;
ID2D1HwndRenderTarget* g_pD2DRenderTarget = NULL;

// 렌더 타겟에서 생성한 브러쉬의 인터페이스 포인터
ID2D1SolidColorBrush* g_pGrayBrush = NULL;
ID2D1SolidColorBrush* g_pBlackBrush = NULL;

// 텍스트 출력을 위한 객체 인터페이스 포인터
IDWriteFactory* g_pWriteFactory = NULL;
IDWriteTextFormat* g_pWriteTextFormat = NULL;

// WIC 인터페이스
IWICImagingFactory* g_pIWICImagingFactory = NULL;

// 이미지로드후 생성하고 받아오는 인터페이스
ID2D1Bitmap* g_pD2DBitmap = NULL;

// 이 코드 모듈에 포함된 함수의 선언을 전달합니다:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);
HRESULT CreateD2DBitmapFromFile(const WCHAR* szFilePath, ID2D1Bitmap** pID2D1Bitmap);

// 렌더 타겟을 쓰기 위한 전처리 과정
bool InitD2D()
{
    HRESULT hr;

    // COM사용
	hr = CoInitialize(NULL);

    // 렌더타겟을 만들 수 있는 팩토리 객체를 생성하고 인터페이스 포인터를 얻어온다.
    if (SUCCEEDED(hr))
    {
        hr = D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, &g_pD2D1Factory);
    }

    // 이미 윈도우가 만들어진 상태에서 윈도우 사이즈를 구한다.
    RECT rc;
    GetClientRect(g_hWnd, &rc);

    D2D1_SIZE_U size = D2D1::SizeU(
        static_cast<UINT>(rc.right - rc.left),
        static_cast<UINT>(rc.bottom - rc.top)
    );

    // 팩토리로 윈도우 핸들, 사이즈를 넘겨 렌더타겟을 만든다.
    if (SUCCEEDED(hr))
    {
        hr = g_pD2D1Factory->CreateHwndRenderTarget(
            D2D1::RenderTargetProperties(),
            D2D1::HwndRenderTargetProperties(g_hWnd, size),
            &g_pD2DRenderTarget
        );
    }
    
    if (SUCCEEDED(hr))
    {
        hr = g_pD2DRenderTarget->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::Gray), &g_pGrayBrush);
    }

    // 회색 브러시 생성
    // Direct2D 렌더 타겟(g_pD2DRenderTarget)에서 회색을 나타내는 솔리드 브러시를 생성합니다.
    // CreateSolidColorBrush 함수는 D2D1::ColorF 구조체를 사용하여 지정된 색상으로 솔리드 브러시를 만듭니다.
    // 이 솔리드 브러시는 회색으로 설정되고, 생성된 브러시의 포인터는 g_pGrayBrush에 저장됩니다.
    if (SUCCEEDED(hr))
    {
        hr = g_pD2DRenderTarget->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::Black), &g_pBlackBrush);
    }

    // 검정색 브러시 생성
    // Direct2D 렌더 타겟(g_pD2DRenderTarget)에서 검정색을 나타내는 솔리드 브러시를 생성합니다.
    // CreateSolidColorBrush 함수를 사용하여 검정색 솔리드 브러시를 만듭니다.
    // 생성된 브러시의 포인터는 g_pBlackBrush에 저장됩니다.

    if (SUCCEEDED(hr))
    {
        hr = DWriteCreateFactory(
            DWRITE_FACTORY_TYPE_SHARED,
            __uuidof(g_pWriteFactory),
            reinterpret_cast<IUnknown**>(&g_pWriteFactory)
        );
    }

    // DirectWrite 팩토리 생성
    // DWriteCreateFactory 함수를 사용하여 DirectWrite 팩토리(g_pWriteFactory)를 생성합니다.
    // 이 팩토리를 사용하여 텍스트 렌더링과 관련된 작업을 수행할 수 있습니다.
    // DWRITE_FACTORY_TYPE_SHARED 플래그를 사용하여 공유 팩토리를 생성합니다.

    if (SUCCEEDED(hr))
    {
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
    }

    // 텍스트 형식 생성
    // CreateTextFormat 함수를 사용하여 텍스트 형식(g_pWriteTextFormat)을 생성합니다.
    // "Agency FB"라는 글꼴을 사용하고, 기본 설정으로 텍스트 형식을 초기화합니다.
    // 텍스트의 두께는 NORMAL, 스타일은 NORMAL, 스트레치는 NORMAL로 설정됩니다.
    // 텍스트 크기는 50.f로 설정되며, 현재 로캘(locale)은 사용하지 않습니다.
    // 생성된 텍스트 형식의 포인터는 g_pWriteTextFormat에 저장됩니다.

    // Center the text horizontally and vertically.
    g_pWriteTextFormat->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_LEADING);
    g_pWriteTextFormat->SetParagraphAlignment(DWRITE_PARAGRAPH_ALIGNMENT_CENTER);

    // 텍스트 정렬 설정
    // 텍스트 형식(g_pWriteTextFormat)에 대해 텍스트 정렬을 설정합니다.
    // SetTextAlignment 함수를 사용하여 텍스트를 수평으로 가운데에 정렬하고,
    // SetParagraphAlignment 함수를 사용하여 텍스트를 수직으로 가운데에 정렬합니다.

    if (SUCCEEDED(hr))
    {
        hr = CoCreateInstance(
            CLSID_WICImagingFactory,
            NULL,
            CLSCTX_INPROC_SERVER,
            IID_PPV_ARGS(&g_pIWICImagingFactory)
        );
    }

    // WIC 팩토리 생성
    // CoCreateInstance 함수를 사용하여 WIC(Windows Imaging Component) 팩토리(g_pIWICImagingFactory)를 생성합니다.
    // WIC 팩토리는 이미지 처리 작업에 사용되며, 이미지 디코딩, 변환 등을 처리할 수 있습니다.
    // CLSID_WICImagingFactory는 WIC 팩토리의 클래스 식별자이며, IID_PPV_ARGS는 인터페이스를 얻기 위한 매크로입니다.
    // 생성된 WIC 팩토리의 포인터는 g_pIWICImagingFactory에 저장됩니다.
    if (SUCCEEDED(hr))
    {
        hr = CoCreateInstance(
            CLSID_WICImagingFactory,
            NULL,
            CLSCTX_INPROC_SERVER,
            IID_PPV_ARGS(&g_pIWICImagingFactory)
        );
    }

    if (SUCCEEDED(hr))
    {
        hr = CreateD2DBitmapFromFile(L"..\\Resource\\atk_1.png", &g_pD2DBitmap);
    }

    return true;
}

void Uninitialize()
{
    if (g_pD2DBitmap != NULL) g_pD2DBitmap->Release();

    // WIC해제
	if (g_pIWICImagingFactory != NULL)
		g_pIWICImagingFactory->Release();

	// 만드는 순서 거꾸로 릴리즈
	if (g_pWriteFactory != NULL)
		g_pWriteFactory->Release();
	if (g_pWriteTextFormat != NULL)
		g_pWriteTextFormat->Release();

	if (g_pGrayBrush != NULL)
		g_pGrayBrush->Release();
	if (g_pBlackBrush != NULL)
		g_pBlackBrush->Release();

	// 해제
	if (g_pD2DRenderTarget != NULL)
		g_pD2DRenderTarget->Release();
	if (g_pD2D1Factory != NULL)
		g_pD2D1Factory->Release();

    //COM사용끝
    CoUninitialize();
}

HRESULT CreateD2DBitmapFromFile(const WCHAR* szFilePath, ID2D1Bitmap** pID2D1Bitmap)
{
    HRESULT hr = S_OK;

    // 디코더 생성
    IWICBitmapDecoder* pDecoder = NULL;

    // 파일명을 사용하여 이미지를 디코딩하는 디코더 생성
    hr = g_pIWICImagingFactory->CreateDecoderFromFilename(
        szFilePath,                      // 디코딩할 이미지 파일 경로
        NULL,                            // 특정 벤더를 선호하지 않음
        GENERIC_READ,                    // 파일에 대한 읽기 접근 권한
        WICDecodeMetadataCacheOnDemand,  // 필요할 때 메타데이터 캐시
        &pDecoder                        // 디코더를 가리키는 포인터
    );

    // 디코더로부터 이미지의 첫 번째 프레임 가져오기
    IWICBitmapFrameDecode* pFrame = NULL;

    if (SUCCEEDED(hr))
    {
        hr = pDecoder->GetFrame(0, &pFrame);
    }

    IWICFormatConverter* pConverter = NULL;

    // 단계 3: 프레임을 32bppPBGRA 형식으로 변환하기 위한 포맷 컨버터 생성
    if (SUCCEEDED(hr))
    {
        hr = g_pIWICImagingFactory->CreateFormatConverter(&pConverter);
    }

    if (SUCCEEDED(hr))
    {
        hr = pConverter->Initialize(
            pFrame,                          // 변환할 입력 비트맵
            GUID_WICPixelFormat32bppPBGRA,   // 목적지 픽셀 형식
            WICBitmapDitherTypeNone,         // 지정된 디더 패턴
            NULL,                            // 특정 팔레트 지정 없음
            0.f,                             // 알파 임계값
            WICBitmapPaletteTypeCustom       // 팔레트 변환 유형
        );
    }

    // D2D 렌더 타겟으로부터 WIC 비트맵으로부터 비트맵 생성
    g_pD2DRenderTarget->CreateBitmapFromWicBitmap(pConverter, NULL, pID2D1Bitmap);

    //pFrame->AddRef();

    if (pFrame != NULL)
        pFrame->Release();

    if (pDecoder != NULL)
        pDecoder->Release();

    if (pConverter != NULL)
        pConverter->Release();

    if (FAILED(hr))
    {
        _com_error err(hr);
        MessageBox(g_hWnd, err.ErrorMessage(), L"FAILED", MB_OK);
    }

    return hr;
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

            // 0, 0
            g_pD2DRenderTarget->SetTransform(D2D1::Matrix3x2F::Identity());
            g_pD2DRenderTarget->DrawBitmap(g_pD2DBitmap);

            // 300, 300
            g_pD2DRenderTarget->SetTransform(D2D1::Matrix3x2F::Identity());
            D2D1_SIZE_F size = g_pD2DBitmap->GetSize();
            rect.left = 300;
            rect.top = 300;
            rect.right = rect.left + size.width;
            rect.bottom = rect.top + size.height;
            g_pD2DRenderTarget->DrawBitmap(g_pD2DBitmap, rect);

            // Transform만 적용한다
            g_pD2DRenderTarget->SetTransform(D2D1::Matrix3x2F::Translation(0,500));
            g_pD2DRenderTarget->DrawBitmap(g_pD2DBitmap);

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
