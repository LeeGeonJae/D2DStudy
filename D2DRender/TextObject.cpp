#include "pch.h"
#include "TextObject.h"

void TextObject::Init(ResourceManager* _ResourceManager, PathManager* _PathManager)
{
	// ��Ʈ ������Ʈ ����
	m_pRootComponent = new SceneComponent;

	// �ؽ�Ʈ ������Ʈ ����
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
