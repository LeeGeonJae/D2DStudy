#include "pch.h"
#include "CameraManager.h"
#include "D2DRenderer.h"
#include "KeyManager.h"
#include "TimeManager.h"

CameraManager* CameraManager::m_pInstance = nullptr;

CameraManager::CameraManager()
	: m_Transform()
{
	m_pInstance = this;
}

CameraManager::~CameraManager()
{
}

void CameraManager::Initialize(D2D1_SIZE_U _size)
{
	m_matRender = D2D1::Matrix3x2F::Scale(1.0f, -1.0f); // screen 좌표계에서 y축 반전 하므로  이전에 이미 반전하게한다.    
	m_matWorld = D2D1::Matrix3x2F::Translation(0.0f, 1080.f); // 왼쪽 하단이 원점이므로 윈도우 상단 부터 그리게한다.
	m_matCamera = D2D1::Matrix3x2F::Identity(); // 입력에 따라 카메라 월드 위치를 변경하고 역행렬을 저장한다.
	m_matScreen = D2D1::Matrix3x2F::Scale(1.0f, -1.0f) * D2D1::Matrix3x2F::Translation(0.0f, (float)_size.height); // 왼쪽 하단이 원점이 되게하는 변환
}

void CameraManager::Update(KeyManager* _KeyManager, TimeManager* _TimeManager)
{
	if (_KeyManager->GetKeyState(KEY::DOWN) == KEY_STATE::HOLD)
	{
		AddCameraLocation(0.f, 500.f * _TimeManager->GetfDT());
	}
	if (_KeyManager->GetKeyState(KEY::UP) == KEY_STATE::HOLD)
	{
		AddCameraLocation(0.f, 500.f * -_TimeManager->GetfDT());
	}
	if (_KeyManager->GetKeyState(KEY::LEFT) == KEY_STATE::HOLD)
	{
		AddCameraLocation(500.f * _TimeManager->GetfDT(), 0.f);
	}
	if (_KeyManager->GetKeyState(KEY::RIGHT) == KEY_STATE::HOLD)
	{
		AddCameraLocation(500.f * -_TimeManager->GetfDT(), 0.f);
	}
}

D2D_MATRIX_3X2_F CameraManager::GetInvertTransform()
{
	m_matCamera = D2D1::Matrix3x2F::Translation(m_locCameraX, m_locCameraY);
	D2D1InvertMatrix(&m_matCamera);

	D2D_MATRIX_3X2_F Transform = m_matRender * m_matWorld * m_matCamera * m_matScreen;
	D2D1InvertMatrix(&Transform);

	return Transform;
}

bool CameraManager::intersect(D2D_POINT_2F AABBmin, D2D_POINT_2F AABBmax)
{
	return (
		AABBmin.x <= 1700.f &&
		AABBmax.x >= 200.f &&
		AABBmin.y <= 800.f &&
		AABBmax.y >= 200.f     );
}
