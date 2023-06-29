#include "pch.h"
#include "AnimationComponent.h"
#include "AnimationInstance.h"
#include "TimeManager.h"
#include "ResourceManager.h"
#include "CameraManager.h"

AnimationComponent::AnimationComponent()
	: m_strAnimationAssetPath ()
	, m_AnimationInstance(nullptr)
	, m_pAnimationAsset(nullptr)
	, m_DstRect()
	, m_Speed(1.f)
{
}

AnimationComponent::~AnimationComponent()
{
	if (m_AnimationInstance != nullptr)
	{
		delete m_AnimationInstance;
		m_AnimationInstance = nullptr;
	}
}

void AnimationComponent::Init(ResourceManager* _ResourceManager)
{
	m_AnimationInstance = new AnimationInstance;

	m_AnimationInstance->SetAnimationInfo(_ResourceManager->FindAnimationAsset(m_strAnimationAssetPath));
	m_AnimationInstance->SetDstRect(m_DstRect);
	m_AnimationInstance->SetSpeed(m_Speed);

	__super::Init(_ResourceManager);
}

void AnimationComponent::Update(TimeManager* _TimeManager)
{
	m_AnimationInstance->Update(_TimeManager->GetfDT());

	__super::Update(_TimeManager);
}

void AnimationComponent::Render(ID2D1RenderTarget* pRenderTarget)
{
	m_AnimationInstance->SetTransform(CameraManager::pInstance->SetObjectTransform(m_WorldTransform));
	m_AnimationInstance->Render(pRenderTarget);

	__super::Render(pRenderTarget);
}
