#pragma once
#include "SceneComponent.h"
class SphereComponent :
    public SceneComponent
{
public:
    SphereComponent();
    virtual ~SphereComponent();

public:
    virtual void Init();
    virtual void Update();
    virtual void Render(ID2D1RenderTarget* pRenderTarget);

public:
    D2D1_POINT_2F m_Position;
    D2D1_POINT_2F m_RadiusPosition;
    ID2D1SolidColorBrush* m_BlackBrush;
};