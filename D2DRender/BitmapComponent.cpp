#include "pch.h"
#include "BitmapComponent.h"
#include "ResourceManager.h"
#include "CameraManager.h"
#include "D2DRenderer.h"
#include "PathManager.h"

BitmapComponent::BitmapComponent()
	: m_strAnimationAssetPath()
	, m_Bitmap(nullptr)
	, m_Rect()
{
}

BitmapComponent::~BitmapComponent()
{
	m_Bitmap = nullptr;
}

void BitmapComponent::Init(ResourceManager* _ResourceManager)
{
	m_Bitmap = _ResourceManager->FindTexture(m_strAnimationAssetPath);

	__super::Init(_ResourceManager);
}

void BitmapComponent::Update(TimeManager* _TimeManager)
{
	__super::Update(_TimeManager);
}

void BitmapComponent::Render(ID2D1RenderTarget* pRenderTarget)
{
	if (CameraManager::m_pInstance->intersect(m_AABBmin, m_AABBmax))
	{
		pRenderTarget->SetTransform(m_WorldTransform * CameraManager::m_pInstance->GetInvertTransform());
		pRenderTarget->DrawBitmap(m_Bitmap, m_Rect, 1.f, D2D1_BITMAP_INTERPOLATION_MODE_LINEAR, NULL);

		CameraManager::m_pInstance->CullCount++;
	}

	__super::Render(pRenderTarget);
}