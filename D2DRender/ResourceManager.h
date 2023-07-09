#pragma once

class AnimationAsset;
class PathManager;

#include <map>

class ResourceManager
{
public:
	ResourceManager();
	~ResourceManager();

private:
	std::map<std::wstring, ID2D1Bitmap*> m_mapTexture;
	std::map<std::wstring, AnimationAsset*> m_mapAnimationAsset;

public:
	void Initialize(PathManager* _pathManager);

	ID2D1Bitmap* CreateTexture(const std::wstring _path);
	ID2D1Bitmap* FindTexture(const std::wstring _key);
	AnimationAsset* CreateAnimationAsset(const std::wstring _path);
	AnimationAsset* FindAnimationAsset(const std::wstring _key);
};