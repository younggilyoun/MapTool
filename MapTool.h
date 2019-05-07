// MapTool.h : MapTool ���� ���α׷��� ���� �� ��� ����
//
#pragma once

#ifndef __AFXWIN_H__
	#error "PCH�� ���� �� ������ �����ϱ� ���� 'stdafx.h'�� �����մϴ�."
#endif

#include "resource.h"       // �� ��ȣ�Դϴ�.


// CMapToolApp:
// �� Ŭ������ ������ ���ؼ��� MapTool.cpp�� �����Ͻʽÿ�.
//

class CMapToolApp : public CWinApp
{
public:
	CMapToolApp();

	void setLoad(bool bLoad) { m_bLoad = bLoad; }
	void setUpDown(bool bUpDown) { m_bUpDown = bUpDown; }
	void SetTerrEditBtn(int nTerrEditBtn) { m_iTerrEditBtn = nTerrEditBtn; }
	void SetObjBtn(int nObjBtn) { m_iObjBtn = nObjBtn; }

private:
	bool m_bLoad;
	bool m_bUpDown;
	
	int m_iObjBtn;
	int m_iTerrEditBtn;


// �������Դϴ�.
public:
	virtual BOOL InitInstance();

// �����Դϴ�.
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
	virtual BOOL OnIdle(LONG lCount);
};

extern CMapToolApp theApp;