#pragma once
#include "afxwin.h"



// Form form view

class Form : public CFormView
{
	DECLARE_DYNCREATE(Form)

protected:
	Form();           // protected constructor used by dynamic creation
	virtual ~Form();

public:
	CString Loadmsg;
	bool	m_bObjBtn;
	enum { IDD = IDD_FORM };
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedSavebtn();
	afx_msg void OnBnClickedLoadbtn();
	afx_msg void OnBnClickedTxtload();

	void	LoadTexture(int _num,float _x,float _y,float _z);
public:
	afx_msg void OnBnClickedObjbtn();
public:
	afx_msg void OnLbnSelchangeList1();
public:
	CListBox g_ListObj;
public:
	virtual void OnInitialUpdate();
	afx_msg void OnBnClickedButton3();
	afx_msg void OnBnClickedButton4();
	afx_msg void OnBnClickedButton5();
};


