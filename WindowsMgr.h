#pragma once

#include "MySingleton.h"

class WindowsMgr : public MySingleton<WindowsMgr>
{
public:
	void Init(int w, int h);
	void Loop(void);
	bool MessagePump(void);
	void Release(void);
	void ResizeWindow(void);

public:
	HWND GetHwnd(void)		{ return m_hWnd; }
	int	 GetWidth(void)		{ return m_iWidth; }
	int  GetHeight(void)	{ return m_iHeight; }

	HWND GetViewHwnd(void)	{ return  m_ViewhWnd; }
	void ViewSetHWND(HWND _hwnd)	{ m_ViewhWnd = _hwnd;}	
	void SetHWND(HWND _hwnd)		{ m_hWnd = _hwnd;}	
	void SetHeight(int _h){m_iHeight=_h;}
	void SetWidTh(int _w) {m_iWidth = _w;}
public:
	WindowsMgr(void);
	virtual ~WindowsMgr(void);
private:
	HWND			m_hWnd;
	HWND			m_ViewhWnd;
	int				m_iWidth;
	int				m_iHeight;
};
