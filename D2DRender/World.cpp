#include "pch.h"
#include "World.h"
#include "GameObject.h"
#include "D2DRenderer.h"

World::World()
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

bool World::Init()
{
	for (auto& pObjects : m_GameObjects)
	{
		pObjects->Init();
	}

	return true;
}

void World::Update()
{
	for (auto& pObjects : m_GameObjects)
	{
		pObjects->Update();
	}
}

void World::Render(ID2D1RenderTarget* pRenderTarget)
{
	for (auto& pObjects : m_GameObjects)
	{
		pObjects->Render(pRenderTarget);
	}
}
