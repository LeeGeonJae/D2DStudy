// DemoApp.cpp : 애플리케이션에 대한 진입점을 정의합니다.
//

#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>

#include "framework.h"
#include "DemoApp.h"

#include "../D2DRender/GameApp.h"
#include "../D2DRender/D2DRenderer.h"
#include "../D2DRender/TimeManager.h"
#include "../D2DRender/SunObject.h"
#include "../D2DRender/BoxObject.h"
#include <time.h>

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPWSTR    lpCmdLine,
	_In_ int       nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

	// 전역 문자열을 초기화합니다.
	{
		DemoApp App(hInstance);

		_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

		App.Initialize();
		App.Loop();
	}
	//_CrtSetReportMode(_CRT_WARN, _CRTDBG_MODE_DEBUG);
	_CrtDumpMemoryLeaks();

	return (int)1;
}

DemoApp::DemoApp(HINSTANCE hInstance)
	: GameApp::GameApp(hInstance)
{
	// DemoApp에서 리소스를 얻어와 클래스 설정하기
	LoadStringW(hInstance, IDS_APP_TITLE, m_szTitle, MAX_LOADSTRING);
	LoadStringW(hInstance, IDC_DEMOAPP, m_szWindowClass, MAX_LOADSTRING);

	m_wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_DEMOAPP));
	m_wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
	//m_wcex.lpszMenuName = MAKEINTRESOURCEW(IDC_DEMOAPP);
	m_wcex.hIconSm = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_SMALL));
	m_hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_DEMOAPP));
}

DemoApp::~DemoApp()
{
}

void DemoApp::Update()
{
	GameApp::Update();



	m_World->Update(m_TimeManager);
}

void DemoApp::Render()
{
	D2DRenderer::m_pD2DRenderTarget->BeginDraw();
	D2D1::ColorF color(D2D1::ColorF::Black);

	D2DRenderer::m_pD2DRenderTarget->Clear(color);

	m_World->Render(D2DRenderer::m_pD2DRenderTarget);

	D2DRenderer::m_pD2DRenderTarget->EndDraw();
}

bool DemoApp::Initialize()
{
	GameApp::Initialize();

	srand((unsigned int)time(NULL));


	// 오브젝트 생성
	SunObject* Object = m_World->CreateGameObject<SunObject>();
	SunObject* Object1 = m_World->CreateGameObject<SunObject>();
	SunObject* Object2 = m_World->CreateGameObject<SunObject>();
	SunObject* Object3 = m_World->CreateGameObject<SunObject>();
	SunObject* Object4 = m_World->CreateGameObject<SunObject>();
	BoxObject* BoxObj[2000];

	for (int i = 0; i < 2000; i++)
		BoxObj[i] = m_World->CreateGameObject<BoxObject>();

	// 월드가 가지고 있는 모든 오브젝트 세팅
	m_World->Init(m_ResourceManager, m_PathManager);

	// 오브젝트 세팅
	Object->SetLocation(900.f, 500.f);
	Object1->SetLocation(1900.f, 500.f);
	Object2->SetLocation(900.f, 1500.f);
	Object3->SetLocation(1900.f, 1500.f);
	Object4->SetLocation(1400.f, 900.f);

	for (int i = 0; i < 2000; i++)
	{
		int randomposX = rand() % 6000 - 3000;
		int randomposY = rand() % 3000 - 1000;
		BoxObj[i]->SetLocation((float)randomposX, (float)randomposY);
	}

	return false;
}