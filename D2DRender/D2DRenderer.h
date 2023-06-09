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
	// 기본 D2D사용을 위한 Factory의 인터페이스 포인터
	ID2D1Factory* m_pD2D1Factory = NULL;
	ID2D1HwndRenderTarget* m_pD2DRenderTarget = NULL;

	// 렌더 타겟에서 생성한 브러쉬의 인터페이스 포인터
	ID2D1SolidColorBrush* m_pGrayBrush = NULL;
	ID2D1SolidColorBrush* m_pBlackBrush = NULL;

	// 텍스트 출력을 위한 객체 인터페이스 포인터
	IDWriteFactory* m_pWriteFactory = NULL;
	IDWriteTextFormat* m_pWriteTextFormat = NULL;

	// WIC 인터페이스
	IWICImagingFactory* m_pIWICImagingFactory = NULL;

	// 이미지로드후 생성하고 받아오는 인터페이스
	ID2D1Bitmap* m_pD2DBitmap = NULL;
};