#include "pch.h"
#include "GameObject.h"
#include "SceneComponent.h"
#include "Component.h"
#include "D2DRenderer.h"

GameObject::GameObject()
{
	m_pRootComponent = new SceneComponent;
	m_pRootComponent->SetOwner(this);
}

GameObject::~GameObject()
{
	delete m_pRootComponent;
}

void GameObject::Init()
{
	m_pRootComponent->Init();
}

void GameObject::Update()
{
	m_pRootComponent->Update();
}

void GameObject::Render(ID2D1RenderTarget* _pRenderTarget)
{
	m_pRootComponent->Render(_pRenderTarget);
}

void GameObject::SetLocation(float _x, float _y)
{
	m_pRootComponent->SetRelativeLocation(_x, _y);
}

D2D_VECTOR_2F GameObject::GetLocation()
{
	D2D_VECTOR_2F position;
	position.x = m_pRootComponent->m_WorldTransform.m21;
	position.y = m_pRootComponent->m_WorldTransform.m22;

	return position;
}
