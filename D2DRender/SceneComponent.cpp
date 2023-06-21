#include "pch.h"
#include "SceneComponent.h"
#include "D2DRenderer.h"

SceneComponent::SceneComponent()
	: m_RelativeScale{ 1.f, 1.f }
	, m_RelativeRotation(0)
	, m_RelativeLocation()
	, m_RelativeTransform()
	, m_WorldTransform()
	, m_pParentScene(nullptr)
{
}

SceneComponent::~SceneComponent()
{
	for (auto pComponent : m_Children)
	{
		delete pComponent;
	}

	m_Children.clear();
}

void SceneComponent::Init()
{
	for (auto& pChild : m_Children)
	{
		pChild->Init();
	}
}

void SceneComponent::Update()
{
	UpdateTransform();

	for (auto& pChild : m_Children)
	{
		pChild->Update();
	}
}

void SceneComponent::Render(ID2D1RenderTarget* pRenderTarget)
{
	for (auto& pChild : m_Children)
	{
		pChild->Render(pRenderTarget);
	}
}

void SceneComponent::UpdateTransform()
{
	m_RelativeTransform = D2D1::Matrix3x2F::Scale(D2D1::SizeF(m_RelativeScale.x, m_RelativeScale.y)) *
		D2D1::Matrix3x2F::Rotation(m_RelativeRotation) *
		D2D1::Matrix3x2F::Translation(m_RelativeLocation.x, m_RelativeLocation.y);

	if (m_pParentScene != nullptr)
	{
		m_WorldTransform = m_RelativeTransform * m_pParentScene->m_WorldTransform;
	}
	else
	{
		m_WorldTransform = m_RelativeTransform;
	}
}