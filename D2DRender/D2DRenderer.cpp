#include "pch.h"
#include "framework.h"
#include "D2DRenderer.h"

// TODO: ���̺귯�� �Լ��� �����Դϴ�.
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

    // COM���
    hr = CoInitialize(NULL);

    // ����Ÿ���� ���� �� �ִ� ���丮 ��ü�� �����ϰ� �������̽� �����͸� ���´�.
    if (SUCCEEDED(hr))
    {
        hr = D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, &m_pD2D1Factory);
    }

    // �̹� �����찡 ������� ���¿��� ������ ����� ���Ѵ�.
    RECT rc;
    GetClientRect(hWnd, &rc);

    D2D1_SIZE_U size = D2D1::SizeU(
        static_cast<UINT>(rc.right - rc.left),
        static_cast<UINT>(rc.bottom - rc.top)
    );

    // ���丮�� ������ �ڵ�, ����� �Ѱ� ����Ÿ���� �����.
    if (SUCCEEDED(hr))
    {
        hr = m_pD2D1Factory->CreateHwndRenderTarget(
            D2D1::RenderTargetProperties(),
            D2D1::HwndRenderTargetProperties(hWnd, size),
            &m_pD2DRenderTarget
        );
    }

    // ȸ�� �귯�� ����
	// Direct2D ���� Ÿ��(g_pD2DRenderTarget)���� ȸ���� ��Ÿ���� �ָ��� �귯�ø� �����մϴ�.
	// CreateSolidColorBrush �Լ��� D2D1::ColorF ����ü�� ����Ͽ� ������ �������� �ָ��� �귯�ø� ����ϴ�.
	// �� �ָ��� �귯�ô� ȸ������ �����ǰ�, ������ �귯���� �����ʹ� g_pGrayBrush�� ����˴ϴ�.
    if (SUCCEEDED(hr))
    {
        hr = m_pD2DRenderTarget->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::Gray), &m_pGrayBrush);
    }

    // ������ �귯�� ����
    // Direct2D ���� Ÿ��(g_pD2DRenderTarget)���� �������� ��Ÿ���� �ָ��� �귯�ø� �����մϴ�.
    // CreateSolidColorBrush �Լ��� ����Ͽ� ������ �ָ��� �귯�ø� ����ϴ�.
    // ������ �귯���� �����ʹ� g_pBlackBrush�� ����˴ϴ�.
    if (SUCCEEDED(hr))
    {
        hr = m_pD2DRenderTarget->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::Black), &m_pBlackBrush);
    }


    // DirectWrite ���丮 ����
    // DWriteCreateFactory �Լ��� ����Ͽ� DirectWrite ���丮(g_pWriteFactory)�� �����մϴ�.
    // �� ���丮�� ����Ͽ� �ؽ�Ʈ �������� ���õ� �۾��� ������ �� �ֽ��ϴ�.
    // DWRITE_FACTORY_TYPE_SHARED �÷��׸� ����Ͽ� ���� ���丮�� �����մϴ�.
    if (SUCCEEDED(hr))
    {
        hr = DWriteCreateFactory(
            DWRITE_FACTORY_TYPE_SHARED,
            __uuidof(m_pWriteFactory),
            reinterpret_cast<IUnknown**>(&m_pWriteFactory)
        );
    }


    // �ؽ�Ʈ ���� ����
    // CreateTextFormat �Լ��� ����Ͽ� �ؽ�Ʈ ����(g_pWriteTextFormat)�� �����մϴ�.
    // "Agency FB"��� �۲��� ����ϰ�, �⺻ �������� �ؽ�Ʈ ������ �ʱ�ȭ�մϴ�.
    // �ؽ�Ʈ�� �β��� NORMAL, ��Ÿ���� NORMAL, ��Ʈ��ġ�� NORMAL�� �����˴ϴ�.
    // �ؽ�Ʈ ũ��� 50.f�� �����Ǹ�, ���� ��Ķ(locale)�� ������� �ʽ��ϴ�.
    // ������ �ؽ�Ʈ ������ �����ʹ� g_pWriteTextFormat�� ����˴ϴ�.
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


    // �ؽ�Ʈ ���� ����
    // �ؽ�Ʈ ����(g_pWriteTextFormat)�� ���� �ؽ�Ʈ ������ �����մϴ�.
    // SetTextAlignment �Լ��� ����Ͽ� �ؽ�Ʈ�� �������� ����� �����ϰ�,
    // SetParagraphAlignment �Լ��� ����Ͽ� �ؽ�Ʈ�� �������� ����� �����մϴ�.
    // Center the text horizontally and vertically.
    m_pWriteTextFormat->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_LEADING);
    m_pWriteTextFormat->SetParagraphAlignment(DWRITE_PARAGRAPH_ALIGNMENT_CENTER);


    // WIC ���丮 ����
    // CoCreateInstance �Լ��� ����Ͽ� WIC(Windows Imaging Component) ���丮(g_pIWICImagingFactory)�� �����մϴ�.
    // WIC ���丮�� �̹��� ó�� �۾��� ���Ǹ�, �̹��� ���ڵ�, ��ȯ ���� ó���� �� �ֽ��ϴ�.
    // CLSID_WICImagingFactory�� WIC ���丮�� Ŭ���� �ĺ����̸�, IID_PPV_ARGS�� �������̽��� ��� ���� ��ũ���Դϴ�.
    // ������ WIC ���丮�� �����ʹ� g_pIWICImagingFactory�� ����˴ϴ�.
    if (SUCCEEDED(hr))
    {
        hr = CoCreateInstance(
            CLSID_WICImagingFactory,
            NULL,
            CLSCTX_INPROC_SERVER,
            IID_PPV_ARGS(&m_pIWICImagingFactory)
        );
    }

    // ��Ʈ�� �̹��� ���� ��������
    if (SUCCEEDED(hr))
    {
        hr = CreateD2DBitmapFromFile(hWnd, L"..\\Resource\\atk_1.png", &m_pD2DBitmap);
    }

    return true;
}

