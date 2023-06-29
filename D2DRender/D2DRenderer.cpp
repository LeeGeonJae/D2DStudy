// D2DRenderer.cpp : ���� ���̺귯���� ���� �Լ��� �����մϴ�.
//
#include "pch.h"
#include "framework.h"
#include "D2DRenderer.h"
#include "GameApp.h"

#pragma comment(lib,"d2d1.lib")
#pragma comment(lib,"dwrite.lib")

ID2D1HwndRenderTarget* D2DRenderer::m_pD2DRenderTarget = nullptr;
D2DRenderer* D2DRenderer::m_Instance = nullptr;

D2DRenderer::D2DRenderer()
{
    D2DRenderer::m_Instance = this; // ��𼭴� ������ ��ü�� �����ϱ� ���� �ν��Ͻ��� �����صд�.
}

D2DRenderer::~D2DRenderer()
{
    if (m_pIWICImagingFactory) m_pIWICImagingFactory->Release();
    if (m_pD2DRenderTarget) m_pD2DRenderTarget->Release();
    if (m_pD2DFactory) m_pD2DFactory->Release();
    if (m_pGrayBrush) m_pGrayBrush->Release();
    if (m_pBlackBrush) m_pBlackBrush->Release();

    // COM ��� ��
    CoUninitialize();
}

HRESULT D2DRenderer::Initialize()
{
    // COM���
    HRESULT hr = S_OK;
    hr = CoInitialize(NULL);
    if (SUCCEEDED(hr))
    {
        // ����Ÿ���� ������ִ����丮��ü�� �����ϰ� �������̽� �����͸����´�.
        hr = D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, &m_pD2DFactory);
    }

    if (SUCCEEDED(hr))
    {
        // �̹� �����찡������� ���¿��� ������ ����� ���Ѵ�.
        RECT rc;
        GetClientRect(GameApp::m_hWnd, &rc);
        D2D1_SIZE_U size = D2D1::SizeU(
            static_cast<UINT>(rc.right - rc.left),
            static_cast<UINT>(rc.bottom - rc.top)
        );

        // ���丮�� �������ڵ�,����� �Ѱ� ����ī���� �����.
        hr = m_pD2DFactory->CreateHwndRenderTarget(
            D2D1::RenderTargetProperties(),
            D2D1::HwndRenderTargetProperties(GameApp::m_hWnd, size),
            &m_pD2DRenderTarget
        );
    }

    if (SUCCEEDED(hr))
    {
        hr = m_pD2DRenderTarget->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::Gray), &m_pGrayBrush);
    }

    if (SUCCEEDED(hr))
    {
        hr = m_pD2DRenderTarget->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::Black), &m_pBlackBrush);
    }

    if (SUCCEEDED(hr))
    {
        hr = DWriteCreateFactory(
            DWRITE_FACTORY_TYPE_SHARED,
            __uuidof(m_pDWriteFactory),
            reinterpret_cast<IUnknown**>(&m_pDWriteFactory)
        );
    }

    if (SUCCEEDED(hr))
    {
        hr = m_pDWriteFactory->CreateTextFormat(
            L"Bernard MT Condensed",
            NULL,
            DWRITE_FONT_WEIGHT_MEDIUM,
            DWRITE_FONT_STYLE_NORMAL,
            DWRITE_FONT_STRETCH_NORMAL,
            15.0f,
            L"", //locale
            &m_pDWriteTextFormat
        );
    }
    if (SUCCEEDED(hr))
    {
        // Center the text horizontally and vertically.
        m_pDWriteTextFormat->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_LEADING);
        m_pDWriteTextFormat->SetParagraphAlignment(DWRITE_PARAGRAPH_ALIGNMENT_CENTER);
    }

    if (SUCCEEDED(hr))
    {
        // WIC Factory �����ϰ� �������̽� ���
        hr = CoCreateInstance(
            CLSID_WICImagingFactory,
            NULL,
            CLSCTX_INPROC_SERVER,
            IID_PPV_ARGS(&m_pIWICImagingFactory)
        );
    }

    if (FAILED(hr))
    {
        _com_error err(hr);
        MessageBox(GameApp::m_hWnd, err.ErrorMessage(), L"FAILED", MB_OK);
    }


    return hr;
}


