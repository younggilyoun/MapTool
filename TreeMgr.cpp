#include "DXCommon.h"
#include "WinCommon.h"
#include "MeshBase.h"
#include "QuadNode.h"
#include "Terrain.h"
#include "TreeMgr.h"


TreeMgr::TreeMgr(void)
{
}

TreeMgr::~TreeMgr(void)
{
	Release();
}

void TreeMgr::CreateTree( D3DXVECTOR3 _vPos ,char* _filename, int _num)
{
	MeshBase* pTree = new MeshBase;
	pTree->init(_filename);
	pTree->SetNum(_num);
	pTree->SetPos(D3DXVECTOR3(_vPos));
	m_listTrees.push_back(pTree);
}       
void TreeMgr::Update( float dTime )
{
	for(TLISTITOR itor=m_listTrees.begin(); itor!=m_listTrees.end(); ++itor)
	{
		MeshBase* pTree = (*itor);
		
		//D3DXVECTOR3 temp33;
		//temp33 = pTree->m_pSphere->GetPos();
		//temp33.y = 0;		
		//pTree->SetTempPos(&(temp33));
		pTree->Update(dTime);
	}
}

void TreeMgr::Render()
{
	for(TLISTITOR itor=m_listTrees.begin(); itor!=m_listTrees.end(); ++itor)
	{
		MeshBase* pTree = (*itor);
		pTree->Render();
	}
}

void TreeMgr::Release()
{
	for(TLISTITOR itor=m_listTrees.begin(); itor!=m_listTrees.end(); ++itor)
	{
		MeshBase* pTree = (*itor);
		SAFE_DELETE(pTree);
	}
	m_listTrees.clear();
}