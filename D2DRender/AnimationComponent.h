#pragma once
#include "SceneComponent.h"

class AnimationInstance;
class AnimationAsset;
class TimeManager;

class AnimationComponent :
    public SceneComponent
{
public:
    AnimationComponent();
    virtual ~AnimationComponent();

    virtual void Init() override;
    virtual void Update(TimeManager* _TimeManager) override;
    virtual void Render(ID2D1RenderTarget* pRenderTarget) override;

public:
    void SetAnimationAssetPasth(const std::wstring& strAssetKey) { m_strAnimationAssetPath = strAssetKey; }

public:
    std::wstring        m_strAnimationAssetPath;
    AnimationInstance*  m_AnimationInstance;
    AnimationAsset*     m_pAnimationAsset;
};