#include "pch.h"
#include "PathManager.h"


PathManager::PathManager()
	: m_szContentPath{}
{

}

PathManager::~PathManager()
{

}

void PathManager::Initialize()
{
	GetCurrentDirectory(255, m_szContentPath);

	int iLen = (int)wcslen(m_szContentPath);

	for (int i = iLen - 1; 0 <= i; --i)
	{
		if ('\\' == m_szContentPath[i])
		{
			m_szContentPath[i] = '\0';
			break;
		}
	}

	wcscat_s(m_szContentPath, 255, L"\\Content\\");
}