#include "pch.h"
#include "GameApp.h"
#include "D2DRenderer.h"

GameApp* GameApp::m_pInstance = nullptr;
HWND GameApp::m_hWnd;

LRESULT CALLBACK DefaultWndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	return  GameApp::m_pInstance->WndProc(hWnd, message, wParam, lParam);
}

GameApp::GameApp(HINSTANCE hInstance)
	:m_hInstance(hInstance), m_szWindowClass(L"DefaultWindowCalss"), m_szTitle(L"GameApp"), m_nHeight(1080), m_nWidth(1920)
{
	std::wstring str(__FUNCTIONW__);
	str += L"\n";
	OutputDebugString(str.c_str());

	GameApp::m_pInstance = this;
	m_wcex.hInstance = hInstance;
	m_wcex.cbSize = sizeof(WNDCLASSEX);
	m_wcex.style = CS_HREDRAW | CS_VREDRAW;
	m_wcex.lpfnWndProc = DefaultWndProc;
	m_wcex.cbClsExtra = 0;
	m_wcex.cbWndExtra = 0;
	m_wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
	m_wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	m_wcex.lpszClassName = m_szWindowClass;
}

GameApp::~GameApp()
{
	std::wstring str(__FUNCTIONW__);
	str += L"\n";
	OutputDebugString(str.c_str());

	delete m_TimeManager;
	delete m_KeyManager;
	delete m_PathManager;
	delete m_ResourceManager;
	delete m_CameraManager;
	delete m_World;
}

// ������ ������ ���� ���� �ٸ��� �����Ƿ� ���,����,���̱⸸ �Ѵ�.
bool GameApp::Initialize()
{
	// ���
	RegisterClassExW(&m_wcex);

	//����
	m_hWnd = CreateWindowW(m_szWindowClass, m_szTitle, WS_OVERLAPPEDWINDOW,
		100, 100,	// ���� ��ġ
		m_nWidth, m_nHeight,	// ����,����
		nullptr, nullptr, m_hInstance, nullptr);

	if (!m_hWnd)
	{
		return false;
	}

	// ������ ���̱�
	ShowWindow(m_hWnd, SW_SHOW);
	UpdateWindow(m_hWnd);

	HRESULT hr = m_D2DRenderer.Initialize();

	RECT rc;
	GetClientRect(&rc);
	D2D1_SIZE_U size = D2D1::SizeU(
		static_cast<UINT>(rc.right - rc.left),
		static_cast<UINT>(rc.bottom - rc.top)
	);

	m_TimeManager->Initialize();
	m_KeyManager->Initialize();
	m_PathManager->Initialize();
	m_ResourceManager->Initialize(m_PathManager);
	
	m_CameraManager->Initialize(size);

	if (FAILED(hr))
	{
		MessageBoxComError(hr);
	}

	return true;
}

void GameApp::Loop()
{
	// PeekMessage �޼����� ������ true,������ false
	while (TRUE)
	{
		if (PeekMessage(&m_msg, NULL, 0, 0, PM_REMOVE))
		{
			if (m_msg.message == WM_QUIT)
				break;

			//������ �޽��� ó�� 
			TranslateMessage(&m_msg); // Ű�Է°��� �޽��� ��ȯ  WM_KEYDOWN -> WM_CHAR
			DispatchMessage(&m_msg);
		}
		else
		{
			Update();
			Render();
		}
	}


	//return (int)m_msg.wParam;
}

void GameApp::Update()
{
	m_TimeManager->Update();
	m_KeyManager->Update();
	m_CameraManager->Update(m_KeyManager, m_TimeManager);

	m_World->Update(m_TimeManager);

	CalculateFrameStats();
}

void GameApp::CalculateFrameStats()
{
	//�ش� �ڵ�� �ʴ� �������� ����ϰ�, 1������ ������ �ɸ��� �ð��� ����� ����Ѵ�.
	//�ش� ��ġ���� â�� ����ǥ���ٿ� �߰��ȴ�.

	static int frameCnt = -1;
	static float timeElapsed = 0.0f;

	frameCnt++;
	if (frameCnt == 0)
		return;

	timeElapsed += m_TimeManager->GetfDT();

	//1�ʵ����� ������ �ð��� ����� ����մϴ�.
	if (timeElapsed >= 1.0f)
	{
		float fps = (float)frameCnt;  //Frame Per Second
		float spf = 1000.0f / fps;   // MilliSecond Per Frame

		std::wstring windowText;
		windowText.append(m_szTitle);
		windowText.append(L"  FPS: ");
		windowText.append(std::to_wstring(fps));
		windowText.append(L"  SPF: ");
		windowText.append(std::to_wstring(spf));
		SetWindowText(m_hWnd, windowText.c_str());

		//���� ��������� ����
		frameCnt = 0;
		timeElapsed -= 1.0f;
	}
}

void GameApp::Render()
{
	D2DRenderer::m_pD2DRenderTarget->BeginDraw();

	D2D1::ColorF color(D2D1::ColorF::Red);

	D2DRenderer::m_pD2DRenderTarget->Clear(color);

	// �׸��� ��
	D2DRenderer::m_pD2DRenderTarget->EndDraw();
}



BOOL GameApp::GetClientRect(LPRECT lpRect)
{
	return ::GetClientRect(m_hWnd, lpRect);
}

int GameApp::MessageBoxComError(HRESULT hr)
{
	_com_error err(hr);
	return ::MessageBox(m_hWnd, err.ErrorMessage(), L"FAILED", MB_OK);
}

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
LRESULT CALLBACK GameApp::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	std::wstring str;
	switch (message)
	{
	//case WM_KEYDOWN:
	//	if (wParam == VK_LEFT)
	//	{
	//		m_CameraManager->AddCameraLocation(-10.f, 0.f);
	//	}
	//	else if (wParam == VK_RIGHT)
	//	{
	//		m_CameraManager->AddCameraLocation(10.f, 0.f);
	//	}
	//	else if (wParam == VK_UP)
	//	{
	//		m_CameraManager->AddCameraLocation(0.f, 10.f);
	//	}
	//	else if (wParam == VK_DOWN)
	//	{
	//		m_CameraManager->AddCameraLocation(0.f, -10.f);
	//	}


	//	str = L"Camera X : " + to_wstring(m_CameraManager->m_locCameraX) + L" Camera Y : " + std::to_wstring(m_CameraManager->m_locCameraY);
	//	SetWindowText(hWnd, str.c_str());
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