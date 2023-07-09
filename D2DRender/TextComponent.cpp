#include "pch.h"
#include "TextComponent.h"
#include "D2DRenderer.h"
#include "CameraManager.h"

TextComponent::TextComponent()
	: m_Color(D2D1::ColorF::Black)
	, m_ColorBrush(nullptr)
	, m_Position()
	, m_TextRect()
{
}

TextComponent::~TextComponent()
{
	if (m_ColorBrush != nullptr)
	{
		m_ColorBrush->Release();
		m_ColorBrush = nullptr;
	}
}

void TextComponent::Init(ResourceManager* _ResourceManager)
{
	m_TextRect = D2D1_RECT_F{ 0.f, 0.f
		, D2DRenderer::m_Instance->m_pD2DRenderTarget->GetSize().height
		, D2DRenderer::m_Instance->m_pD2DRenderTarget->GetSize().width };

	__super::Init(_ResourceManager);
}

void TextComponent::Update(TimeManager* _TimeManager)
{
	m_Text = std::to_wstring((int)m_WorldTransform.dx);
	m_Text += ',';
	m_Text += std::to_wstring((int)m_WorldTransform.dy);

	__super::Update(_TimeManager);
}

void TextComponent::Render(ID2D1RenderTarget* _pRenderTarget)
{
	if (CameraManager::m_pInstance->intersect(m_AABBmin, m_AABBmax))
	{
		_pRenderTarget->SetTransform(m_WorldTransform * CameraManager::m_pInstance->GetInvertTransform());
		_pRenderTarget->CreateSolidColorBrush(m_Color, &m_ColorBrush);

		_pRenderTarget->DrawText
		(m_Text.c_str()
			, (int)m_Text.size()
			, D2DRenderer::m_Instance->m_pDWriteTextFormat
			, D2D1::Rect((-(float)m_Text.size() * 3.8f), 0.f, D2DRenderer::m_Instance->m_pD2DRenderTarget->GetSize().height
				, 0.f)
			, m_ColorBrush
		);

		CameraManager::m_pInstance->CullCount++;
	}
	__super::Render(_pRenderTarget);
}
