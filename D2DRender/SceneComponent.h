#pragma once
#include "Component.h"

class D2DRenderer;
class TimeManager;

// 위치 정보가 필요한 컴포넌트와 위치 정보가 필요없는 컴포넌트
// 위치 정보가 필요한 컴포넌트라면 SceneComponent로 생성
// 아니면 그냥 Component로 생성
class SceneComponent : public Component
{
public:
	SceneComponent();
	~SceneComponent();

public:
	template<typename T>
	T* CreateChild();

	virtual void Init();
	virtual void Update(TimeManager* _TimeManager);
	virtual void Render(ID2D1RenderTarget* pRenderTarget);
	virtual void UpdateTransform();

public:
	void SetParentScene(SceneComponent* pParent) { m_pParentScene = pParent; }
	void SetRelativeScale(float _x, float _y) { m_RelativeScale.x = _x; m_RelativeScale.y = _y; }
	void SetRelativeRotation(float _rotate) { m_RelativeRotation = _rotate; }
	void AddRelativeRotation(float _rotate) { m_RelativeRotation += _rotate; }
	void SetRelativeLocation(float _x, float _y) { m_RelativeLocation.x = _x; m_RelativeLocation.y = _y; }

	const D2D_MATRIX_3X2_F GetWorldTransform() { return m_WorldTransform; }

public:
	std::vector<SceneComponent*> m_Children;
	SceneComponent* m_pParentScene;
	
	D2D_VECTOR_2F		m_RelativeScale;
	float				m_RelativeRotation;
	D2D_VECTOR_2F		m_RelativeLocation;
	D2D_MATRIX_3X2_F	m_RelativeTransform;

	D2D_MATRIX_3X2_F	m_WorldTransform;
};

template<typename T>
inline T* SceneComponent::CreateChild()
{
	//bool bIsBase = std::is_base_of<Component, T>::value;
	//assert(bIsBase == true);
	T* pComponent = new T;
	pComponent->SetParentScene(this);
	m_Children.push_back(pComponent);
	return pComponent;
}