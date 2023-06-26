#pragma once

class GameObject;
class TimeManager;
class KeyManager;
class PathManager;

class Component
{
public:
	Component() 
		: m_ObjectOwner(nullptr)
		, m_TimeManager(nullptr)
		, m_KeyManager(nullptr)
		, m_PathManager(nullptr)
	{
	}
	Component(TimeManager* _TimeManager, KeyManager* _KeyManager, PathManager* _PathManager)
		: m_ObjectOwner(nullptr)
		, m_TimeManager(_TimeManager)
		, m_KeyManager(_KeyManager)
		, m_PathManager(_PathManager)
	{
	}

	virtual ~Component() {};

public:
	virtual void Update(TimeManager* _TimeManager) = 0;
	void SetOwner(GameObject* pOwner) { m_ObjectOwner = pOwner; }

public:
	GameObject* m_ObjectOwner;
	TimeManager* m_TimeManager;
	KeyManager* m_KeyManager;
	PathManager* m_PathManager;
};