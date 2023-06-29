#pragma once
#include "SceneComponent.h"
class CameraComponent :
    public SceneComponent
{
public:
	CameraComponent();
	~CameraComponent();

public:
	//static CameraComponent* pInstance;

public:
	void Initialize(D2D1_SIZE_U _size);
	D2D_MATRIX_3X2_F SetObjectTransform(D2D_MATRIX_3X2_F _ObjectTransform);

public:
	void SetCameraLocation(float _x, float _y) {
		m_locCameraX = _x;
		m_locCameraY = _y;
	}
	void AddCameraLocation(float _x, float _y) {
		m_locCameraX += _x;
		m_locCameraY += _y;
	}
	D2D_MATRIX_3X2_F GetTransform() { return m_Transform; }

public:
	D2D_MATRIX_3X2_F m_matRender = D2D1::Matrix3x2F::Identity(); // ������ ��ȯ�� ���� ���   
	D2D_MATRIX_3X2_F m_matWorld = D2D1::Matrix3x2F::Identity(); // ���� ��ǥ�� ��ȯ�� ���� ���

	float m_locCameraX = 0;
	float m_locCameraY = 0;
	D2D_MATRIX_3X2_F m_matCamera = D2D1::Matrix3x2F::Identity(); // ī�޶� ��ǥ�� ��ȯ�� ���� ���
	D2D_MATRIX_3X2_F m_matScreen = D2D1::Matrix3x2F::Identity(); //�����ϴ��� 0,0�� ��ũ�� ��ǥ�� ��ȯ�� ���� ���

	D2D_MATRIX_3X2_F m_Transform;
};