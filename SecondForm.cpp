// SecondForm.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "MapTool.h"

#include "DXCommon.h"
#include "WinCommon.h"
#include "QuadNode.h"
#include "Terrain.h"
#include "SecondForm.h"


// CSecondForm 대화 상자입니다.

IMPLEMENT_DYNAMIC(CSecondForm, CDialog)

CSecondForm::CSecondForm(CWnd* pParent /*=NULL*/)
	: CDialog(CSecondForm::IDD, pParent)
{

}

CSecondForm::~CSecondForm()
{
}

void CSecondForm::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CSecondForm, CDialog)
	ON_BN_CLICKED(EDITSIZEBTN, &CSecondForm::OnBnClickedEditsizebtn)
	ON_BN_CLICKED(IDC_BUTTON3, &CSecondForm::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON4, &CSecondForm::OnBnClickedButton4)
	ON_BN_CLICKED(IDC_BUTTON5, &CSecondForm::OnBnClickedButton5)
	ON_BN_CLICKED(IDC_CHECK1, &CSecondForm::OnBnClickedCheck1)
	ON_BN_CLICKED(IDC_CHECK2, &CSecondForm::OnBnClickedCheck2)
END_MESSAGE_MAP()


// CSecondForm 메시지 처리기입니다.

BOOL CSecondForm::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  여기에 추가 초기화 작업을 추가합니다.
	SetDlgItemText(EDITSIZEEDIT,"10");

	return TRUE;  // return TRUE unless you set the focus to a control
	// 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}
void CSecondForm::OnBnClickedEditsizebtn()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CString _str;
	GetDlgItemText(TERRSIZEEDIT,_str);

	CMapToolApp *pApp = (CMapToolApp *) AfxGetApp();
	float _fsize = _ttof(_str);

	GAMEMGR->GetTerrain()->SetQuadSize(_fsize);
}

void CSecondForm::OnBnClickedButton3()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CMapToolApp *pApp = (CMapToolApp *) AfxGetApp();
	pApp->SetTerrEditBtn(0);
}

void CSecondForm::OnBnClickedButton4()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CMapToolApp *pApp = (CMapToolApp *) AfxGetApp();
	pApp->SetTerrEditBtn(1);
}

void CSecondForm::OnBnClickedButton5()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	
	CMapToolApp *pApp = (CMapToolApp *) AfxGetApp();
	pApp->SetTerrEditBtn(2);
}

void CSecondForm::OnBnClickedCheck1()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CMapToolApp *pApp = (CMapToolApp *) AfxGetApp();
	pApp->SetObjBtn(false);

	BOOL _bCheck = IsDlgButtonChecked(IDC_CHECK2);
	if(_bCheck == true)
		CheckDlgButton(IDC_CHECK2,false);
}

void CSecondForm::OnBnClickedCheck2()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.

	CMapToolApp *pApp = (CMapToolApp *) AfxGetApp();
	pApp->SetObjBtn(true);

	BOOL _bCheck = IsDlgButtonChecked(IDC_CHECK1);
	if(_bCheck == true)
		CheckDlgButton(IDC_CHECK1,false);
}
