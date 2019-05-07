#pragma once

enum {	QT_CN,QT_LT,QT_RT,QT_LB,QT_RB,QT_MAX};

struct QTINFO
{
	int							iPatchCnt;

	D3DINDEX*					pQTTerrainIB;
	D3DINDEX*					pTerrainIB;
	int*						piQTTotalFaceCnt;
};

class QuadNode;
typedef void (*GetIndexFunc)(QuadNode* pNode, QTINFO& pData);


class QuadNode
{
public:
	int						m_iCorner[QT_MAX];
	int						m_iLevel;				//쿼드노드 레벨
	int						m_iMaxLevel;			//최대 레벨

	static int  			m_iVertexCnt;

	QuadNode*				m_pParentNode;
	QuadNode*				m_pChildNodeList[4];

	D3DFVF_XYZ_NORMAL_TEX1*	m_pTerrainVertex;

	float					m_fSize;

public:

	void CreateNode(D3DFVF_XYZ_NORMAL_TEX1* _pTerrainVertex, int _coner[QT_MAX], int _MaxLev, int _currLev, QuadNode* pParent, int _vtxCnt);

	void CreateChild(void);
	bool isIn(D3DXVECTOR3 vPos, QTINFO info, GetIndexFunc pFunc, float _size);
	void Release();

	QuadNode(void);
	QuadNode(int _vertexCnt);
	~QuadNode(void);
};
