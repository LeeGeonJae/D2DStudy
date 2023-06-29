#pragma once
#include "SceneComponent.h"

class AnimationInstance;
class AnimationAsset;
class TimeManager;
class ResourceManager;

class AnimationComponent :
    public SceneComponent
{
public:
    AnimationComponent();
    virtual ~AnimationComponent();

    virtual void Init(ResourceManager* _ResourceManager) override;
    virtual void Update(TimeManager* _TimeManager) override;
    virtual void Render(ID2D1RenderTarget* pRenderTarget) override;

public:
    void SetAnimationAssetPasth(const std::wstring& _strAssetKey) { m_strAnimationAssetPath = _strAssetKey; }
    void SetSizeRect(float _top, float _left, float _bottom, float _right) {
        m_DstRect.top = _top - _bottom / 2;
        m_DstRect.left = _left - _right / 2;
        m_DstRect.bottom = _bottom / 2;
        m_DstRect.right = _right / 2;
    }

public:
    std::wstring        m_strAnimationAssetPath;
    D2D1_RECT_F         m_DstRect;
    float               m_Speed;

    AnimationInstance*  m_AnimationInstance;
    AnimationAsset*     m_pAnimationAsset;
};