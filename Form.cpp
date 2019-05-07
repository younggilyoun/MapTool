// Form.cpp : implementation file
//

#include "stdafx.h"
#include "MapTool.h"


#include "DXCommon.h"
#include "WinCommon.h"
#include "QuadNode.h"
#include "Terrain.h"
#include "MeshBase.h"

#include "Form.h"


// Form

IMPLEMENT_DYNCREATE(Form, CFormView)
Form::Form(): CFormView(Form::IDD)
,m_bObjBtn(false)
{

}

Form::~Form()
{
}

void Form::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_ListObj);
}

BEGIN_MESSAGE_MAP(Form, CFormView)
	ON_BN_CLICKED(IDC_SAVEBTN, &Form::OnBnClickedSavebtn)
	ON_BN_CLICKED(LOADBTN, &Form::OnBnClickedLoadbtn)
	ON_BN_CLICKED(TXTLOAD, &Form::OnBnClickedTxtload)
	ON_BN_CLICKED(IDC_OBJBTN, &Form::OnBnClickedObjbtn)
	ON_LBN_SELCHANGE(IDC_LIST1, &Form::OnLbnSelchangeList1)
	ON_BN_CLICKED(IDC_BUTTON3, &Form::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON4, &Form::OnBnClickedButton4)
	ON_BN_CLICKED(IDC_BUTTON5, &Form::OnBnClickedButton5)
END_MESSAGE_MAP()


// Form diagnostics

#ifdef _DEBUG
void Form::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void Form::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG


// Form message handlers

void Form::OnBnClickedSavebtn()
{
	// TODO: Add your control notification handler code here
	
}

void Form::OnBnClickedLoadbtn()
{
	// TODO: Add your control notification handler code here

	
}

void Form::OnBnClickedTxtload()
{
	// TODO: Add your control notification handler code here

	
}

void Form::OnBnClickedObjbtn()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
		
	CMapToolApp *pApp = (CMapToolApp *) AfxGetApp();
	pApp->SetObjBtn(m_ListObj.GetCaretIndex());
}

void Form::OnLbnSelchangeList1()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	
	
}

void Form::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();

	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
	
}

//void Form::LoadTexture(int _num,float _x,float _y,float _z)
//{
//	
//}
void Form::OnBnClickedButton3()
{
	// TODO: Add your control notification handler code here

	CMapToolApp *pApp = (CMapToolApp *) AfxGetApp();
	pApp->SetTerrEditBtn(0);

}

void Form::OnBnClickedButton4()
{
	// TODO: Add your control notification handler code here
	CMapToolApp *pApp = (CMapToolApp *) AfxGetApp();
	pApp->SetTerrEditBtn(1);
}

void Form::OnBnClickedButton5()
{
	// TODO: Add your control notification handler code here
	CMapToolApp *pApp = (CMapToolApp *) AfxGetApp();
	pApp->SetTerrEditBtn(2);
}
