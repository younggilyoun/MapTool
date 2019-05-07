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
	virtual BOOL OnInitDialog();
	DECLARE_MESSAGE_MAP()

	afx_msg void OnBnClickedLoadbtn();		
	afx_msg void OnBnClickedSavebtn();	
	afx_msg void OnBnClickedTxtload();
	afx_msg void OnBnClickedTerrsizebtn();
	afx_msg void OnBnClickedObjbtn2();

private:
	CString m_strLoadmsg;
	CListBox m_ListBox;
	void	LoadTexture(int _num, float _x, float _y, float _z);
	
};
