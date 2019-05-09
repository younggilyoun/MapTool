// SecondForm.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "MapTool.h"

#include "DXCommon.h"
#include "WinCommon.h"
#include "QuadNode.h"
#include "Terrain.h"
#include "SecondForm.h"


// CSecondForm ��ȭ �����Դϴ�.

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


// CSecondForm �޽��� ó�����Դϴ�.

BOOL CSecondForm::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  ���⿡ �߰� �ʱ�ȭ �۾��� �߰��մϴ�.
	SetDlgItemText(EDITSIZEEDIT,"10");

	return TRUE;  // return TRUE unless you set the focus to a control
	// ����: OCX �Ӽ� �������� FALSE�� ��ȯ�ؾ� �մϴ�.
}
void CSecondForm::OnBnClickedEditsizebtn()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	CString _str;
	GetDlgItemText(TERRSIZEEDIT,_str);

	CMapToolApp *pApp = (CMapToolApp *) AfxGetApp();
	float _fsize = _ttof(_str);

	GAMEMGR->GetTerrain()->SetQuadSize(_fsize);
}

void CSecondForm::OnBnClickedButton3()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	CMapToolApp *pApp = (CMapToolApp *) AfxGetApp();
	pApp->SetTerrEditBtn(0);
}

void CSecondForm::OnBnClickedButton4()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	CMapToolApp *pApp = (CMapToolApp *) AfxGetApp();
	pApp->SetTerrEditBtn(1);
}

void CSecondForm::OnBnClickedButton5()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	
	CMapToolApp *pApp = (CMapToolApp *) AfxGetApp();
	pApp->SetTerrEditBtn(2);
}

void CSecondForm::OnBnClickedCheck1()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	CMapToolApp *pApp = (CMapToolApp *) AfxGetApp();
	pApp->SetObjBtn(false);

	BOOL _bCheck = IsDlgButtonChecked(IDC_CHECK2);
	if(_bCheck == true)
		CheckDlgButton(IDC_CHECK2,false);
}

void CSecondForm::OnBnClickedCheck2()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.

	CMapToolApp *pApp = (CMapToolApp *) AfxGetApp();
	pApp->SetObjBtn(true);

	BOOL _bCheck = IsDlgButtonChecked(IDC_CHECK1);
	if(_bCheck == true)
		CheckDlgButton(IDC_CHECK1,false);
}
