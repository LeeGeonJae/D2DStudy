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
	// Ű�� ��� ���¸� false�� ����
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
			// Ű�� �����ִ�
			if (GetAsyncKeyState(g_arrVK[i]) & 0x8000)
			{
				if (m_ArrayKey[i].PrevPush)
				{
					// �������� ���� �־���.
					m_ArrayKey[i].State = KEY_STATE::HOLD;
				}
				else
				{
					// ������ �������� �ʾҴ�.
					m_ArrayKey[i].State = KEY_STATE::TAP;
				}

				m_ArrayKey[i].PrevPush = true;
			}

			// Ű�� �ȴ����ִ�
			else
			{
				if (m_ArrayKey[i].PrevPush)
				{
					// ������ ���� �־���.
					m_ArrayKey[i].State = KEY_STATE::AWAY;
				}
				else
				{
					// �������� �������� �ʾҴ�.
					m_ArrayKey[i].State = KEY_STATE::NONE;
				}

				m_ArrayKey[i].PrevPush = false;
			}
		}
	}

	// ������ ��Ŀ�� ��������
	else
	{
		// ���࿡ ������ ��Ŀ���� ������ ���¶�� ��� Ű�� ���¸� AWAY�� NONE ���·� ��ȯ�ϰ� bPrevPush�� false�� ����
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
