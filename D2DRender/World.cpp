#include "pch.h"
#include "World.h"
#include "GameObject.h"
#include "D2DRenderer.h"
#include "TimeManager.h"
#include "ResourceManager.h"

World::World()
	//:m_FocusCameraComponent()
{

}

World::~World()
{
	for (auto& pObjects : m_GameObjects)
	{
		if (pObjects != nullptr)
		{
			delete pObjects;
			pObjects = nullptr;
		}
	}
}

bool World::Init(ResourceManager* _ResourceManager, PathManager* _PathManager)
{
	for (auto& pObjects : m_GameObjects)
	{
		pObjects->Init(_ResourceManager, _PathManager);
	}

	return true;
}

void World::Update(TimeManager* _TimeManager)
{
	for (auto& pObjects : m_GameObjects)
	{
		pObjects->Update(_TimeManager);
	}
}

void World::Render(ID2D1RenderTarget* pRenderTarget)
{
	for (auto& pObjects : m_GameObjects)
	{
		pObjects->Render(pRenderTarget);
	}
}