void D2DRenderer::Uninitialize()
{
    if (m_pD2DBitmap != NULL) m_pD2DBitmap->Release();

    // WIC����
    if (m_pIWICImagingFactory != NULL)
        m_pIWICImagingFactory->Release();
        
    // ����� ���� �Ųٷ� ������
    if (m_pWriteFactory != NULL)
        m_pWriteFactory->Release();
    if (m_pWriteTextFormat != NULL)
        m_pWriteTextFormat->Release();

    if (m_pGrayBrush != NULL)
        m_pGrayBrush->Release();
    if (m_pBlackBrush != NULL)
        m_pBlackBrush->Release();

    // ����
    if (m_pD2DRenderTarget != NULL)
        m_pD2DRenderTarget->Release();
    if (m_pD2D1Factory != NULL)
        m_pD2D1Factory->Release();

    //COM��볡
    CoUninitialize();
}

HRESULT D2DRenderer::CreateD2DBitmapFromFile(HWND hWnd, const WCHAR* szFilePath, ID2D1Bitmap** pID2D1Bitmap)
{
    HRESULT hr = S_OK;

    // ���ڴ� ����
    IWICBitmapDecoder* pDecoder = NULL;

    // ���ϸ��� ����Ͽ� �̹����� ���ڵ��ϴ� ���ڴ� ����
    hr = m_pIWICImagingFactory->CreateDecoderFromFilename(
        szFilePath,                      // ���ڵ��� �̹��� ���� ���
        NULL,                            // Ư�� ������ ��ȣ���� ����
        GENERIC_READ,                    // ���Ͽ� ���� �б� ���� ����
        WICDecodeMetadataCacheOnDemand,  // �ʿ��� �� ��Ÿ������ ĳ��
        &pDecoder                        // ���ڴ��� ����Ű�� ������
    );

    // ���ڴ��κ��� �̹����� ù ��° ������ ��������
    IWICBitmapFrameDecode* pFrame = NULL;

    if (SUCCEEDED(hr))
    {
        hr = pDecoder->GetFrame(0, &pFrame);
    }

    IWICFormatConverter* pConverter = NULL;

    // �ܰ� 3: �������� 32bppPBGRA �������� ��ȯ�ϱ� ���� ���� ������ ����
    if (SUCCEEDED(hr))
    {
        hr = m_pIWICImagingFactory->CreateFormatConverter(&pConverter);
    }

    if (SUCCEEDED(hr))
    {
        hr = pConverter->Initialize(
            pFrame,                          // ��ȯ�� �Է� ��Ʈ��
            GUID_WICPixelFormat32bppPBGRA,   // ������ �ȼ� ����
            WICBitmapDitherTypeNone,         // ������ ��� ����
            NULL,                            // Ư�� �ȷ�Ʈ ���� ����
            0.f,                             // ���� �Ӱ谪
            WICBitmapPaletteTypeCustom       // �ȷ�Ʈ ��ȯ ����
        );
    }

    // D2D ���� Ÿ�����κ��� WIC ��Ʈ�����κ��� ��Ʈ�� ����
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