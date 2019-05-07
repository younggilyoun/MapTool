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

CFirstForm::CFirstForm(CWnd* pParent /*=NULL*/)
	: CDialog(CFirstForm::IDD, pParent)
{
	Loadmsg= "";
	_Loadmsg="";
	

}

CFirstForm::~CFirstForm()
{
}

void CFirstForm::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);

	DDX_Control(pDX, IDC_LIST2, g_ListBox);
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
	g_ListBox.InsertString(0,"Box");
	g_ListBox.InsertString(1,"Fish Box");
	g_ListBox.InsertString(2,"Gear Box");
	g_ListBox.InsertString(3,"Post");
	g_ListBox.InsertString(4,"Tree");
	g_ListBox.InsertString(5,"Tree Box");

	return TRUE;  // return TRUE unless you set the focus to a control
	// 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}


void CFirstForm::OnBnClickedLoadbtn()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다
	CFileDialog dlg(TRUE);
	if(dlg.DoModal()==IDOK){
		CMapToolApp *pApp = (CMapToolApp *) AfxGetApp();
		pApp->g_bLoad =true;

		Loadmsg = dlg.GetPathName();
		_Loadmsg = (char*)((LPCSTR)Loadmsg);

		GAMEMGR->Init(_Loadmsg);
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

		CString str;
		file.Write(Loadmsg,Loadmsg.GetLength());

		for( int j = 0; j < GAMEMGR->g_Terrain->m_iVertexCnt; j++ )
		{
			for( int i = 0; i < GAMEMGR->g_Terrain->m_iVertexCnt; i++ )
			{
				int iPos = j *  GAMEMGR->g_Terrain->m_iVertexCnt + i;
				float _x,_y,_z;

				_x = GAMEMGR->g_Terrain->m_pTerrainVB[iPos].vPos.x;
				_y = GAMEMGR->g_Terrain->m_pTerrainVB[iPos].vPos.y;
				_z = GAMEMGR->g_Terrain->m_pTerrainVB[iPos].vPos.z;

				str ="\r\n";
				file.Write(str,str.GetLength());

				str.Format(_T("%5f "), _x);
				file.Write(str,str.GetLength());
				str.Format(_T("%5f "), _y);
				file.Write(str,str.GetLength());
				str.Format(_T("%5f "), _z);
				file.Write(str,str.GetLength());
			}
		}


		str ="\r\n";
		file.Write(str,str.GetLength());

		str.Format(_T("%5d "), TREEMGR->m_listTrees.size());
		file.Write(str,str.GetLength());

		list<MeshBase*>::iterator itor;
		for(itor=TREEMGR->m_listTrees.begin(); itor!=TREEMGR->m_listTrees.end(); ++itor)
		{
			MeshBase* pTree = (*itor);

			float _x,_y,_z;

			_x = pTree->m_vPos.x;
			_y = pTree->m_vPos.y;
			_z = pTree->m_vPos.z;

			CString str;
			str ="\r\n";
			file.Write(str,str.GetLength());

			str.Format(_T("%5d "), pTree->m_iNum);
			file.Write(str,str.GetLength());

			str.Format(_T("%5f "), _x);
			file.Write(str,str.GetLength());

			str.Format(_T("%5f "), _y);
			file.Write(str,str.GetLength());

			str.Format(_T("%5f "), _z);
			file.Write(str,str.GetLength());

		}
		file.Close();

	}
}


void CFirstForm::OnBnClickedTxtload()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CMapToolApp *pApp = (CMapToolApp *) AfxGetApp();
	pApp->g_bLoad =true;

	CFileDialog dlg(TRUE);
	if(dlg.DoModal()==IDOK){
		CString msg = dlg.GetPathName();
		FILE *p = NULL;
		p = fopen(msg,"r");
		CString str;
		fscanf(p,"%s",_Loadmsg);

		GAMEMGR->Init(_Loadmsg);


		//좌표부르기

		for( int j = 0; j < GAMEMGR->g_Terrain->m_iVertexCnt; j++ )
		{
			for( int i = 0; i < GAMEMGR->g_Terrain->m_iVertexCnt; i++ )
			{
				int iPos = j *  GAMEMGR->g_Terrain->m_iVertexCnt + i;
				float _x,_y,_z;
				CString _strx,_stry,_strz;
				fscanf(p," %s",_strx);
				_x = _ttoi(_strx);
				GAMEMGR->g_Terrain->m_pTerrainVB[iPos].vPos.x =_x;
				fscanf(p," %s",_stry);
				_y = _ttoi(_stry);
				GAMEMGR->g_Terrain->m_pTerrainVB[iPos].vPos.y =_y;
				fscanf(p," %s",_strz);
				_z = _ttoi(_strz);
				GAMEMGR->g_Terrain->m_pTerrainVB[iPos].vPos.z =_z;				
			}
		}
		GAMEMGR->g_Terrain->LockVB();

		CString _strSize,_strNum,_strx,_stry,_strz;

		// 오브젝트수
		int _size;
		// 오브젝트번호
		int _num;
		// 오브젝트 포지션
		float _x,_y,_z;

		fscanf(p," %s",_strNum);
		_size = _ttoi(_strx);

		for(int i=0; i<_size;i++){
			fscanf(p," %s",_strNum);
			_num = _ttoi(_strx);

			fscanf(p," %s",_strx);
			_x = _ttoi(_strx);

			fscanf(p," %s",_stry);
			_y = _ttoi(_stry);

			fscanf(p," %s",_strz);
			_z = _ttoi(_strz);		

			LoadTexture(_num,_x,_y,_z);
		}		
	}
}

void CFirstForm::LoadTexture( int _num,float _x,float _y,float _z )
{
	D3DXVECTOR3 temp;
	temp = D3DXVECTOR3(_x,_y,_z);
	switch (_num)
	{
	case 0:
		TREEMGR->CreateTree(temp,"obj/Boxes/Boxes.X",_num);  
		break;

	case 1:
		TREEMGR->CreateTree(temp,"obj/Fishing Box/Fishing.X",_num);
		break;

	case 2:
		TREEMGR->CreateTree(temp,"obj/Gear Box/GearBox.X",_num);
		break;

	case 3:
		TREEMGR->CreateTree(temp,"obj/Post/Post.X",_num);
		break;

	case 4:
		TREEMGR->CreateTree(temp,"obj/Tree/Tree.X",_num);
		break;

	case 5:
		TREEMGR->CreateTree(temp,"obj/Tree Box/TreeBox.X",_num);
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
	int _size = _ttoi(_str);

	GAMEMGR->g_Terrain->Init(_size,_Loadmsg);
}

void CFirstForm::OnBnClickedObjbtn2()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CMapToolApp *pApp = (CMapToolApp *) AfxGetApp();
	pApp->g_iObjBtn =g_ListBox.GetCaretIndex();
}
