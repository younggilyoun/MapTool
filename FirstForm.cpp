// FirstForm.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "MapTool.h"
#include "DXCommon.h"
#include "WinCommon.h"
#include "QuadNode.h"
#include "Terrain.h"
#include "MeshBase.h"
#include "FirstForm.h"


// CFirstForm 대화 상자입니다.

IMPLEMENT_DYNAMIC(CFirstForm, CDialog)

CFirstForm::CFirstForm(CWnd* pParent /*=NULL*/) : CDialog(CFirstForm::IDD, pParent) 
{		

}

CFirstForm::~CFirstForm()
{
}

void CFirstForm::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);

	DDX_Control(pDX, IDC_LIST2, m_ListBox);
}


BEGIN_MESSAGE_MAP(CFirstForm, CDialog)
	ON_BN_CLICKED(LOADBTN, &CFirstForm::OnBnClickedLoadbtn)
	ON_BN_CLICKED(IDC_SAVEBTN, &CFirstForm::OnBnClickedSavebtn)
	ON_BN_CLICKED(TXTLOAD, &CFirstForm::OnBnClickedTxtload)
	ON_BN_CLICKED(TERRSIZEBTN, &CFirstForm::OnBnClickedTerrsizebtn)
	ON_BN_CLICKED(IDC_OBJBTN2, &CFirstForm::OnBnClickedObjbtn2)
END_MESSAGE_MAP()


// CFirstForm 메시지 처리기입니다.
BOOL CFirstForm::OnInitDialog()
{
	CDialog::OnInitDialog();

	SetDlgItemText(TERRSIZEEDIT,"128");
	m_ListBox.InsertString(0,"Box");
	m_ListBox.InsertString(1,"Fish Box");
	m_ListBox.InsertString(2,"Gear Box");
	m_ListBox.InsertString(3,"Post");
	m_ListBox.InsertString(4,"Tree");
	m_ListBox.InsertString(5,"Tree Box");

	return TRUE;  // return TRUE unless you set the focus to a control
	// 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}


void CFirstForm::OnBnClickedLoadbtn()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다
	CFileDialog dlg(TRUE);
	if(dlg.DoModal()==IDOK){
		CMapToolApp *pApp = (CMapToolApp *) AfxGetApp();
		pApp->setLoad(true);

		m_strLoadmsg = dlg.GetPathName();

		GAMEMGR->Init((char*)((LPCSTR)m_strLoadmsg));
	}
}

void CFirstForm::OnBnClickedSavebtn()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CFileDialog dlg(false);
	if(dlg.DoModal()==IDOK){
		CString msg = dlg.GetPathName();
		CFile file;
		file.Open(msg,CFile::modeCreate | CFile::modeWrite);

		CString strValue;
		file.Write(m_strLoadmsg, m_strLoadmsg.GetLength());

		for( int j = 0; j < GAMEMGR->GetTerrain()->m_iVertexCnt; j++ )
		{
			for( int i = 0; i < GAMEMGR->GetTerrain()->m_iVertexCnt; i++ )
			{
				int iPos = j *  GAMEMGR->GetTerrain()->m_iVertexCnt + i;
				float fx,fy, fz;

				fx = GAMEMGR->GetTerrain()->m_pTerrainVB[iPos].vPos.x;
				fy = GAMEMGR->GetTerrain()->m_pTerrainVB[iPos].vPos.y;
				fz = GAMEMGR->GetTerrain()->m_pTerrainVB[iPos].vPos.z;

				strValue ="\r\n";
				file.Write(strValue, strValue.GetLength());

				strValue.Format(_T("%5f "), fx);
				file.Write(strValue, strValue.GetLength());
				strValue.Format(_T("%5f "), fy);
				file.Write(strValue, strValue.GetLength());
				strValue.Format(_T("%5f "), fz);
				file.Write(strValue, strValue.GetLength());
			}
		}


		strValue ="\r\n";
		file.Write(strValue, strValue.GetLength());

		strValue.Format(_T("%5d "), TREEMGR->m_listTrees.size());
		file.Write(strValue, strValue.GetLength());

		for(auto iter=TREEMGR->m_listTrees.begin(); iter !=TREEMGR->m_listTrees.end(); ++iter)
		{
			MeshBase* pTree = (*iter);

			float _fx,_fy,_fz;

			_fx = pTree->GetPos().x;
			_fy = pTree->GetPos().y;
			_fz = pTree->GetPos().z;

			CString strValue;
			strValue ="\r\n";
			file.Write(strValue, strValue.GetLength());

			strValue.Format(_T("%5d "), pTree->GetNum());
			file.Write(strValue, strValue.GetLength());

			strValue.Format(_T("%5f "), _fx);
			file.Write(strValue, strValue.GetLength());

			strValue.Format(_T("%5f "), _fy);
			file.Write(strValue, strValue.GetLength());

			strValue.Format(_T("%5f "), _fz);
			file.Write(strValue, strValue.GetLength());

		}
		file.Close();

	}
}


