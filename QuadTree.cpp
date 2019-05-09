#include "DXCommon.h"
#include "WinCommon.h"
#include "QuadNode.h"
#include "QuadTree.h"

QuadTree::QuadTree(void)
{
}

QuadTree::~QuadTree(void)
{
	Release();
}

void QuadTree::QuadCreate( D3DFVF_XYZ_NORMAL_TEX1* _pTerrainVertex, int _level, int _vtxCnt )
{
	m_iMaxLevel = _level;
	m_iVertexCnt = _vtxCnt;

	m_pTop = new QuadNode(m_iVertexCnt);

	m_pTop->CreateNode(_pTerrainVertex,m_pTop->GetCorner(),m_iMaxLevel,0,NULL,m_iVertexCnt);
	m_pTop->CreateChild();
}

bool QuadTree::FindQuadNode(D3DXVECTOR3 _vPos, QTINFO info, GetIndexFunc pFunc, float _size)
{
	return m_pTop->isIn(_vPos,info,pFunc,_size);	
}

void QuadTree::Release()
{
	m_pTop->Release();
	SAFE_DELETE(m_pTop);
}