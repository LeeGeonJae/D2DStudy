#pragma once

#include "../D2DRender/GameApp.h"
#include "resource.h"
#include <d2d1.h>

class DemoApp : public GameApp
{
public:
	DemoApp(HINSTANCE hInstance);
	virtual ~DemoApp();

	virtual void Update();
	virtual void Render();
	virtual bool Initialize() override;//

private:
};