void CFirstForm::OnBnClickedTxtload()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CMapToolApp *pApp = (CMapToolApp *) AfxGetApp();
	pApp->setLoad(true);

	CFileDialog dlg(TRUE);
	if(dlg.DoModal()==IDOK){
		CString msg = dlg.GetPathName();
		FILE *p = NULL;
		p = fopen(msg,"r");
		fscanf(p,"%s", (char*)((LPCSTR)m_strLoadmsg));

		GAMEMGR->Init((char*)((LPCSTR)m_strLoadmsg));


		//좌표부르기

		for( int j = 0; j < GAMEMGR->GetTerrain()->m_iVertexCnt; j++ )
		{
			for( int i = 0; i < GAMEMGR->GetTerrain()->m_iVertexCnt; i++ )
			{
				int iPos = j *  GAMEMGR->GetTerrain()->m_iVertexCnt + i;
				float _fx,_fy,_fz;
				CString _strx,_stry,_strz;
				fscanf(p," %s",_strx);
				_fx = _ttoi(_strx);
				GAMEMGR->GetTerrain()->m_pTerrainVB[iPos].vPos.x = _fx;
				fscanf(p," %s",_stry);
				_fy = _ttoi(_stry);
				GAMEMGR->GetTerrain()->m_pTerrainVB[iPos].vPos.y = _fy;
				fscanf(p," %s",_strz);
				_fz = _ttoi(_strz);
				GAMEMGR->GetTerrain()->m_pTerrainVB[iPos].vPos.z = _fz;
			}
		}
		GAMEMGR->GetTerrain()->LockVB();

		CString _strSize,_strNum,_strx,_stry,_strz;

		// 오브젝트수
		int nSize  = 0;
		// 오브젝트번호
		int nNum = 0;
		// 오브젝트 포지션
		float _fx =0.0,_fy = 0.0,_fz = 0.0;

		fscanf(p," %s",_strNum);
		nSize = _ttoi(_strx);

		for(int i=0; i< nSize;i++){
			fscanf(p," %s",_strNum);
			nNum = _ttoi(_strx);

			fscanf(p," %s",_strx);
			_fx = _ttoi(_strx);

			fscanf(p," %s",_stry);
			_fy = _ttoi(_stry);

			fscanf(p," %s",_strz);
			_fz = _ttoi(_strz);		

			LoadTexture(nNum,_fx,_fy,_fz);
		}		
	}
}

void CFirstForm::LoadTexture( int nNum,float fx,float fy,float fz )
{
	D3DXVECTOR3 temp;
	temp = D3DXVECTOR3(fx, fy, fz);
	switch (nNum)
	{
	case 0:
		TREEMGR->CreateTree(temp,"obj/Boxes/Boxes.X", nNum);
		break;

	case 1:
		TREEMGR->CreateTree(temp,"obj/Fishing Box/Fishing.X", nNum);
		break;

	case 2:
		TREEMGR->CreateTree(temp,"obj/Gear Box/GearBox.X", nNum);
		break;

	case 3:
		TREEMGR->CreateTree(temp,"obj/Post/Post.X", nNum);
		break;

	case 4:
		TREEMGR->CreateTree(temp,"obj/Tree/Tree.X", nNum);
		break;

	case 5:
		TREEMGR->CreateTree(temp,"obj/Tree Box/TreeBox.X", nNum);
		break;

	default:
		break;
	}
}
void CFirstForm::OnBnClickedTerrsizebtn()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CString _str;
	GetDlgItemText(TERRSIZEEDIT,_str);

	CMapToolApp *pApp = (CMapToolApp *) AfxGetApp();
	int nSize = _ttoi(_str);

	GAMEMGR->GetTerrain()->Init(nSize, (char*)((LPCSTR)m_strLoadmsg));
}

void CFirstForm::OnBnClickedObjbtn2()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CMapToolApp *pApp = (CMapToolApp *) AfxGetApp();
	pApp->SetObjBtn(m_ListBox.GetCaretIndex());
}
