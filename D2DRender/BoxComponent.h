#pragma once
#include "RenderComponent.h"

class TimeManager;
class ResourceManager;

class BoxComponent :
    public RenderComponent
{
public:
    BoxComponent();
    virtual ~BoxComponent();

public:
    virtual void Init(ResourceManager* _ResourceManager);
    virtual void Update(TimeManager* _TimeManager);
    virtual void Render(ID2D1RenderTarget* pRenderTarget);

public:
    void SetColor(D2D1::ColorF _color) { m_Color = _color; }
    void SetRect(float _left, float _top, float _right, float _bottom)
    {
        m_rect.left = _left;
        m_rect.top = _top;
        m_rect.right = _right;
        m_rect.bottom = _bottom;

        m_AABBRect = m_rect;
    }

public:
    D2D1_RECT_F             m_rect;
    ID2D1SolidColorBrush*   m_ColorBrush;
    D2D1::ColorF            m_Color;
};