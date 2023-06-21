#pragma once

class D2DRenderer;

#include "GameObject.h"

class World
{
public:
	World();
	~World();

public:
	template<typename T>
	T* CreateGameObject();

	virtual bool Init();
	virtual void Update();
	void Render(ID2D1RenderTarget* pRenderTarget);

public:
	std::list<GameObject*> m_GameObjects;
};

template<typename T>
T* World::CreateGameObject()
{
	//bool bIsBase = std::is_base_of<GameObject, T>::value;
	//assert(bIsBase == true);
	T* newObject = new T;
	m_GameObjects.push_back((GameObject*)newObject);
	return newObject;
}