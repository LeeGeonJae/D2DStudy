#include "pch.h"
#include "OBBCollision.h"
#include "GameObject.h"
#include "CameraManager.h"
#include <math.h>

OBBCollision::OBBCollision()
{
}

OBBCollision::~OBBCollision()
{
}

void OBBCollision::Init(ResourceManager* _ResourceManager)
{
}

void OBBCollision::Update(TimeManager* _TimeManager)
{
}

void OBBCollision::Render(ID2D1RenderTarget* pRenderTarget)
{
}

bool OBBCollision::CheckCollision(GameObject* _OtherObject)
{
	if (_OtherObject->GetCollision() == nullptr)
		return false;

	m_OtherOBBPoint.x = (_OtherObject->GetCollision()->GetWorldTransform() * CameraManager::m_pInstance->GetInvertTransform())._31;
	m_OtherOBBPoint.y = (_OtherObject->GetCollision()->GetWorldTransform() * CameraManager::m_pInstance->GetInvertTransform())._32;

	m_OtherOBBRect = _OtherObject->GetCollision()->GetOBBRect();

	if (abs(sqrt((m_OtherOBBPoint.x - GetWorldTransform()._31) * (m_OtherOBBPoint.x - GetWorldTransform()._31))
		+ sqrt((m_OtherOBBPoint.y - GetWorldTransform()._32) * m_OtherOBBPoint.y - GetWorldTransform()._32))
		> abs(sqrt((m_OtherOBBRect.right + m_OBBRect.right) / 2) + sqrt((m_OtherOBBRect.bottom + m_OBBRect.bottom) / 2)))
		return false;

}
