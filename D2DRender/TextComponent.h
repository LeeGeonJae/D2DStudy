#pragma once
#include "SceneComponent.h"

class TextComponent :
    public SceneComponent
{
public:
    TextComponent();
    virtual ~TextComponent();

public:
    virtual void Init(ResourceManager* _ResourceManager);
    virtual void Update(TimeManager* _TimeManager);
    virtual void Render(ID2D1RenderTarget* _pRenderTarget);

public:
    void SetColor(D2D1::ColorF _color) { m_Color = _color; }
    void SetPosition(float _x, float _y) { m_Position.x = _x; m_Position.y = _y; }
    void SetText(const WCHAR* _Text) { m_Text = _Text; }

public:
    D2D1_VECTOR_2F          m_Position;
    D2D1_RECT_F             m_TextRect;
    ID2D1SolidColorBrush*   m_ColorBrush;
    D2D1::ColorF            m_Color;
    std::wstring            m_Text;
};

