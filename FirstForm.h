#pragma once
#include "afxwin.h"


// CFirstForm 대화 상자입니다.

class CFirstForm : public CDialog
{
	DECLARE_DYNAMIC(CFirstForm)

public:
	CFirstForm(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CFirstForm();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_DIALOG1 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

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
