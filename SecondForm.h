#pragma once
#include "afxwin.h"


// CSecondForm ��ȭ �����Դϴ�.

class CSecondForm : public CDialog
{
	DECLARE_DYNAMIC(CSecondForm)

public:
	CSecondForm(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CSecondForm();

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_DIALOG2 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
public:
	
public:
	virtual BOOL OnInitDialog();

public:
	afx_msg void OnBnClickedEditsizebtn();
public:
	afx_msg void OnBnClickedButton3();
public:
	afx_msg void OnBnClickedButton4();
public:
	afx_msg void OnBnClickedButton5();
public:
	afx_msg void OnBnClickedCheck1();
public:
	afx_msg void OnBnClickedCheck2();
};
