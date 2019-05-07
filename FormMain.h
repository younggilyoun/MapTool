#pragma once
#include "afxcmn.h"
#include "FirstForm.h"
#include "SecondForm.h"


// CFormMain �� ���Դϴ�.
class CFormMain : public CFormView
{
	DECLARE_DYNCREATE(CFormMain)

protected:
	CFormMain();           // ���� ����⿡ ���Ǵ� protected �������Դϴ�.
	virtual ~CFormMain();

public:
	enum { IDD = IDD_FORMMAIN };
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
public:
	CFirstForm	m_first;
	CSecondForm	m_second;
	CTabCtrl	m_Tab;
	CWnd*       m_pwndShow;
public:
	virtual void OnInitialUpdate();
public:
	afx_msg void OnTcnSelchangeTab1(NMHDR *pNMHDR, LRESULT *pResult);
};


