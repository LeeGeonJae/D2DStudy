#pragma once

class Component;
class D2DRenderer;
class SceneComponent;
class TimeManager;
class ResourceManager;

#include <cassert>

#include "SceneComponent.h"
#include "BitmapComponent.h"
#include "CameraComponent.h"
#include "BoxComponent.h"
#include "AnimationComponent.h"
#include "TextComponent.h"

class GameObject
{
public:
	GameObject();
	virtual ~GameObject();

public:
	template <typename T>
	T* CreateComponent();

	virtual void Init(ResourceManager* _ResourceManager, PathManager* _PathManager);
	virtual void Update(TimeManager* _TimeManager);
	virtual void Render(ID2D1RenderTarget* _pRenderTarget);
	void SetLocation(float _x, float _y);
	D2D_VECTOR_2F GetLocation();

public:
	std::vector<Component*> m_OwnedComponent;
	SceneComponent* m_pRootComponent;
};

template<typename T>
T* GameObject::CreateComponent()
{
	bool bIsBase = std::is_base_of<Component, T>::value;
	assert(bIsBase == true);
	T* pComponent = new T;
	pComponent->SetOwner(this);
	m_OwnedComponent.push_back(pComponent);
	return pComponent;
}