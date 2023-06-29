#pragma once

class D2DRenderer;
class TimeManager;
class ResourceManager;
class CameraComponent;

#include "GameObject.h"
#include <cassert>

class World
{
public:
	World();
	~World();

public:
	template<typename T>
	T* CreateGameObject();

	virtual bool Init(ResourceManager* _ResourceManager, PathManager* _PathManager);
	virtual void Update(TimeManager* _TimeManager);
	void Render(ID2D1RenderTarget* pRenderTarget);
	void CullObject();

public:
	std::list<GameObject*>		m_GameObjects;
	//std::list<CameraComponent*> m_CameraComponent;
	//CameraComponent*			m_FocusCameraComponent;
};

template<typename T>
T* World::CreateGameObject()
{
	bool bIsBase = std::is_base_of<GameObject, T>::value;
	assert(bIsBase == true);
	T* newObject = new T;
	m_GameObjects.push_back((GameObject*)newObject);
	return newObject;
}