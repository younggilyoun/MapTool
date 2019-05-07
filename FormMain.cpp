// FormMain.cpp : 구현 파일입니다.
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


// CFormMain 진단입니다.

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


// CFormMain 메시지 처리기입니다.

void CFormMain::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();

	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
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
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
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
