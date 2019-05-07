// FormMain.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "MapTool.h"
#include "FormMain.h"



// CFormMain

IMPLEMENT_DYNCREATE(CFormMain, CFormView)

CFormMain::CFormMain()
	: CFormView(CFormMain::IDD), m_pwndShow(NULL)
{

}

CFormMain::~CFormMain()
{
}

void CFormMain::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_TAB1, m_Tab);
}

BEGIN_MESSAGE_MAP(CFormMain, CFormView)
	ON_NOTIFY(TCN_SELCHANGE, IDC_TAB1, &CFormMain::OnTcnSelchangeTab1)
END_MESSAGE_MAP()


// CFormMain �����Դϴ�.

#ifdef _DEBUG
void CFormMain::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void CFormMain::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG


// CFormMain �޽��� ó�����Դϴ�.

void CFormMain::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();

	// TODO: ���⿡ Ư��ȭ�� �ڵ带 �߰� ��/�Ǵ� �⺻ Ŭ������ ȣ���մϴ�.
	CString    strOne = _T("First");
	CString    strTwo = _T("Second");
	//CString    strThree = _T("Third");
	m_Tab.InsertItem(1, strOne);
	m_Tab.InsertItem(2, strTwo);
	//m_Tab.InsertItem(3, strThree);


	CRect Rect;
	m_Tab.GetClientRect(&Rect);
	 
	m_first.Create(IDD_DIALOG1, &m_Tab);
	m_first.SetWindowPos(NULL, 5, 25,
		Rect.Width() - 12, Rect.Height() - 33,
		SWP_SHOWWINDOW | SWP_NOZORDER);
	m_pwndShow = &m_first;

	m_second.Create(IDD_DIALOG2, &m_Tab);
	m_second.SetWindowPos(NULL, 5, 25,
		Rect.Width() - 12, Rect.Height() - 33,
		SWP_NOZORDER);
	
}

void CFormMain::OnTcnSelchangeTab1(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	if(m_pwndShow != NULL)
		{
		 m_pwndShow->ShowWindow(SW_HIDE);
		 m_pwndShow = NULL;
		}
	
	int nIndex = m_Tab.GetCurSel();
	switch(nIndex)
	{
		case 0:
		 m_first.ShowWindow(SW_SHOW);
			m_pwndShow = &m_first;
			break;

		case 1:
			m_second.ShowWindow(SW_SHOW);
			m_pwndShow = &m_second;
			break;

			
	 }

	*pResult = 0;
}
