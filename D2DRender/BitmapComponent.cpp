#include "pch.h"
#include "BitmapComponent.h"
#include "ResourceManager.h"
#include "CameraManager.h"
#include "PathManager.h"

BitmapComponent::BitmapComponent()
	: m_strAnimationAssetPath()
	, m_Bitmap(nullptr)
{
}

BitmapComponent::~BitmapComponent()
{
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
	pRenderTarget->SetTransform(CameraManager::pInstance->SetObjectTransform(m_WorldTransform));

	pRenderTarget->DrawBitmap(m_Bitmap, m_Rect, 1.f, D2D1_BITMAP_INTERPOLATION_MODE_LINEAR, NULL);

	__super::Render(pRenderTarget);
}