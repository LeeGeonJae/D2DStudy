#include "pch.h"
#include "ResourceManager.h"
#include "AnimationAsset.h"
#include "D2DRenderer.h"
#include "PathManager.h"

void ResourceManager::Initialize(PathManager* _pathManager)
{
	// ��� �ؽ��� ����
	std::wstring path = _pathManager->GetContentPath();
	path += L"Texture\\midnight.png";
	CreateTexture(path);
	AnimationAsset* asset = CreateAnimationAsset(path);
	// ��� �ִϸ��̼� ���� ����
	std::vector<FRAME_INFO> midnightframe;
	midnightframe.push_back(FRAME_INFO(0, 0, 784, 320, 0.2f));
	midnightframe.push_back(FRAME_INFO(789, 0, 784, 320, 0.2f));
	midnightframe.push_back(FRAME_INFO(0, 325, 784, 320, 0.2f));
	midnightframe.push_back(FRAME_INFO(789, 325, 784, 320, 0.2f));
	asset->m_Animations.push_back(midnightframe);


	// �޸��� �ؽ��� ����
	std::wstring path1 = _pathManager->GetContentPath();
	path1 += L"Texture\\run.png";
	CreateTexture(path1);
	asset = CreateAnimationAsset(path1);
	// �޸��� ���ϸ��̼� ���� ����
	std::vector<FRAME_INFO> runframe;
	runframe.push_back(FRAME_INFO(28, 36, 103, 84, 0.1f));
	runframe.push_back(FRAME_INFO(148, 36, 86, 84, 0.1f));
	runframe.push_back(FRAME_INFO(255, 34, 87, 86, 0.1f));
	runframe.push_back(FRAME_INFO(363, 32, 76, 88, 0.1f));
	runframe.push_back(FRAME_INFO(458, 31, 91, 89, 0.1f));
	runframe.push_back(FRAME_INFO(567, 40, 103, 80, 0.1f));
	runframe.push_back(FRAME_INFO(686, 32, 85, 88, 0.1f));
	runframe.push_back(FRAME_INFO(792, 32, 86, 88, 0.1f));
	runframe.push_back(FRAME_INFO(899, 31, 76, 89, 0.1f));
	runframe.push_back(FRAME_INFO(993, 33, 92, 87, 0.1f));
	asset->m_Animations.push_back(runframe);

	//
}

void ResourceManager::CreateTexture(const std::wstring _path)
{
	ID2D1Bitmap* bitmap;
	D2DRenderer::m_Instance->CreateD2DBitmapFromFile(_path, &bitmap);	// ��Ʈ�� ���� ����
	m_mapTexture.insert(make_pair(_path, bitmap));						// �� ����
}

AnimationAsset* ResourceManager::CreateAnimationAsset(const std::wstring _path)
{
	AnimationAsset* animationasset = new AnimationAsset;
	animationasset->SetBitmap(FindTexture(_path));						// ��Ʈ�� ����
	animationasset->SetBitmapFilePath(_path.c_str());					// ��� ����
	m_mapAnimationAsset.insert(make_pair(_path, animationasset));		// �� ����

	return animationasset;
}

ID2D1Bitmap* ResourceManager::FindTexture(const std::wstring _key)
{
	auto iter = m_mapTexture.find(_key);

	if (iter != m_mapTexture.end())
		return iter->second;

	return nullptr;
}

AnimationAsset* ResourceManager::FindAnimationAsset(const std::wstring _key)
{
	auto iter = m_mapAnimationAsset.find(_key);

	if (iter != m_mapAnimationAsset.end())
		return iter->second;

	return nullptr;
}