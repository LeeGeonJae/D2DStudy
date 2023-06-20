#pragma once

class D2DRenderer;

enum class ShapeType
{
	Rect,
	Circle,

};

class Shape
{
public:
	Shape(int _x, int _y, ShapeType _Type);
	~Shape();

	void Update();
	void Render(D2DRenderer* _Renderer);

private:
	POINT Position;
	ShapeType Type;
};