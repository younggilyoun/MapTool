#pragma once
#include "afxwin.h"


// CFirstForm ��ȭ �����Դϴ�.

class CFirstForm : public CDialog
{
	DECLARE_DYNAMIC(CFirstForm)

public:
	CFirstForm(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CFirstForm();

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_DIALOG1 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedLoadbtn();
public:
	char*	_Loadmsg;
	CString Loadmsg;
	void	LoadTexture(int _num,float _x,float _y,float _z);
public:
	afx_msg void OnBnClickedSavebtn();
public:
	virtual BOOL OnInitDialog();
public:
	afx_msg void OnBnClickedTxtload();

public:
	afx_msg void OnBnClickedTerrsizebtn();
public:
	afx_msg void OnBnClickedObjbtn2();
public:
	CListBox g_ListBox;
};
