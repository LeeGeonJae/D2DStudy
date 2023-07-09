#pragma once
#include "RenderComponent.h"

class BitmapComponent :
    public RenderComponent
{
public:
    BitmapComponent();
    virtual ~BitmapComponent();

public:
    virtual void Init(ResourceManager* _ResourceManager);
    virtual void Update(TimeManager* _TimeManager);
    virtual void Render(ID2D1RenderTarget* pRenderTarget);

public:
    void SetBitmapPasth(const std::wstring& _strAssetKey) { m_strAnimationAssetPath = _strAssetKey; }
    void SetRect(float _left, float _top, float _right, float _bottom)
    {
        m_Rect.left = _left;
        m_Rect.top = _top;
        m_Rect.right = _right;
        m_Rect.bottom = _bottom;
        m_AABBRect = m_Rect;
    }

private:
    ID2D1Bitmap* m_Bitmap;
    std::wstring m_strAnimationAssetPath;
    D2D1_RECT_F  m_Rect;
};

