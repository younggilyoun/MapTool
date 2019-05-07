#include "DXCommon.h"
#include "WinCommon.h"

#include "WindowsMgr.h"

LRESULT CALLBACK MsgProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

WindowsMgr::WindowsMgr(void)
{
	m_hWnd		= NULL;
	m_iHeight	= 0;
	m_iWidth	= 0;
}

WindowsMgr::~WindowsMgr(void)
{
	Release();
}

void WindowsMgr::Init( int w, int h )
{
	m_iWidth	= w;
	m_iHeight	= h;

	WNDCLASSEX wc = 
	{
		sizeof(WNDCLASSEX),
		CS_CLASSDC,
		MsgProc,
		0, 0,
		GetModuleHandle(NULL), NULL, NULL,
		(HBRUSH)GetStockObject(WHITE_BRUSH),
		NULL, "YGProject", NULL
	};

	RegisterClassEx(&wc);

	m_hWnd = CreateWindow( "YGProject", "YGProject",
		WS_OVERLAPPEDWINDOW,
		0, 0, m_iWidth, m_iHeight, GetDesktopWindow(), NULL,
		wc.hInstance, NULL);

	ShowWindow(m_hWnd, SW_SHOW);

	ResizeWindow();
}

void WindowsMgr::Loop( void )
{
	while( 1 )
	{
		if( MessagePump() == false )
			break;

		// 여기에서 다이렉트 렌더링부분 업데이트부분
		MYINPUT->UpdateDirectInput();
		GAMEMGR->GameLoop();
	}
}

bool WindowsMgr::MessagePump( void )
{
	MSG msg;
	ZeroMemory(&msg, sizeof(msg));

	while( 1 )
	{
		if( PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			if( msg.message == WM_QUIT )
				return false;

			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else
			return true;
	}

	return false;
}

void WindowsMgr::Release( void )
{

}

void WindowsMgr::ResizeWindow( void )
{
	RECT oldrc;
	DWORD sytle = (DWORD)GetWindowLong(m_hWnd, GWL_STYLE);
	DWORD exsytle = (DWORD)GetWindowLong(m_hWnd, GWL_EXSTYLE);

	// 현재 윈도우 크기 얻기
	GetWindowRect(m_hWnd, &oldrc);

	// 클라이언트 영역
	RECT newrc;
	newrc.left = 0;
	newrc.top = 0;
	newrc.right = m_iWidth;
	newrc.bottom = m_iHeight;

	// 클라이언트 영역 재설정
	AdjustWindowRectEx(&newrc, sytle, NULL, exsytle);

	int width = (newrc.right - newrc.left);
	int height = (newrc.bottom - newrc.top);

	SetWindowPos(m_hWnd, HWND_NOTOPMOST, oldrc.left, oldrc.top,
		width, height, SWP_SHOWWINDOW);
}

LRESULT CALLBACK MsgProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch( msg )
	{
	case WM_KEYDOWN:

		switch( wParam )
		{
		case VK_ESCAPE:
			SendMessage(hWnd, WM_DESTROY, 0, 0);
			break;
		}

		return 0;

	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	}

	return DefWindowProc(hWnd, msg, wParam, lParam);
}