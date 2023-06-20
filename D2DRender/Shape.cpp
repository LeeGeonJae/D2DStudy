#include "pch.h"
#include "Shape.h"
#include "D2DRenderer.h"

Shape::Shape(int _x, int _y, ShapeType _Type)
{
	Position.x = _x;
	Position.y = _y;
	Type = _Type;
}

Shape::~Shape()
{
}

void Shape::Update()
{
}

void Shape::Render(D2DRenderer* _Renderer)
{
	switch (Type)
	{
	case ShapeType::Rect:
	{
		D2D1_RECT_F rect;
		rect.left = (float)Position.x - 100;
		rect.top = (float)Position.y - 50;
		rect.right = (float)Position.x + 100;
		rect.bottom = (float)Position.y + 50;

		_Renderer->m_pD2DRenderTarget->FillRectangle(rect, _Renderer->g_pBlackBrush);
	}
		break;
	case ShapeType::Circle:

		break;
	}
}
