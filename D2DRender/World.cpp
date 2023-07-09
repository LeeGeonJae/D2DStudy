#include "pch.h"
#include "World.h"
#include "GameObject.h"
#include "D2DRenderer.h"
#include "TimeManager.h"
#include "CameraManager.h"
#include "ResourceManager.h"

World::World()
	//:m_FocusCameraComponent()
{

}

World::~World()
{
	for (auto& pObjects : m_GameObjects)
	{
		if (pObjects != nullptr)
		{
			delete pObjects;
			pObjects = nullptr;
		}
	}
}

bool World::Init(ResourceManager* _ResourceManager, PathManager* _PathManager)
{
	for (auto& pObjects : m_GameObjects)
	{
		pObjects->Init(_ResourceManager, _PathManager);
	}

	return true;
}

void World::Update(TimeManager* _TimeManager)
{
	for (auto& pObjects : m_GameObjects)
	{
		pObjects->Update(_TimeManager);
	}
}

void World::Render(ID2D1RenderTarget* pRenderTarget)
{
	// 렌더러 박스 그리기
	D2D_MATRIX_3X2_F pivot = D2D_MATRIX_3X2_F(D2D1::IdentityMatrix());

	pRenderTarget->SetTransform(pivot);
	pRenderTarget->DrawRectangle(D2D1_RECT_F{ 200, 200, 1700, 800 }, D2DRenderer::m_Instance->m_pGrayBrush, 3.f);

	// 컬 카운트 텍스쳐 그리기
	pivot._32 += 50.f;
	pivot._31 += 50.f;
	pRenderTarget->SetTransform(pivot);

	std::wstring Text;
	Text = L"Cull Count : ";
	Text += std::to_wstring(CameraManager::m_pInstance->CullCount);

	pRenderTarget->DrawText
	(Text.c_str()
		, Text.size()
		, D2DRenderer::m_Instance->m_pDWriteTextFormat
		, D2D1::Rect((0.f), 0.f, D2DRenderer::m_Instance->m_pD2DRenderTarget->GetSize().height
			, 0.f)
		, D2DRenderer::m_Instance->m_pGrayBrush
	);

	CameraManager::m_pInstance->CullCount = 0;

	// 오브젝트들 그려주기
	for (auto& pObjects : m_GameObjects)
	{
		pObjects->Render(pRenderTarget);
	}
}