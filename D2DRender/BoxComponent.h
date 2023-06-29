#pragma once
#include "SceneComponent.h"

class TimeManager;
class ResourceManager;

class BoxComponent :
    public SceneComponent
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

public:
    D2D1_RECT_F             m_rect;
    ID2D1SolidColorBrush*   m_ColorBrush;
    D2D1::ColorF            m_Color;
};