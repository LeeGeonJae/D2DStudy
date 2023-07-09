#include "pch.h"
#include "TextObject.h"

void TextObject::Init(ResourceManager* _ResourceManager, PathManager* _PathManager)
{
	// 루트 컴포넌트 생성
	m_pRootComponent = new SceneComponent;

	// 텍스트 컴포넌트 생성
	m_TextComponent = m_pRootComponent->CreateChild<TextComponent>();
	m_TextComponent->SetColor(D2D1::ColorF::White);

}

void TextObject::Update(TimeManager* _TimeManager)
{
	__super::Update(_TimeManager);
}

void TextObject::Render(ID2D1RenderTarget* _pRenderTarget)
{
	__super::Render(_pRenderTarget);
}
