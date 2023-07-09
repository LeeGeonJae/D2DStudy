#pragma once

class KeyManager;
class TimeManager;

class CameraManager
{
public:
	CameraManager();
	~CameraManager();

public:
	static CameraManager* m_pInstance;

public:
	void Initialize(D2D1_SIZE_U _size);
	void Update(KeyManager* _KeyManager, TimeManager* _TimeManager);
	bool intersect(D2D_POINT_2F AABBmin, D2D_POINT_2F AABBmax);

public:
	void SetCameraLocation(float _x, float _y) 
	{
		m_locCameraX = _x;
		m_locCameraY = _y;
	}
	void AddCameraLocation(float _x, float _y) 
	{
		m_locCameraX += _x;
		m_locCameraY += _y;
	}
	D2D_MATRIX_3X2_F GetTransform() 
	{ 
		m_Transform = m_matRender * m_matWorld * m_matCamera * m_matScreen;
		return m_Transform; 
	}
	D2D_MATRIX_3X2_F GetInvertTransform();

public:
	D2D_MATRIX_3X2_F m_matRender = D2D1::Matrix3x2F::Identity(); // 렌더링 변환을 위한 행렬   
	D2D_MATRIX_3X2_F m_matWorld = D2D1::Matrix3x2F::Identity(); // 월드 좌표계 변환을 위한 행렬

	float m_locCameraX = 0;
	float m_locCameraY = 0;
	D2D_MATRIX_3X2_F m_matCamera = D2D1::Matrix3x2F::Identity(); // 카메라 좌표계 변환을 위한 행렬
	D2D_MATRIX_3X2_F m_matScreen = D2D1::Matrix3x2F::Identity(); //왼쪽하단이 0,0인 스크린 좌표계 변환을 위한 행렬

	D2D_MATRIX_3X2_F m_Transform;

	int CullCount = 0;
};

