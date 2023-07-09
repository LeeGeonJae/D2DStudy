#pragma once
#include "SceneComponent.h"
class OBBCollision :
    public SceneComponent
{
public:
	OBBCollision();
	virtual ~OBBCollision();

public:
	virtual void Init(ResourceManager* _ResourceManager);
	virtual void Update(TimeManager* _TimeManager);
	virtual void Render(ID2D1RenderTarget* pRenderTarget);

public:
	bool CheckCollision(GameObject* _OtherObject);

public:
	D2D_RECT_F GetOBBRect() { return m_OBBRect; }

private:
	D2D_RECT_F			m_OBBRect;
	D2D_RECT_F			m_OtherOBBRect;
	D2D_POINT_2F		m_OtherOBBPoint;
};

