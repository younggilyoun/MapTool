#pragma once
#include "afxwin.h"


// CSecondForm 대화 상자입니다.

class CSecondForm : public CDialog
{
	DECLARE_DYNAMIC(CSecondForm)

public:
	CSecondForm(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CSecondForm();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_DIALOG2 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

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
