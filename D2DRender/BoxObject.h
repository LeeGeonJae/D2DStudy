#pragma once
#include "GameObject.h"
class BoxObject :
    public GameObject
{
public:
	BoxObject();
	virtual ~BoxObject();

public:
	virtual void Init(ResourceManager* _ResourceManager, PathManager* _PathManager);
	virtual void Update(TimeManager* _TimeManager);
	virtual void Render(ID2D1RenderTarget* _pRenderTarget);

public:
	BoxComponent* m_Box;
	int randSpeed;
};

