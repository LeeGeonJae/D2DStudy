#include "pch.h"
#include "SunObject.h"
#include "PathManager.h"

SunObject::SunObject()
	: m_Sun()
	, m_Text1()
	, m_Text2()
	, m_Text3()
	, m_Box()
	, m_Earth()
	, m_Animation()
{
}

SunObject::~SunObject()
{
}

void SunObject::Init(ResourceManager* _ResourceManager, PathManager* _PathManager)
{
    // ��Ʈ ������Ʈ ����
    m_pRootComponent = new SceneComponent;

    // ��Ʈ�� ������Ʈ(�¾�) ����
    std::wstring sunpath = _PathManager->GetContentPath();
    sunpath += L"Texture\\Sun.png";
    m_Sun = m_pRootComponent->CreateChild<BitmapComponent>();
    m_Sun->SetBitmapPasth(sunpath);
    m_Sun->SetRelativeLocation(0.f, 0.f);
    m_Sun->SetRect(-50.f, -50.f, 50.f, 50.f);
    
    // �ؽ�Ʈ ������Ʈ ����
    m_Text1 = m_Sun->CreateChild<TextComponent>();
    m_Text1->SetColor(D2D1::ColorF::White);

    // �ڽ� ������Ʈ ����
    m_Box = m_Sun->CreateChild<BoxComponent>();
    m_Box->SetColor(D2D1::ColorF::White);

    // ��Ʈ�� ������Ʈ (����) ����
    m_Earth = m_Sun->CreateChild<BitmapComponent>();
    std::wstring Earthpath = _PathManager->GetContentPath();
    Earthpath += L"Texture\\Earth.png";
    m_Earth->SetBitmapPasth(Earthpath);
    m_Earth->SetRelativeLocation(200.f, 0.f);
    m_Earth->SetRect(-30.f, -30.f, 30.f, 30.f);
    m_Text2 = m_Earth->CreateChild<TextComponent>();
    m_Text2->SetColor(D2D1::ColorF::White);

    // �ִϸ��̼� ������Ʈ (�޸���) ����
    m_Animation = m_Earth->CreateChild<AnimationComponent>();
    std::wstring runpath = _PathManager->GetContentPath();
    runpath += L"Texture\\run.png";
    m_Animation->SetAnimationAssetPasth(runpath);
    m_Animation->SetRelativeLocation(100.f, 0.f);
    m_Animation->SetSizeRect(0.f, 0.f, 50.f, 50.f);
    m_Animation->Init(_ResourceManager);

    // �ؽ�Ʈ ������Ʈ ����
    m_Text3 = m_Animation->CreateChild<TextComponent>();
    m_Text3->SetColor(D2D1::ColorF::White);

    __super::Init(_ResourceManager, _PathManager);
}

void SunObject::Update(TimeManager* _TimeManager)
{
    m_Sun->AddRelativeRotation(0.3f);
    m_Earth->AddRelativeRotation(0.5f);
    m_Animation->AddRelativeRotation(-0.8f);
    m_Text1->AddRelativeRotation(-0.3f);
    m_Text2->AddRelativeRotation(-0.8f);

    __super::Update(_TimeManager);
}

void SunObject::Render(ID2D1RenderTarget* _pRenderTarget)
{
    __super::Render(_pRenderTarget);
}
