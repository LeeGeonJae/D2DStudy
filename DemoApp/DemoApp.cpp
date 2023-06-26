// DemoApp.cpp : 애플리케이션에 대한 진입점을 정의합니다.
//


#include "framework.h"
#include "DemoApp.h"

#include "../D2DRender/GameApp.h"
#include "../D2DRender/D2DRenderer.h"
#include "../D2DRender/TimeManager.h"
#include "../D2DRender/AnimationAsset.h"
#include "../D2DRender/AnimationInstance.h"
#include "../D2DRender/SphereComponent.h"
#include "../D2DRender/Component.h"

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
    _In_opt_ HINSTANCE hPrevInstance,
    _In_ LPWSTR    lpCmdLine,
    _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // 전역 문자열을 초기화합니다.
    DemoApp App(hInstance);

    App.Initialize();
    App.Loop();

    return (int)1;
}

DemoApp::DemoApp(HINSTANCE hInstance)
	: GameApp::GameApp(hInstance)
	, m_AnimationInstance1(nullptr)
	, m_AnimationInstance2(nullptr)
    , Sphere2(nullptr)
    , Sphere3(nullptr)
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
    delete m_AnimationInstance1;
    delete m_AnimationInstance2;
}

void DemoApp::Update()
{
    GameApp::Update();

    // 애니메이션 배경 및 달리기 업데이트
    m_AnimationInstance1->Update(m_TimeManager->GetfDT());
    m_AnimationInstance2->Update(m_TimeManager->GetfDT());

    Sphere2->AddRelativeRotation(1.f);
    Sphere3->AddRelativeRotation(-5.f);
    
    m_World->Update(m_TimeManager);
}

void DemoApp::Render()
{
    D2DRenderer::m_pD2DRenderTarget->BeginDraw();
    D2D1::ColorF color(D2D1::ColorF::Bisque);

    D2DRenderer::m_pD2DRenderTarget->Clear(color);
    
    // 애니메이션 배경 및 달리기 렌더링
    m_AnimationInstance1->Render(D2DRenderer::m_pD2DRenderTarget);
    m_AnimationInstance2->Render(D2DRenderer::m_pD2DRenderTarget);

    m_World->Render(D2DRenderer::m_pD2DRenderTarget);

    D2DRenderer::m_pD2DRenderTarget->EndDraw();
}

bool DemoApp::Initialize()
{
    GameApp::Initialize();

    GameObject* Object = m_World->CreateGameObject<GameObject>();
    Object->SetLocation(300.f, 300.f);
    SphereComponent* Sphere = Object->m_pRootComponent->CreateChild<SphereComponent>();
    Sphere->SetRelativeLocation(0.f, 0.f);
    Sphere->m_RadiusPosition.x = 50.f;
    Sphere->m_RadiusPosition.y = 50.f;
    Sphere->SetColor(D2D1::ColorF::Yellow);

    Sphere2 = Object->m_pRootComponent->CreateChild<SphereComponent>();
    Sphere2->m_Position.x = 200.f;
    Sphere2->SetRelativeScale(1.f, 1.f);
    Sphere2->m_RadiusPosition.x = 30.f;
    Sphere2->m_RadiusPosition.y = 30.f;
    Sphere2->SetColor(D2D1::ColorF::Blue);

    Sphere3 = Sphere2->CreateChild<SphereComponent>();
    Sphere3->SetRelativeLocation(200.f, 0.f);
    Sphere3->m_Position.x = 80;
    Sphere3->m_RadiusPosition.x = 10.f;
    Sphere3->m_RadiusPosition.y = 10.f;
    Sphere3->SetColor(D2D1::ColorF::LightGray);

    // 경로 세팅
    m_AnimationInstance1 = new AnimationInstance;
    m_AnimationInstance2 = new AnimationInstance;

    // 애니메이션 에셋의 비트맵 세팅 ( 경로 탐색 )
    wstring path = m_PathManager->GetContentPath();
    path += L"Texture\\midnight.png";
    m_AnimationInstance1->SetAnimationInfo(m_ResourceManager->FindAnimationAsset(path));
    RECT rect;
    GetClientRect(&rect);
    m_AnimationInstance1->SetDstRect(rect);

    path = m_PathManager->GetContentPath();
    path += L"Texture\\run.png";
    m_AnimationInstance2->SetAnimationInfo(m_ResourceManager->FindAnimationAsset(path));
    m_AnimationInstance2->SetPosition(200.f, 200.f);
    rect = RECT{ 0, 0, 100, 100 };
    m_AnimationInstance2->SetDstRect(rect);

    return false;
}