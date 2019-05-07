#include "DXCommon.h"
#include "WinCommon.h"

#include "QuadNode.h"

int QuadNode::m_iVertexCnt = 0;

QuadNode::QuadNode(void)
{
	for(int i=0; i<QT_MAX; i++)
		m_iCorner[i]	= -1;
	m_iLevel			= -1;			
	m_iMaxLevel			=0;		

	m_pParentNode		=NULL;
	for(int i=0; i<4; i++)
		m_pChildNodeList[i] = NULL;

	m_pTerrainVertex = NULL;

}

QuadNode::QuadNode( int _vertexCnt)
{	
	for(int i=0; i<QT_MAX; i++)
		m_iCorner[i]	= -1;
	m_iLevel			= -1;			
	m_iMaxLevel			=0;		

	m_pParentNode		=NULL;
	for(int i=0; i<4; i++)
		m_pChildNodeList[i] = NULL;

	m_pTerrainVertex = NULL;

	m_iCorner[QT_LT]		=0;
	m_iCorner[QT_RT]		=_vertexCnt -1;
	m_iCorner[QT_LB]		=_vertexCnt *(_vertexCnt-1);
	m_iCorner[QT_RB]		=_vertexCnt *_vertexCnt-1;
	m_iCorner[QT_CN]		=(m_iCorner[QT_LT] +m_iCorner[QT_RT]+m_iCorner[QT_LB] + m_iCorner[QT_RB])/4;

}
QuadNode::~QuadNode(void)
{
	Release();
}

void QuadNode::CreateNode( D3DFVF_XYZ_NORMAL_TEX1* _pTerrainVertex, int _corner[QT_MAX], int _MaxLev, int _currLev, QuadNode* pParent,int _vtxCnt )
{
	m_pTerrainVertex		=_pTerrainVertex;
	m_iLevel				=_currLev;
	m_iMaxLevel				=_MaxLev;
	m_pParentNode			=pParent;
	m_iVertexCnt			=_vtxCnt;

	m_iCorner[QT_LT]			=_corner[QT_LT];
	m_iCorner[QT_RT]			=_corner[QT_RT];
	m_iCorner[QT_LB]			=_corner[QT_LB];
	m_iCorner[QT_RB]			=_corner[QT_RB];
	m_iCorner[QT_CN]			=_corner[QT_CN];

}

void QuadNode::CreateChild( void )
{
	int idxSp = m_iCorner[QT_LT];
	int idxW  = (m_iCorner[QT_RT] - m_iCorner[QT_LT])/2;			//넓이

	int iCorner[QT_MAX] = {-1};
	int iChildIdx       = 0;

	for(int j = 0; j<2; j++)
	{
		for(int i=0; i<2; i++)
		{
			int startidx = idxSp + (( j * idxW ) * m_iVertexCnt) + idxW * i;

			iCorner[QT_LT] = startidx;
			iCorner[QT_RT] = iCorner[QT_LT] + idxW;
			iCorner[QT_LB] = startidx + idxW * m_iVertexCnt;
			iCorner[QT_RB] = iCorner[QT_LB] + idxW;
			iCorner[QT_CN] = (iCorner[QT_LT] +iCorner[QT_RT]+iCorner[QT_LB] + iCorner[QT_RB])/4;

			m_pChildNodeList[iChildIdx] = new QuadNode;
			m_pChildNodeList[iChildIdx]->CreateNode(m_pTerrainVertex,iCorner,m_iMaxLevel,m_iLevel+1,this,m_iVertexCnt);

			if(m_iLevel + 1 < m_iMaxLevel)
				m_pChildNodeList[iChildIdx]->CreateChild();

			iChildIdx++;
		}
	}

}

void QuadNode::Release()
{
	for(int i = 0; i<4; i++)
	{
		if(!m_pChildNodeList[i])
			continue;
		m_pChildNodeList[i]->Release();
		SAFE_DELETE(m_pChildNodeList[i]);
	}
}

bool QuadNode::isIn( D3DXVECTOR3 vPos ,QTINFO info, GetIndexFunc pFunc, float _size)
{

	m_fSize= _size;
	QuadNode*	pNode = NULL;
	
	D3DXVECTOR3 vQTCN = m_pTerrainVertex[m_iCorner[QT_CN]].vPos;			//높이를 빼야함.
	D3DXVECTOR3 vQTLT = m_pTerrainVertex[m_iCorner[QT_LT]].vPos;
	D3DXVECTOR3 vQTRB = m_pTerrainVertex[m_iCorner[QT_RB]].vPos;
	D3DXVECTOR3 vPlayerPos = vPos;

	vQTRB.y = vQTLT.y =vQTCN.y = vPlayerPos.y = 0.0f;
	
	float fDis = D3DXVec3Length(&(vPlayerPos-vQTCN));

	float fRadius = D3DXVec3Length(&(vQTLT-vQTRB))/2;

	if(fDis>(fRadius+m_fSize))
	{
		return false;
	}

	if(m_iLevel<m_iMaxLevel)
	{
		for (int i=0; i<4; i++)
		{
			if(m_pChildNodeList[i]==NULL)
				continue;
			m_pChildNodeList[i]->isIn(vPos,info,pFunc, _size);
		}
	}

	else
	{
		//현재노드를 쿼드 인덱스 버퍼에 넣어라
		// 함수포인트 

		pFunc(this,info);
	}
	return true;
}