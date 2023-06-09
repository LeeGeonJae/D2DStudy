#include "pch.h"
#include "framework.h"
#include "D2DRenderer.h"

// TODO: 라이브러리 함수의 예제입니다.
void fnD2DRender()
{
}

D2DRenderer::D2DRenderer()
{
}

D2DRenderer::~D2DRenderer()
{

}

bool D2DRenderer::Initialize(HWND hWnd)
{
    HRESULT hr;

    // COM사용
    hr = CoInitialize(NULL);

    // 렌더타겟을 만들 수 있는 팩토리 객체를 생성하고 인터페이스 포인터를 얻어온다.
    if (SUCCEEDED(hr))
    {
        hr = D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, &m_pD2D1Factory);
    }

    // 이미 윈도우가 만들어진 상태에서 윈도우 사이즈를 구한다.
    RECT rc;
    GetClientRect(hWnd, &rc);

    D2D1_SIZE_U size = D2D1::SizeU(
        static_cast<UINT>(rc.right - rc.left),
        static_cast<UINT>(rc.bottom - rc.top)
    );

    // 팩토리로 윈도우 핸들, 사이즈를 넘겨 렌더타겟을 만든다.
    if (SUCCEEDED(hr))
    {
        hr = m_pD2D1Factory->CreateHwndRenderTarget(
            D2D1::RenderTargetProperties(),
            D2D1::HwndRenderTargetProperties(hWnd, size),
            &m_pD2DRenderTarget
        );
    }

    // 회색 브러시 생성
	// Direct2D 렌더 타겟(g_pD2DRenderTarget)에서 회색을 나타내는 솔리드 브러시를 생성합니다.
	// CreateSolidColorBrush 함수는 D2D1::ColorF 구조체를 사용하여 지정된 색상으로 솔리드 브러시를 만듭니다.
	// 이 솔리드 브러시는 회색으로 설정되고, 생성된 브러시의 포인터는 g_pGrayBrush에 저장됩니다.
    if (SUCCEEDED(hr))
    {
        hr = m_pD2DRenderTarget->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::Gray), &m_pGrayBrush);
    }

    // 검정색 브러시 생성
    // Direct2D 렌더 타겟(g_pD2DRenderTarget)에서 검정색을 나타내는 솔리드 브러시를 생성합니다.
    // CreateSolidColorBrush 함수를 사용하여 검정색 솔리드 브러시를 만듭니다.
    // 생성된 브러시의 포인터는 g_pBlackBrush에 저장됩니다.
    if (SUCCEEDED(hr))
    {
        hr = m_pD2DRenderTarget->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::Black), &m_pBlackBrush);
    }


    // DirectWrite 팩토리 생성
    // DWriteCreateFactory 함수를 사용하여 DirectWrite 팩토리(g_pWriteFactory)를 생성합니다.
    // 이 팩토리를 사용하여 텍스트 렌더링과 관련된 작업을 수행할 수 있습니다.
    // DWRITE_FACTORY_TYPE_SHARED 플래그를 사용하여 공유 팩토리를 생성합니다.
    if (SUCCEEDED(hr))
    {
        hr = DWriteCreateFactory(
            DWRITE_FACTORY_TYPE_SHARED,
            __uuidof(m_pWriteFactory),
            reinterpret_cast<IUnknown**>(&m_pWriteFactory)
        );
    }


    // 텍스트 형식 생성
    // CreateTextFormat 함수를 사용하여 텍스트 형식(g_pWriteTextFormat)을 생성합니다.
    // "Agency FB"라는 글꼴을 사용하고, 기본 설정으로 텍스트 형식을 초기화합니다.
    // 텍스트의 두께는 NORMAL, 스타일은 NORMAL, 스트레치는 NORMAL로 설정됩니다.
    // 텍스트 크기는 50.f로 설정되며, 현재 로캘(locale)은 사용하지 않습니다.
    // 생성된 텍스트 형식의 포인터는 g_pWriteTextFormat에 저장됩니다.
    if (SUCCEEDED(hr))
    {
        hr = m_pWriteFactory->CreateTextFormat(
            L"Agency FB",
            NULL,
            DWRITE_FONT_WEIGHT_NORMAL,
            DWRITE_FONT_STYLE_NORMAL,
            DWRITE_FONT_STRETCH_NORMAL,
            50.f,
            L"", //locale
            &m_pWriteTextFormat
        );
    }


    // 텍스트 정렬 설정
    // 텍스트 형식(g_pWriteTextFormat)에 대해 텍스트 정렬을 설정합니다.
    // SetTextAlignment 함수를 사용하여 텍스트를 수평으로 가운데에 정렬하고,
    // SetParagraphAlignment 함수를 사용하여 텍스트를 수직으로 가운데에 정렬합니다.
    // Center the text horizontally and vertically.
    m_pWriteTextFormat->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_LEADING);
    m_pWriteTextFormat->SetParagraphAlignment(DWRITE_PARAGRAPH_ALIGNMENT_CENTER);


    // WIC 팩토리 생성
    // CoCreateInstance 함수를 사용하여 WIC(Windows Imaging Component) 팩토리(g_pIWICImagingFactory)를 생성합니다.
    // WIC 팩토리는 이미지 처리 작업에 사용되며, 이미지 디코딩, 변환 등을 처리할 수 있습니다.
    // CLSID_WICImagingFactory는 WIC 팩토리의 클래스 식별자이며, IID_PPV_ARGS는 인터페이스를 얻기 위한 매크로입니다.
    // 생성된 WIC 팩토리의 포인터는 g_pIWICImagingFactory에 저장됩니다.
    if (SUCCEEDED(hr))
    {
        hr = CoCreateInstance(
            CLSID_WICImagingFactory,
            NULL,
            CLSCTX_INPROC_SERVER,
            IID_PPV_ARGS(&m_pIWICImagingFactory)
        );
    }

    // 비트맵 이미지 파일 가져오기
    if (SUCCEEDED(hr))
    {
        hr = CreateD2DBitmapFromFile(hWnd, L"..\\Resource\\atk_1.png", &m_pD2DBitmap);
    }

    return true;
}

