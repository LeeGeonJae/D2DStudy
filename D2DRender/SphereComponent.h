#pragma once
#include "RenderComponent.h"

class TimeManager;
class ResourceManager;

class SphereComponent :
    public RenderComponent
{
public:
    SphereComponent();
    virtual ~SphereComponent();

public:
    virtual void Init(ResourceManager* _ResourceManager);
    virtual void Update(TimeManager* _TimeManager);
    virtual void Render(ID2D1RenderTarget* pRenderTarget);

public:
    void SetColor(D2D1::ColorF _color) { m_Color = _color; }
    void SetRadius(float _x, float _y) { 
        m_RadiusPosition.x = _x; m_RadiusPosition.y = _y; 
        m_AABBRect.left = 0.f - m_RadiusPosition.x / 2;
        m_AABBRect.top = 0.f - m_RadiusPosition.y / 2;
        m_AABBRect.bottom = 0.f + m_RadiusPosition.y / 2;
        m_AABBRect.right = 0.f + m_RadiusPosition.x / 2;
    }

public:
    D2D1_POINT_2F m_Position;
    D2D1_POINT_2F m_RadiusPosition;
    ID2D1SolidColorBrush* m_ColorBrush;
    D2D1::ColorF m_Color;
};