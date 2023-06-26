#include "pch.h"
#include "AnimationComponent.h"
#include "AnimationInstance.h"
#include "TimeManager.h"

AnimationComponent::AnimationComponent()
	: m_strAnimationAssetPath ()
	, m_AnimationInstance(nullptr)
	, m_pAnimationAsset(nullptr)
{
}

AnimationComponent::~AnimationComponent()
{
}

void AnimationComponent::Init()
{

	__super::Init();
}

void AnimationComponent::Update(TimeManager* _TimeManager)
{
	m_AnimationInstance->Update(_TimeManager->GetfDT());

	__super::Update(_TimeManager);
}

void AnimationComponent::Render(ID2D1RenderTarget* pRenderTarget)
{
	m_AnimationInstance->Render(pRenderTarget);

	__super::Render(pRenderTarget);
}
