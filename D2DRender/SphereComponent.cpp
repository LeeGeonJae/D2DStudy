#include "pch.h"
#include "SphereComponent.h"
#include "D2DRenderer.h"
#include "TimeManager.h"
#include "ResourceManager.h"
#include "CameraManager.h"

SphereComponent::SphereComponent()
	: m_Position{}
	, m_RadiusPosition{}
	, m_ColorBrush(nullptr)
	, m_Color(D2D1::ColorF::White)
{
}

SphereComponent::~SphereComponent()
{
	if (m_ColorBrush != nullptr)
	{
		m_ColorBrush->Release();
		m_ColorBrush = nullptr;
	}
}

void SphereComponent::Init(ResourceManager* _ResourceManager)
{
	__super::Init(_ResourceManager);
}

void SphereComponent::Update(TimeManager* _TimeManager)
{
	__super::Update(_TimeManager);
}

void SphereComponent::Render(ID2D1RenderTarget* pRenderTarget)
{
	pRenderTarget->SetTransform(CameraManager::pInstance->SetObjectTransform(m_WorldTransform));
	
	D2D1_ELLIPSE Ellipse;
	Ellipse.point.x = 0;
	Ellipse.point.y = 0;
	Ellipse.radiusX = m_RadiusPosition.x;
	Ellipse.radiusY = m_RadiusPosition.y;

	pRenderTarget->CreateSolidColorBrush(D2D1::ColorF(m_Color), &m_ColorBrush);

	if (m_ColorBrush != nullptr)
		pRenderTarget->DrawEllipse(Ellipse, m_ColorBrush);

	// 자식 클래스의 Render함수를 모두 실행
	__super::Render(pRenderTarget);
}