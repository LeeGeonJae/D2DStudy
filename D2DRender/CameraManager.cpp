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
	m_matRender = D2D1::Matrix3x2F::Scale(1.0f, -1.0f); // screen ��ǥ�迡�� y�� ���� �ϹǷ�  ������ �̹� �����ϰ��Ѵ�.    
	m_matWorld = D2D1::Matrix3x2F::Translation(0.0f, 768); // ���� �ϴ��� �����̹Ƿ� ������ ��� ���� �׸����Ѵ�.
	m_matCamera = D2D1::Matrix3x2F::Identity(); // �Է¿� ���� ī�޶� ���� ��ġ�� �����ϰ� ������� �����Ѵ�.
	m_matScreen = D2D1::Matrix3x2F::Scale(1.0f, -1.0f) * D2D1::Matrix3x2F::Translation(0.0f, (float)_size.height); // ���� �ϴ��� ������ �ǰ��ϴ� ��ȯ
}

D2D_MATRIX_3X2_F CameraManager::SetObjectTransform(D2D_MATRIX_3X2_F _ObjectTransform)
{
	m_matCamera = D2D1::Matrix3x2F::Translation(m_locCameraX, m_locCameraY);
	D2D1InvertMatrix(&m_matCamera);

	D2D_MATRIX_3X2_F Transform = m_matRender * _ObjectTransform * m_matCamera * m_matScreen;
	return Transform;
}
