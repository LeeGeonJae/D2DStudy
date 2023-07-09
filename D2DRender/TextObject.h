#pragma once
#include "GameObject.h"

class TextObject :
    public GameObject
{
public:
	TextObject();
	virtual ~TextObject();

public:
	virtual void Init(ResourceManager* _ResourceManager, PathManager* _PathManager);
	virtual void Update(TimeManager* _TimeManager);
	virtual void Render(ID2D1RenderTarget* _pRenderTarget);

public:
	TextComponent* m_TextComponent;
};

