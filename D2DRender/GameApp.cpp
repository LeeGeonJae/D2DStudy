#include "pch.h"
#include "GameApp.h"
#include "D2DRenderer.h"
//
//  �Լ�: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  �뵵: �� â�� �޽����� ó���մϴ�.
//
//  WM_COMMAND  - ���ø����̼� �޴��� ó���մϴ�.
//  WM_PAINT    - �� â�� �׸��ϴ�.
//  WM_DESTROY  - ���� �޽����� �Խ��ϰ� ��ȯ�մϴ�.
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_PAINT:
    {
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(hWnd, &ps);
        // TODO: ���⿡ hdc�� ����ϴ� �׸��� �ڵ带 �߰��մϴ�...
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

// ���� ��ȭ ������ �޽��� ó�����Դϴ�.
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

GameApp::GameApp(HINSTANCE hInstance)
    :m_hInst(hInstance)
    , m_szWindowClass(L"DefaultWindowClass")
    , m_szTitle(L"DefalutWindowTitle")
{
    // Ư�� ����App�� ������� �⺻ ����
    m_wcex.cbSize = sizeof(WNDCLASSEX);
    m_wcex.style = CS_HREDRAW | CS_VREDRAW;
    m_wcex.lpfnWndProc = WndProc;
    m_wcex.cbClsExtra = 0;
    m_wcex.cbWndExtra = 0;
    m_wcex.hInstance = m_hInst;
    m_wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    m_wcex.lpszMenuName = NULL;
    m_wcex.lpszClassName = m_szWindowClass;

}

GameApp::~GameApp()
{
}

bool GameApp::Initialize()
{

    // m_wcex�� �غ�Ǿ��ٰ� ����
    RegisterClassExW(&m_wcex);

    m_hWnd = CreateWindowW(m_szWindowClass, m_szTitle, WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, m_hInst, nullptr);

    if (!m_hWnd)
    {
        return FALSE;
    }

    ShowWindow(m_hWnd, SW_SHOW);
    UpdateWindow(m_hWnd);
    
    m_Renderer = new D2DRenderer;
    m_Renderer->Initialize(m_hWnd);

    return false;
}

void GameApp::Loop()
{
    while (true)
    {
        if (PeekMessage(&m_msg, m_hWnd, 0, 0, PM_REMOVE))
        {
            if (m_msg.message == WM_QUIT)
                break;

            TranslateMessage(&m_msg);
            DispatchMessage(&m_msg);
        }
        else
        {
            Update();
            Render();
        }
    }
}

void GameApp::Update()
{
}

void GameApp::Render()
{
}

void GameApp::Uninitalize()
{
    m_Renderer->Uninitialize();
    delete m_Renderer;
}
