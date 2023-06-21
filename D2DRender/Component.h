#pragma once

class GameObject;

class Component
{
public:
	Component() : m_ObjectOwner(nullptr)
	{
	}
	virtual ~Component() {};

public:
	virtual void Update() = 0;
	void SetOwner(GameObject* pOwner) { m_ObjectOwner = pOwner; }

public:
	GameObject* m_ObjectOwner;
};