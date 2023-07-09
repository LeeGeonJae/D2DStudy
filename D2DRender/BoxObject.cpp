#include "pch.h"
#include "BoxObject.h"
#include "TimeManager.h"
#include <time.h>

BoxObject::BoxObject()
	:m_Box(nullptr)
	, randSpeed(0)
{
}

BoxObject::~BoxObject()
{
}

void BoxObject::Init(ResourceManager* _ResourceManager, PathManager* _PathManager)
{
	// 박스 컴포넌트 생성
	m_Box = m_pRootComponent->CreateChild<BoxComponent>();
	m_Box->SetColor(D2D1::ColorF::Red);
	m_Box->SetRect(-30.f, -50.f, 30.f, 50.f);

	randSpeed = rand() % 50 - 20;

	__super::Init(_ResourceManager, _PathManager);
}

void BoxObject::Update(TimeManager* _TimeManager)
{
	m_Box->AddRelativeLocation((float)randSpeed * _TimeManager->GetfDT(), (float)((randSpeed + -6) % 5) * _TimeManager->GetfDT());

	__super::Update(_TimeManager);
}

void BoxObject::Render(ID2D1RenderTarget* _pRenderTarget)
{
	__super::Render(_pRenderTarget);
}
