// DemoApp.cpp : 애플리케이션에 대한 진입점을 정의합니다.
//

#include "framework.h"
#include "DemoApp.h"
#include "../D2DRender/D2DRenderer.h"
#include "../D2DRender/AnimationAsset.h"
#include "../D2DRender/AnimationInstance.h"
#include "../D2DRender/TimeManager.h"

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
    _In_opt_ HINSTANCE hPrevInstance,
    _In_ LPWSTR    lpCmdLine,
    _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: 여기에 코드를 입력합니다.

    // 전역 문자열을 초기화합니다.
    DemoApp App(hInstance);
    App.Initialize();
    App.Loop();
    return (int)1;
}


DemoApp::DemoApp(HINSTANCE hInstance)
	: GameApp::GameApp(hInstance)
	, m_pBitmap1(nullptr)
	, m_pBitmap2(nullptr)
	, m_AnimationAsset1(nullptr)
	, m_AnimationAsset2(nullptr)
	, m_AnimationInstance1(nullptr)
	, m_AnimationInstance2(nullptr)
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
    delete m_AnimationAsset1;
    delete m_AnimationAsset2;
    delete m_AnimationInstance1;
    delete m_AnimationInstance2;
}

void DemoApp::Update()
{
    GameApp::Update();

    // 애니메이션 배경 및 달리기 업데이트
    m_AnimationInstance1->Update(m_TimeManager->GetfDT());
    m_AnimationInstance2->Update(m_TimeManager->GetfDT());
}

void DemoApp::Render()
{
    D2DRenderer::m_pD2DRenderTarget->BeginDraw();
    D2D1::ColorF color(D2D1::ColorF::Red);

    D2DRenderer::m_pD2DRenderTarget->Clear(color);
    
    // 애니메이션 배경 및 달리기 렌더링
    m_AnimationInstance1->Render(D2DRenderer::m_pD2DRenderTarget);
    m_AnimationInstance2->Render(D2DRenderer::m_pD2DRenderTarget);

    D2DRenderer::m_pD2DRenderTarget->EndDraw();
}

bool DemoApp::Initialize()
{
    GameApp::Initialize();

    // 경로 세팅
    m_PathManager->Initialize();

    m_AnimationAsset1 = new AnimationAsset;
    m_AnimationAsset2 = new AnimationAsset;
    m_AnimationInstance1 = new AnimationInstance;
    m_AnimationInstance2 = new AnimationInstance;

    // 애니메이션 에셋의 비트맵 세팅 ( 경로 탐색 )
    wstring path = m_PathManager->GetContentPath();
    path += L"Texture\\midnight.png";
    m_AnimationAsset1->SetBitmapFilePath(path.c_str());
    m_AnimationAsset1->Build();
    path = m_PathManager->GetContentPath();
    path += L"Texture\\Run.png";
    m_AnimationAsset2->SetBitmapFilePath(path.c_str());
    m_AnimationAsset2->Build();
    

    // 애니메이션 좌표값 계산 ( 배경 )
    std::vector<FRAME_INFO> frame1;
    frame1.push_back(FRAME_INFO(0, 0, 784, 320, 0.2f));
    frame1.push_back(FRAME_INFO(789, 0, 784, 320, 0.2f));
    frame1.push_back(FRAME_INFO(0, 325, 784, 320, 0.2f));
    frame1.push_back(FRAME_INFO(789, 325, 784, 320, 0.2f));
    m_AnimationAsset1->m_Animations.push_back(frame1);
    m_AnimationInstance1->SetAnimationInfo(m_AnimationAsset1);
    RECT rect;
    GetClientRect(&rect);
    m_AnimationInstance1->SetDstRect(rect);


    // 애니메이션 좌표값 계산 ( 달리기 )
    std::vector<FRAME_INFO> frame2;
    frame2.push_back(FRAME_INFO(28, 36, 103, 84, 0.1f));
    frame2.push_back(FRAME_INFO(148, 36, 86, 84, 0.1f));
    frame2.push_back(FRAME_INFO(255, 34, 87, 86, 0.1f));
    frame2.push_back(FRAME_INFO(363, 32, 76, 88, 0.1f));
    frame2.push_back(FRAME_INFO(458, 31, 91, 89, 0.1f));
    frame2.push_back(FRAME_INFO(567, 40, 103, 80, 0.1f));
    frame2.push_back(FRAME_INFO(686, 32, 85, 88, 0.1f));
    frame2.push_back(FRAME_INFO(792, 32, 86, 88, 0.1f));
    frame2.push_back(FRAME_INFO(899, 31, 76, 89, 0.1f));
    frame2.push_back(FRAME_INFO(993, 33, 92, 87, 0.1f));
    m_AnimationAsset2->m_Animations.push_back(frame2);
    m_AnimationInstance2->SetAnimationInfo(m_AnimationAsset2);
    m_AnimationInstance2->SetPosition(200.f, 200.f);
    rect = RECT{ 0, 0, 100, 100 };
    m_AnimationInstance2->SetDstRect(rect);

    m_AnimationInstance2->SetRotation(135.f);

    return false;
}
