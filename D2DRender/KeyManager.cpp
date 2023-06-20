#include "pch.h"
#include "KeyManager.h"

int g_arrVK[(int)KEY::LAST] =
{
	VK_LEFT,	//LEFT,
	VK_RIGHT,	//RIGHT,
	VK_UP,		//UP,
	VK_DOWN,	//DOWN,
	'Q',
	'W',
	'E',
	'R',
	'T',
	'Y',
	'U',
	'I',
	'O',
	'P',
	'A',
	'S',
	'D',
	'F',
	'G',
	'H',
	'J',
	'K',
	'L',
	'Z',
	'X',
	'C',
	'V',
	'B',
	'N',
	'M',
	'1',
	'2',
	'3',
	'4',
	'5',
	'6',
	'7',
	'8',
	'9',

	VK_MENU,	// ALT
	VK_CONTROL,	// CTRL
	VK_LSHIFT,	// LSHIFT
	VK_SPACE,	// SPACE BAR
	VK_RETURN,	// ENTER
	VK_ESCAPE,	// ESC

	VK_LBUTTON,
	VK_RBUTTON,
};

KeyManager::KeyManager()
{

}

KeyManager::~KeyManager()
{

}

void KeyManager::Initialize()
{
	// 키의 모든 상태를 false로 세팅
	for (int i = 0; i < (int)KEY::LAST; ++i)
	{
		m_ArrayKey.push_back(tKeyInfo{ KEY_STATE::NONE, false });
	}
}

void KeyManager::Update()
{
	HWND hWnd = GetFocus();

	if (nullptr != hWnd)
	{
		for (int i = 0; i < (int)KEY::LAST; ++i)
		{
			// 키가 눌려있다
			if (GetAsyncKeyState(g_arrVK[i]) & 0x8000)
			{
				if (m_ArrayKey[i].PrevPush)
				{
					// 이전에도 눌려 있었다.
					m_ArrayKey[i].State = KEY_STATE::HOLD;
				}
				else
				{
					// 이전에 눌려있지 않았다.
					m_ArrayKey[i].State = KEY_STATE::TAP;
				}

				m_ArrayKey[i].PrevPush = true;
			}

			// 키가 안눌려있다
			else
			{
				if (m_ArrayKey[i].PrevPush)
				{
					// 이전에 눌려 있었다.
					m_ArrayKey[i].State = KEY_STATE::AWAY;
				}
				else
				{
					// 이전에도 눌려있지 않았다.
					m_ArrayKey[i].State = KEY_STATE::NONE;
				}

				m_ArrayKey[i].PrevPush = false;
			}
		}
	}

	// 윈도우 포커싱 해제상태
	else
	{
		// 만약에 윈도우 포커싱이 해제된 상태라면 모든 키의 상태를 AWAY와 NONE 상태로 전환하고 bPrevPush를 false로 세팅
		for (int i = 0; i < (int)KEY::LAST; ++i)
		{
			m_ArrayKey[i].PrevPush = false;

			if (m_ArrayKey[i].State == KEY_STATE::TAP || m_ArrayKey[i].State == KEY_STATE::HOLD)
			{
				m_ArrayKey[i].State = KEY_STATE::AWAY;
			}
			else if (m_ArrayKey[i].State == KEY_STATE::AWAY)
			{
				m_ArrayKey[i].State = KEY_STATE::NONE;
			}
		}
	}
}
