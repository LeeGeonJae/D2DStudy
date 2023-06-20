#pragma once
#include <vector>

using namespace std;

enum KEY_STATE
{
	NONE,	// ������ �ʾҰ�, �������� ������ ���� ����
	TAP,	// �� ���� ����
	HOLD,	// ������ �ִ�
	AWAY,	// �� �� ����
};

enum class KEY
{
	LEFT,
	RIGHT,
	UP,
	DOWN,
	Q,
	W,
	E,
	R,
	T,
	Y,
	U,
	I,
	O,
	P,
	A,
	S,
	D,
	F,
	G,
	H,
	J,
	K,
	L,
	Z,
	X,
	C,
	V,
	B,
	N,
	M,
	N_1,
	N_2,
	N_3,
	N_4,
	N_5,
	N_6,
	N_7,
	N_8,
	N_9,

	ALT,
	CTRL,
	LSHIFT,
	SPACE,
	ENTER,
	ESC,
	LBTN,
	RBTN,

	LAST,
};

struct tKeyInfo
{
	KEY_STATE	State;			// Ű�� ���°�
	bool		PrevPush;		// ���� �����ӿ��� ���ȴ��� ����
};

class KeyManager
{
public:
	KeyManager();
	~KeyManager();

public:
	void Initialize();
	void Update();

public:
	KEY_STATE GetKeyState(KEY _eKey) { return m_ArrayKey[(int)_eKey].State; }
	//void SetMousePos(int _x, int _y) { m_Mouse_Pos.x = _x; m_Mouse_Pos.y = _y; }
	//POINT GetMousePos() { return m_Mouse_Pos; }

private:
	vector<tKeyInfo> m_ArrayKey;
	//POINT m_Mouse_Pos;
};