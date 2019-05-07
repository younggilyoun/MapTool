#pragma once

class QuadNode;
class QuadTree
{

public:
	int				m_iMaxLevel;
	QuadNode*		m_pTop;

	int				m_iVertexCnt;

	void QuadCreate(D3DFVF_XYZ_NORMAL_TEX1* _pTerrainVertex, int _level, int _vtxCnt);

	bool FindQuadNode(D3DXVECTOR3 _vPos, QTINFO info, GetIndexFunc pFunc,float _size);

	void Release();


public:
	QuadTree(void);
public:
	~QuadTree(void);
};
