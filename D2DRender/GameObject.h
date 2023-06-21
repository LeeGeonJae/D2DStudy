#pragma once

class Component;
class D2DRenderer;
class SceneComponent;

class GameObject
{
public:
	GameObject();
	virtual ~GameObject();

public:
	template <typename T>
	T* CreateComponent();

	virtual void Init();
	virtual void Update();
	void Render(ID2D1RenderTarget* _pRenderTarget);
	void SetLocation(float _x, float _y);
	D2D_VECTOR_2F GetLocation();

public:
	std::vector<Component*> m_OwnedComponent;
	SceneComponent* m_pRootComponent;
};



template<typename T>
T* GameObject::CreateComponent()
{
	//bool bIsBase = std::is_base_of<Component, T>::value;
	//assert(bIsBase == true);
	T* pComponent = new T;
	pComponent->SetOwner(this);
	m_OwnedComponent.push_back(pComponent);
	return pComponent;
}