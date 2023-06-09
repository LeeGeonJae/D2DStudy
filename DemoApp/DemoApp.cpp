// DemoApp.cpp : 애플리케이션에 대한 진입점을 정의합니다.
//

#include "framework.h"
#include "DemoApp.h"

#pragma comment(lib, "windowscodecs.lib")

// 전역 변수:
HINSTANCE hInst;                                // 현재 인스턴스입니다.


// 이 코드 모듈에 포함된 함수의 선언을 전달합니다:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: 여기에 코드를 입력합니다.

    // 전역 문자열을 초기화합니다.
    DemoApp* App = new DemoApp(hInstance);
    App->Initialize();
    App->Loop();
    App->Uninitalize();

    return 1;
}

DemoApp::DemoApp(HINSTANCE hInstance)
    :GameApp(hInstance)
{
    // DemoApp에서 리소스를 얻어와 클래스 설정하기
    m_hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_DEMOAPP));
    LoadStringW(hInstance, IDS_APP_TITLE, m_szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_DEMOAPP, m_szWindowClass, MAX_LOADSTRING);

	m_wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_DEMOAPP));
	m_wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
    //m_wcex.lpszMenuName = MAKEINTRESOURCEW(IDC_DEMOAPP);
	m_wcex.hIconSm = LoadIcon(m_wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));
}

DemoApp::~DemoApp()
{
}

void DemoApp::Update()
{

}

void DemoApp::Render()
{
    // 그리기 시작 알린다.
    m_Renderer->m_pD2DRenderTarget->BeginDraw();

    D2D1::ColorF color(D2D1::ColorF::Red);

    m_Renderer->m_pD2DRenderTarget->Clear(color);

    D2D1_RECT_F rect;
    rect.left = 100;
    rect.right = rect.left + 500;
    rect.top = 100;
    rect.bottom = rect.top + 500;

    m_Renderer->m_pD2DRenderTarget->FillRectangle(rect, m_Renderer->m_pGrayBrush);

    rect.left = 400;
    rect.right = rect.left + 300;
    rect.top = 400;
    rect.bottom = rect.top + 300;

    m_Renderer->m_pD2DRenderTarget->DrawRectangle(rect, m_Renderer->m_pBlackBrush);

    static const WCHAR sc_helloWorld[] = L"Hello, World!";
    D2D1_SIZE_F renderTargetSize = m_Renderer->m_pD2DRenderTarget->GetSize();

    m_Renderer->m_pD2DRenderTarget->DrawText(
        sc_helloWorld,
        ARRAYSIZE(sc_helloWorld) - 1,
        m_Renderer->m_pWriteTextFormat,
        D2D1::RectF(0, 0, renderTargetSize.width, renderTargetSize.height),
        m_Renderer->m_pBlackBrush
    );

    m_Renderer->m_pD2DRenderTarget->SetTransform(D2D1::Matrix3x2F::Translation(500, 0));
    m_Renderer->m_pD2DRenderTarget->DrawBitmap(m_Renderer->m_pD2DBitmap);

    // 그리기 시작 알린다.
    m_Renderer->m_pD2DRenderTarget->EndDraw();
}
