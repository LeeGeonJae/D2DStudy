#pragma once

#include "resource.h"
#include "../D2DRender/GameApp.h"

class DemoApp : public GameApp
{
public:
	DemoApp(HINSTANCE hInstance);
	~DemoApp();

	virtual void Update() final; // override 
	virtual void Render() final;

private:

};