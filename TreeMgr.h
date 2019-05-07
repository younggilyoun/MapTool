#pragma once
#include "MySingleton.h"


class MeshBase;
class TreeMgr : public MySingleton<TreeMgr>
{
	typedef list<MeshBase*>				TLIST;
	typedef list<MeshBase*>::iterator	TLISTITOR;


	

	D3DMATERIAL9 m_Material;

public:
	list<MeshBase*>	m_listTrees;
	void CreateTree(D3DXVECTOR3 _vPos,char* _filename, int num);
	void Update(float dTime);
	void Render();
	void Release();

	TLIST* GetTreeList(void)	{return &m_listTrees;};
	


public:
	TreeMgr(void);
public:
	~TreeMgr(void);
};
