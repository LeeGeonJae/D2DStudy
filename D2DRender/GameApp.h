#pragma once

class D2DRenderer;

#define MAX_LOADSTRING 100

class GameApp
{
public:
	GameApp(HINSTANCE hInstance);
	virtual ~GameApp();

	bool Initialize();
	void Loop();
	virtual void Update();
	virtual void Render();
	void Uninitalize();


protected:
	D2DRenderer* m_Renderer;

	WNDCLASSEXW m_wcex;
	HINSTANCE m_hInst;
	MSG m_msg;
	HWND m_hWnd;
	HACCEL m_hAccelTable;
	WCHAR m_szTitle[MAX_LOADSTRING];                  // 제목 표시줄 텍스트입니다.
	WCHAR m_szWindowClass[MAX_LOADSTRING];            // 기본 창 클래스 이름입니다.
}; 