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
