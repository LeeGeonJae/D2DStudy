#include "pch.h"
#include "AnimationInstance.h"
#include "AnimationAsset.h"

AnimationInstance::AnimationInstance()
	:m_pAnimationAsset(nullptr), m_AnimationIndex(0), m_FrameIndex(0), m_ProgressTime(0), m_bMirror(false), m_Speed(1.0f)
{
	m_SrcRect = { 0.0f,0.0f,0.0f,0.0f };
	m_DstRect = { 0.0f,0.0f,0.0f,0.0f };
	m_Position = { 0.0f,0.0f };
	m_Transform = D2D1::Matrix3x2F::Identity();

}

AnimationInstance::~AnimationInstance()
{
	m_pAnimationAsset = nullptr;
}

void AnimationInstance::SetAnimationInfo(AnimationAsset* pAnimationInfo)
{
	m_pAnimationAsset = pAnimationInfo;
	m_SrcRect = m_pAnimationAsset->m_Animations[m_AnimationIndex][m_FrameIndex].Source;

	m_Transform.dx = m_Position.x;
	m_Transform.dy = m_Position.y;
}

void AnimationInstance::Update(float deltaTime)
{
	//여러분이 채워보세요
	m_ProgressTime += deltaTime;

	if ((m_pAnimationAsset->m_Animations[m_AnimationIndex][m_FrameIndex].RenderTime / m_Speed) <= m_ProgressTime)
	{
		m_ProgressTime -= m_pAnimationAsset->m_Animations[m_AnimationIndex][m_FrameIndex].RenderTime / m_Speed;
		m_SrcRect = m_pAnimationAsset->m_Animations[m_AnimationIndex][m_FrameIndex].Source;
		m_FrameIndex++;

		if (m_pAnimationAsset->m_Animations[m_AnimationIndex].size() <= m_FrameIndex)
			m_FrameIndex = 0;
	}
}

void AnimationInstance::Render(ID2D1RenderTarget* pRenderTarget)
{
	pRenderTarget->SetTransform(m_Transform);

	pRenderTarget->DrawBitmap(m_pAnimationAsset->m_pBitmap, m_DstRect, 1.0f, D2D1_BITMAP_INTERPOLATION_MODE_LINEAR, m_SrcRect);
}

void AnimationInstance::SetAnimationIndex(size_t index, bool bMirror)
{
	assert(m_pAnimationAsset != nullptr);
	assert(m_pAnimationAsset->m_Animations.size() > index);

	m_AnimationIndex = index;
	m_FrameIndex = 0;
	m_ProgressTime = 0.0f;
	m_bMirror = bMirror;
}