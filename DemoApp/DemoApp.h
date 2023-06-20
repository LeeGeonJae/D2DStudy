#pragma once

#include "resource.h"
#include "../D2DRender/GameApp.h"
#include <d2d1.h>

class AnimationAsset;
class AnimationInstance;

class DemoApp : public GameApp
{
public:
	DemoApp(HINSTANCE hInstance);
	~DemoApp();

	virtual void Update();
	virtual void Render();
	virtual bool Initialize() override;//

private:
	ID2D1Bitmap*		m_pBitmap1;
	ID2D1Bitmap*		m_pBitmap2;
	AnimationAsset*		m_AnimationAsset1;
	AnimationAsset*		m_AnimationAsset2;
	AnimationInstance*	m_AnimationInstance1;
	AnimationInstance*	m_AnimationInstance2;
};

