#pragma once

#include "../D2DRender/GameApp.h"
#include "resource.h"
#include <d2d1.h>

class AnimationAsset;
class AnimationInstance;
class SphereComponent;

class DemoApp : public GameApp
{
public:
	DemoApp(HINSTANCE hInstance);
	virtual ~DemoApp();

	virtual void Update();
	virtual void Render();
	virtual bool Initialize() override;//

private:
	AnimationInstance*	m_AnimationInstance1;
	AnimationInstance*	m_AnimationInstance2;
	SphereComponent* Sphere2;
	SphereComponent* Sphere3;
};

