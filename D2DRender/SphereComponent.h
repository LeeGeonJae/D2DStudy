#pragma once
#include "SceneComponent.h"

class TimeManager;

class SphereComponent :
    public SceneComponent
{
public:
    SphereComponent();
    virtual ~SphereComponent();

public:
    virtual void Init();
    virtual void Update(TimeManager* _TimeManager);
    virtual void Render(ID2D1RenderTarget* pRenderTarget);

public:
    void SetColor(D2D1::ColorF _color) { m_Color = _color; }

public:
    D2D1_POINT_2F m_Position;
    D2D1_POINT_2F m_RadiusPosition;
    ID2D1SolidColorBrush* m_ColorBrush;
    D2D1::ColorF m_Color;
};