// MainFrm.cpp : CMainFrame 클래스의 구현
//

#include "stdafx.h"
#include "MapTool.h"
#include "DXCommon.h"
#include "WinCommon.h"
#include "MainFrm.h"
#include "MapToolDoc.h"
#include "MapToolView.h"
#include "FormMain.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMainFrame

IMPLEMENT_DYNCREATE(CMainFrame, CFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CFrameWnd)
	ON_WM_CREATE()
END_MESSAGE_MAP()

static UINT indicators[] =
{
	ID_SEPARATOR,           // 상태 줄 표시기
	ID_INDICATOR_CAPS,
	ID_INDICATOR_NUM,
	ID_INDICATOR_SCRL,
};


// CMainFrame 생성/소멸

CMainFrame::CMainFrame()
{
	// TODO: 여기에 멤버 초기화 코드를 추가합니다.
}

CMainFrame::~CMainFrame()
{
}


int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	if (!m_wndToolBar.CreateEx(this, TBSTYLE_FLAT, WS_CHILD | WS_VISIBLE | CBRS_TOP
		| CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC) ||
		!m_wndToolBar.LoadToolBar(IDR_MAINFRAME))
	{
		TRACE0("도구 모음을 만들지 못했습니다.\n");
		return -1;      // 만들지 못했습니다.
	}

	if (!m_wndStatusBar.Create(this) ||
		!m_wndStatusBar.SetIndicators(indicators,
		  sizeof(indicators)/sizeof(UINT)))
	{
		TRACE0("상태 표시줄을 만들지 못했습니다.\n");
		return -1;      // 만들지 못했습니다.
	}

	// TODO: 도구 모음을 도킹할 수 없게 하려면 이 세 줄을 삭제하십시오.
	m_wndToolBar.EnableDocking(CBRS_ALIGN_ANY);
	EnableDocking(CBRS_ALIGN_ANY);
	DockControlBar(&m_wndToolBar);

	return 0;
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if( !CFrameWnd::PreCreateWindow(cs) )
		return FALSE;
	// TODO: CREATESTRUCT cs를 수정하여 여기에서
	//  Window 클래스 또는 스타일을 수정합니다.

	return TRUE;
}


// CMainFrame 진단

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	CFrameWnd::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CFrameWnd::Dump(dc);
}

#endif //_DEBUG


// CMainFrame 메시지 처리기




BOOL CMainFrame::OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext)
{
	// TODO: Add your specialized code here and/or call the base class

	m_wndSplitter.CreateStatic(this, 1, 2);


	// 미리 정의해 놓은 class 를 분할된 영역에 생성함. 크기를 지정할 수 있다.
	// Main splitter 의 두번째 행과 첫번째 열에 해당하는 창.
	m_wndSplitter.CreateView(0, 0, RUNTIME_CLASS(CMapToolView), CSize(850, 0), pContext);

	// Sub splitter 의 첫번째 행과 첫번째 열에 해당하는 창.
	m_wndSplitter.CreateView(0, 1, RUNTIME_CLASS(CFormMain), CSize(0, 0), pContext);

	return true;
}