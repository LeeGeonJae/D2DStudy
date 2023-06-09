#pragma once
#include <list>
#include <string>
#include <d2d1_1.h>

class D2DRenderer
{
public:
	D2DRenderer();
	~D2DRenderer();
	HRESULT Initialize();
	static ID2D1HwndRenderTarget* m_pD2DRenderTarget;
	static D2DRenderer* m_Instance;

public:
	ID2D1Factory* m_pD2DFactory = NULL;				// 기본 D2D사용을 위한 Factory의 인터페이스 포인터
	IDWriteFactory* m_pDWriteFactory = NULL;		// 텍스트 출력을 위한 객체 인터페이스 포인터
	IDWriteTextFormat* m_pDWriteTextFormat = NULL;
	IWICImagingFactory* m_pIWICImagingFactory = NULL;	// WIC 인터페이스

public:
	ID2D1SolidColorBrush* m_pGrayBrush = NULL;	// 렌더타겟에서생성한 브러시의 인터페이스 포인터
	ID2D1SolidColorBrush* m_pBlackBrush = NULL;
	ID2D1SolidColorBrush* m_pRedBrush = NULL;
	ID2D1SolidColorBrush* m_pGreenBrush = NULL;
	ID2D1SolidColorBrush* m_pWhiteBrush = NULL;
	ID2D1SolidColorBrush* m_pBlueBrush = NULL;
	ID2D1SolidColorBrush* m_pYellowBrush = NULL;

	std::list < std::pair<std::wstring, ID2D1Bitmap*>> m_SharingD2DBitmaps;

public:
	HRESULT CreateD2DBitmapFromFile(std::wstring strFilePath, ID2D1Bitmap** pID2D1Bitmap);
	void ReleaseD2DBitmapFromFile(ID2D1Bitmap* pID2D1Bitmap);
};