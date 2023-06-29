#include "pch.h"
#include "CameraManager.h"
#include "D2DRenderer.h"

CameraManager* CameraManager::pInstance = nullptr;

CameraManager::CameraManager()
	: m_Transform()
{
	pInstance = this;
}

CameraManager::~CameraManager()
{
}

void CameraManager::Initialize(D2D1_SIZE_U _size)
{
	m_matRender = D2D1::Matrix3x2F::Scale(1.0f, -1.0f); // screen 좌표계에서 y축 반전 하므로  이전에 이미 반전하게한다.    
	m_matWorld = D2D1::Matrix3x2F::Translation(0.0f, 768); // 왼쪽 하단이 원점이므로 윈도우 상단 부터 그리게한다.
	m_matCamera = D2D1::Matrix3x2F::Identity(); // 입력에 따라 카메라 월드 위치를 변경하고 역행렬을 저장한다.
	m_matScreen = D2D1::Matrix3x2F::Scale(1.0f, -1.0f) * D2D1::Matrix3x2F::Translation(0.0f, (float)_size.height); // 왼쪽 하단이 원점이 되게하는 변환
}

D2D_MATRIX_3X2_F CameraManager::SetObjectTransform(D2D_MATRIX_3X2_F _ObjectTransform)
{
	m_matCamera = D2D1::Matrix3x2F::Translation(m_locCameraX, m_locCameraY);
	D2D1InvertMatrix(&m_matCamera);

	D2D_MATRIX_3X2_F Transform = m_matRender * _ObjectTransform * m_matCamera * m_matScreen;
	return Transform;
}
