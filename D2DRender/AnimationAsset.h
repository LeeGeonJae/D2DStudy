#pragma once

#include "ReferenceCounter.h"
#include <vector>

class ResourceManager;

// �ִϸ��̼� �⺻ �������� �⺻ ����
struct FRAME_INFO
{
	D2D1_RECT_F Source;		// �̹��� ���Ͽ��� ��� ���� Rect�� ���� ���������� �����Ѵ�.
	float		RenderTime; // �׸��� �ð�

	FRAME_INFO(float x, float y, float with, float height, float time)
	{
		Source.left = x;
		Source.top = y;
		Source.right = x + with;
		Source.bottom = y + height;
		RenderTime = time;
	}
	FRAME_INFO(D2D1_RECT_F rect, float time)
	{
		Source = rect;
		RenderTime = time;
	}
};

/*
	�ִϸ��̼ǿ� �ʿ��� �������ʴ� ������ �ڻ�
*/
class AnimationAsset : public ReferenceCounter
{
	// �ı��� Release�� , ������ D2DRenderer�� �ϰ��Ѵ�.
public:
	AnimationAsset();
	virtual ~AnimationAsset();

public:
	ID2D1Bitmap* m_pBitmap;
	std::wstring m_BitmapFilePath;

	std::vector<std::vector<FRAME_INFO>> m_Animations;

	void SetBitmapFilePath(const WCHAR* szFilePath);
	void SetBitmap(ID2D1Bitmap* _bitmap)
	{
		m_pBitmap = _bitmap;
	}
private:

};