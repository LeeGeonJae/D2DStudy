#include "pch.h"
#include "RenderComponent.h"
#include "D2DRenderer.h"
#include "CameraManager.h"

RenderComponent::RenderComponent()
	: m_bVisible(true)
	, m_iZOrder()
{
}

RenderComponent::~RenderComponent()
{
}

void RenderComponent::Update(TimeManager* _TimeManager)
{
	__super::Update(_TimeManager);
}

void RenderComponent::Render(ID2D1RenderTarget* pRenderTarget)
{
	// AABB 렌더 가능한 박스 범위 그리기
	D2D1_MATRIX_3X2_F AABBRender = D2D1::IdentityMatrix();
	AABBRender._31 = m_AABBmin.x - m_AABBRect.left;
	AABBRender._32 = m_AABBmin.y - m_AABBRect.top;

	pRenderTarget->SetTransform(AABBRender);
	pRenderTarget->DrawRectangle(m_AABBRect, D2DRenderer::m_Instance->m_pGrayBrush);

	if (CameraManager::m_pInstance->intersect(m_AABBmin, m_AABBmax))
	{
		// 피벗 그리기
		pRenderTarget->DrawEllipse(D2D1_ELLIPSE{ D2D1_POINT_2F{0.f, 0.f}, 10.f, 10.f }, D2DRenderer::m_Instance->m_pGreenBrush, 2.f);
		pRenderTarget->DrawLine(D2D1_POINT_2F{ -20.f, 0.f }, D2D1_POINT_2F{ 20.f, 0.f }, D2DRenderer::m_Instance->m_pRedBrush);
		pRenderTarget->DrawLine(D2D1_POINT_2F{ 0.f, -20.f }, D2D1_POINT_2F{ 0.f, 20.f }, D2DRenderer::m_Instance->m_pGreenBrush);
	}

	__super::Render(pRenderTarget);
}
