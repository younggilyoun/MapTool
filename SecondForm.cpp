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
	int _size = _ttoi(_str);

	GAMEMGR->g_Terrain->g_fQuadSize = _size;
}

void CSecondForm::OnBnClickedButton3()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	CMapToolApp *pApp = (CMapToolApp *) AfxGetApp();
	pApp->g_iTerrEditBtn =0;
}

void CSecondForm::OnBnClickedButton4()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	CMapToolApp *pApp = (CMapToolApp *) AfxGetApp();
	pApp->g_iTerrEditBtn =1;
}

void CSecondForm::OnBnClickedButton5()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	
	CMapToolApp *pApp = (CMapToolApp *) AfxGetApp();
	pApp->g_iTerrEditBtn =2;
}

void CSecondForm::OnBnClickedCheck1()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	CMapToolApp *pApp = (CMapToolApp *) AfxGetApp();
	pApp->g_bUpDown = false;

	BOOL _noCheck = IsDlgButtonChecked(IDC_CHECK2);
	if(_noCheck == true)
		CheckDlgButton(IDC_CHECK2,false);
}

void CSecondForm::OnBnClickedCheck2()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.

	CMapToolApp *pApp = (CMapToolApp *) AfxGetApp();
	pApp->g_bUpDown = true;

	BOOL _yesCheck = IsDlgButtonChecked(IDC_CHECK1);
	if(_yesCheck == true)
		CheckDlgButton(IDC_CHECK1,false);
}
