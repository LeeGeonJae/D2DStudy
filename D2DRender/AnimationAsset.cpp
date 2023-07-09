#include "pch.h"
#include "AnimationAsset.h"
#include "D2DRenderer.h"
#include "ResourceManager.h"

AnimationAsset::AnimationAsset()
	:m_pBitmap(nullptr)
{

}

AnimationAsset::~AnimationAsset()
{
}

void AnimationAsset::SetBitmapFilePath(const WCHAR* szFilePath)
{
	m_BitmapFilePath = szFilePath;
}