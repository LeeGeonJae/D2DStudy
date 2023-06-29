#pragma once
#include "GameObject.h"


class SunObject :
    public GameObject
{
public:
	SunObject();
	~SunObject();

public:
	virtual void Init(ResourceManager* _ResourceManager, PathManager* _PathManager);
	virtual void Update(TimeManager* _TimeManager);
	virtual void Render(ID2D1RenderTarget* _pRenderTarget);

public:
	BitmapComponent*	m_Sun;
	TextComponent*		m_Text1;
	TextComponent*		m_Text2;
	TextComponent*		m_Text3;
	BoxComponent*		m_Box;
	BitmapComponent*	m_Earth;
	AnimationComponent* m_Animation;
};