void D2DRenderer::Uninitialize()
{
    if (m_pD2DBitmap != NULL) m_pD2DBitmap->Release();

    // WIC해제
    if (m_pIWICImagingFactory != NULL)
        m_pIWICImagingFactory->Release();
        
    // 만드는 순서 거꾸로 릴리즈
    if (m_pWriteFactory != NULL)
        m_pWriteFactory->Release();
    if (m_pWriteTextFormat != NULL)
        m_pWriteTextFormat->Release();

    if (m_pGrayBrush != NULL)
        m_pGrayBrush->Release();
    if (m_pBlackBrush != NULL)
        m_pBlackBrush->Release();

    // 해제
    if (m_pD2DRenderTarget != NULL)
        m_pD2DRenderTarget->Release();
    if (m_pD2D1Factory != NULL)
        m_pD2D1Factory->Release();

    //COM사용끝
    CoUninitialize();
}

HRESULT D2DRenderer::CreateD2DBitmapFromFile(HWND hWnd, const WCHAR* szFilePath, ID2D1Bitmap** pID2D1Bitmap)
{
    HRESULT hr = S_OK;

    // 디코더 생성
    IWICBitmapDecoder* pDecoder = NULL;

    // 파일명을 사용하여 이미지를 디코딩하는 디코더 생성
    hr = m_pIWICImagingFactory->CreateDecoderFromFilename(
        szFilePath,                      // 디코딩할 이미지 파일 경로
        NULL,                            // 특정 벤더를 선호하지 않음
        GENERIC_READ,                    // 파일에 대한 읽기 접근 권한
        WICDecodeMetadataCacheOnDemand,  // 필요할 때 메타데이터 캐시
        &pDecoder                        // 디코더를 가리키는 포인터
    );

    // 디코더로부터 이미지의 첫 번째 프레임 가져오기
    IWICBitmapFrameDecode* pFrame = NULL;

    if (SUCCEEDED(hr))
    {
        hr = pDecoder->GetFrame(0, &pFrame);
    }

    IWICFormatConverter* pConverter = NULL;

    // 단계 3: 프레임을 32bppPBGRA 형식으로 변환하기 위한 포맷 컨버터 생성
    if (SUCCEEDED(hr))
    {
        hr = m_pIWICImagingFactory->CreateFormatConverter(&pConverter);
    }

    if (SUCCEEDED(hr))
    {
        hr = pConverter->Initialize(
            pFrame,                          // 변환할 입력 비트맵
            GUID_WICPixelFormat32bppPBGRA,   // 목적지 픽셀 형식
            WICBitmapDitherTypeNone,         // 지정된 디더 패턴
            NULL,                            // 특정 팔레트 지정 없음
            0.f,                             // 알파 임계값
            WICBitmapPaletteTypeCustom       // 팔레트 변환 유형
        );
    }

    // D2D 렌더 타겟으로부터 WIC 비트맵으로부터 비트맵 생성
    m_pD2DRenderTarget->CreateBitmapFromWicBitmap(pConverter, NULL, pID2D1Bitmap);

    if (pFrame != NULL)
        pFrame->Release();

    if (pDecoder != NULL)
        pDecoder->Release();

    if (pConverter != NULL)
        pConverter->Release();

    if (FAILED(hr))
    {
        _com_error err(hr);
        MessageBox(hWnd, err.ErrorMessage(), L"FAILED", MB_OK);
    }

    return hr;
}