HRESULT D2DRenderer::CreateD2DBitmapFromFile(std::wstring strFilePath, ID2D1Bitmap** pID2D1Bitmap)
{
    // ���ڿ��� ������ �ֿ��� ���ڿ��� ������ �ش� ���Ҹ� ã�´�.
    auto it = std::find_if(m_SharingD2DBitmaps.begin(), m_SharingD2DBitmaps.end(),
        [strFilePath](std::pair<std::wstring, ID2D1Bitmap*> ContainerData)
        {
            return (ContainerData.first == strFilePath);
        }
    );

    // ã����� 
    if (it != m_SharingD2DBitmaps.end())
    {
        *pID2D1Bitmap = it->second;
        (*pID2D1Bitmap)->AddRef();
        return S_OK;
    }

    // ��� ���� �����.
    HRESULT hr;
    // Create a decoder
    IWICBitmapDecoder* pDecoder = NULL;

    hr = m_pIWICImagingFactory->CreateDecoderFromFilename(
        strFilePath.c_str(),                      // Image to be decoded
        NULL,                            // Do not prefer a particular vendor
        GENERIC_READ,                    // Desired read access to the file
        WICDecodeMetadataCacheOnDemand,  // Cache metadata when needed
        &pDecoder                        // Pointer to the decoder
    );

    // Retrieve the first frame of the image from the decoder
    IWICBitmapFrameDecode* pFrame = NULL;
    if (SUCCEEDED(hr))
    {
        hr = pDecoder->GetFrame(0, &pFrame);
    }

    IWICFormatConverter* pConverter = NULL;
    //Step 3: Format convert the frame to 32bppPBGRA
    if (SUCCEEDED(hr))
    {
        hr = m_pIWICImagingFactory->CreateFormatConverter(&pConverter);
    }

    if (SUCCEEDED(hr))
    {
        hr = pConverter->Initialize(
            pFrame,                          // Input bitmap to convert
            GUID_WICPixelFormat32bppPBGRA,   // Destination pixel format
            WICBitmapDitherTypeNone,         // Specified dither pattern
            NULL,                            // Specify a particular palette 
            0.f,                             // Alpha threshold
            WICBitmapPaletteTypeCustom       // Palette translation type
        );
    }

    if (SUCCEEDED(hr))
    {
        hr = m_pD2DRenderTarget->CreateBitmapFromWicBitmap(pConverter, NULL, pID2D1Bitmap);
    }

    if (pFrame != NULL)
        pFrame->Release();

    if (pConverter != NULL)
        pConverter->Release();

    if (pDecoder != NULL)
        pDecoder->Release();

    m_SharingD2DBitmaps.push_back(std::make_pair(strFilePath, *pID2D1Bitmap));
    return hr;
}

void D2DRenderer::ReleaseD2DBitmapFromFile(ID2D1Bitmap* pID2D1Bitmap)
{
    ULONG count = pID2D1Bitmap->Release();
    if (count > 0)
        return;

    // ���ڿ��� ������ �ֿ��� �����Ͱ� ������ �ش� ���Ҹ� ã�´�.
    auto it = std::find_if(m_SharingD2DBitmaps.begin(), m_SharingD2DBitmaps.end(),
        [pID2D1Bitmap](std::pair<std::wstring, ID2D1Bitmap*> ContainerData)
        {
            return (ContainerData.second == pID2D1Bitmap);
        }
    );

    // ã����� 
    if (it != m_SharingD2DBitmaps.end())
    {
        m_SharingD2DBitmaps.erase(it);
    }
}