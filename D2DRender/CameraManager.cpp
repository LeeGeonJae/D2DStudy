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
	m_matRender = D2D1::Matrix3x2F::Scale(1.0f, -1.0f); // screen ��ǥ�迡�� y�� ���� �ϹǷ�  ������ �̹� �����ϰ��Ѵ�.    
	m_matWorld = D2D1::Matrix3x2F::Translation(0.0f, 1080.f); // ���� �ϴ��� �����̹Ƿ� ������ ��� ���� �׸����Ѵ�.
	m_matCamera = D2D1::Matrix3x2F::Identity(); // �Է¿� ���� ī�޶� ���� ��ġ�� �����ϰ� ������� �����Ѵ�.
	m_matScreen = D2D1::Matrix3x2F::Scale(1.0f, -1.0f) * D2D1::Matrix3x2F::Translation(0.0f, (float)_size.height); // ���� �ϴ��� ������ �ǰ��ϴ� ��ȯ
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
