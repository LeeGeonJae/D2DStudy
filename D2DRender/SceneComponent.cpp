#include "pch.h"
#include "SceneComponent.h"
#include "D2DRenderer.h"
#include "TimeManager.h"
#include "ResourceManager.h"
#include "CameraManager.h"

SceneComponent::SceneComponent()
	: m_RelativeScale{ 1.f, 1.f }
	, m_RelativeRotation(0)
	, m_RelativeLocation()
	, m_RelativeTransform()
	, m_WorldTransform()
	, m_pParentScene(nullptr)
	, m_AABBRect()
	, m_AABBmax()
	, m_AABBmin()
{
}

SceneComponent::~SceneComponent()
{
	for (auto pComponent : m_Children)
	{
		if (pComponent != nullptr)
		{
			delete pComponent;
			pComponent = nullptr;
		}
	}

	m_Children.clear();
}

void SceneComponent::Init(ResourceManager* _ResourceManager)
{
	for (auto& pChild : m_Children)
	{
		pChild->Init(_ResourceManager);
	}
}

void SceneComponent::Update(TimeManager* _TimeManager)
{
	UpdateTransform();

	for (auto& pChild : m_Children)
	{
		pChild->Update(_TimeManager);
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

	// AABB °è»ê
	D2D1_MATRIX_3X2_F AABB = m_WorldTransform * CameraManager::m_pInstance->GetInvertTransform();
	m_AABBmin.x = AABB._31 + m_AABBRect.left;
	m_AABBmin.y = AABB._32 + m_AABBRect.top;
	m_AABBmax.x = AABB._31 + m_AABBRect.right;
	m_AABBmax.y = AABB._32 + m_AABBRect.bottom;
}

void SceneComponent::AttachToComponent(SceneComponent* _pParnt)
{
	if (m_pParentScene != nullptr)
		return;

	m_pParentScene = _pParnt;
	_pParnt->m_Children.push_back(this);
}