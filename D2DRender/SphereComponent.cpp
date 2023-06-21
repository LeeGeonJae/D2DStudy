#include "pch.h"
#include "SphereComponent.h"
#include "D2DRenderer.h"


SphereComponent::SphereComponent()
	: m_Position{}
	, m_RadiusPosition{}
	, m_BlackBrush(nullptr)
{
}

SphereComponent::~SphereComponent()
{
}

void SphereComponent::Init()
{
	__super::Init();
}

void SphereComponent::Update()
{
	AddRelativeRotation(0.01f);

	__super::Update();
}

void SphereComponent::Render(ID2D1RenderTarget* pRenderTarget)
{
	D2D1_ELLIPSE Ellipse;
	Ellipse.point.x = m_WorldTransform.m21;
	Ellipse.point.y = m_WorldTransform.m22;
	Ellipse.radiusX = m_RadiusPosition.x;
	Ellipse.radiusY = m_RadiusPosition.y;

	pRenderTarget->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::Red), &m_BlackBrush);

	if (m_BlackBrush != nullptr)
		pRenderTarget->FillEllipse(Ellipse, m_BlackBrush);

	// 자식 클래스의 Render함수를 모두 실행
	__super::Render(pRenderTarget);
}