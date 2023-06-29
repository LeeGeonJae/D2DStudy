#include "pch.h"
#include "BoxComponent.h"
#include "CameraManager.h"

BoxComponent::BoxComponent()
	: m_rect()
	, m_ColorBrush(nullptr)
	, m_Color(D2D1::ColorF::Black)
{
}

BoxComponent::~BoxComponent()
{
	if (m_ColorBrush != nullptr)
	{
		m_ColorBrush->Release();
		m_ColorBrush = nullptr;
	}
}

void BoxComponent::Init(ResourceManager* _ResourceManager)
{


	__super::Init(_ResourceManager);
}

void BoxComponent::Update(TimeManager* _TimeManager)
{
	__super::Update(_TimeManager);
}

void BoxComponent::Render(ID2D1RenderTarget* pRenderTarget)
{
	pRenderTarget->SetTransform(CameraManager::pInstance->SetObjectTransform(m_WorldTransform));

	pRenderTarget->CreateSolidColorBrush(m_Color, &m_ColorBrush);
	pRenderTarget->DrawRectangle(D2D1_RECT_F{-30.f, -30.f, 30.f, 30.f}, m_ColorBrush, 3.f);

	__super::Render(pRenderTarget);
}
