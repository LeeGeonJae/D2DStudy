#pragma once

#include <d2d1.h>
#include <d2d1_1helper.h>
#include <dwrite.h>
#include <wincodec.h>
#include <comdef.h>

class D2DRenderer
{
public:
	D2DRenderer();
	~D2DRenderer();


	bool Initialize(HWND hWnd);
	void Uninitialize();

public:
	HRESULT CreateD2DBitmapFromFile(HWND hWnd, const WCHAR* szFilePath, ID2D1Bitmap** pID2D1Bitmap);

public:
	// �⺻ D2D����� ���� Factory�� �������̽� ������
	ID2D1Factory* m_pD2D1Factory = NULL;
	ID2D1HwndRenderTarget* m_pD2DRenderTarget = NULL;

	// ���� Ÿ�ٿ��� ������ �귯���� �������̽� ������
	ID2D1SolidColorBrush* m_pGrayBrush = NULL;
	ID2D1SolidColorBrush* m_pBlackBrush = NULL;

	// �ؽ�Ʈ ����� ���� ��ü �������̽� ������
	IDWriteFactory* m_pWriteFactory = NULL;
	IDWriteTextFormat* m_pWriteTextFormat = NULL;

	// WIC �������̽�
	IWICImagingFactory* m_pIWICImagingFactory = NULL;

	// �̹����ε��� �����ϰ� �޾ƿ��� �������̽�
	ID2D1Bitmap* m_pD2DBitmap = NULL;
};