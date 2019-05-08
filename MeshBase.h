#pragma once

class BoneSphere;
class TreeSphere;
class MeshBase
{
	
public:
	//TreeSphere*			m_pSphere;
	void init(char * name);
	void Update(float dTime);
	void Render(void);
	void Release(void);


	D3DXVECTOR3 GetPos(void) {	return m_vPos;	}
	D3DXMATRIX	GetTM(void){return m_mTM;}
	int  GetNum() { return m_iNum; }
	void SetPos(D3DXVECTOR3 _vPos){m_vPos = _vPos;}
	void SetTempPos(D3DXVECTOR3* _vPos){m_pvTempPos= _vPos;}
	void SetRot(D3DXVECTOR3 _vRot){m_vRot = _vRot;}
	void SetTM(D3DXMATRIX _TM){m_mParentTM = _TM;}
	void SetNum(int iNum) { m_iNum = iNum; }
public:
	MeshBase(void);
	virtual ~MeshBase(void);

private:
	
	int					m_iNum;

	LPD3DXMESH			m_pMesh;
	DWORD				m_dMtricnt;
	D3DMATERIAL9*		m_pMaterials;

	LPDIRECT3DTEXTURE9* m_pTexture;

	D3DXVECTOR3	 m_vPos;
	D3DXVECTOR3* m_pvTempPos;
	D3DXVECTOR3  m_vRot;
	D3DXVECTOR3  m_vScale;
	D3DXVECTOR3	 m_vDir;
	D3DXVECTOR3	 m_vOrgDir;

	D3DXMATRIX	m_mTM;
	D3DXMATRIX  m_mTempTrans;
	D3DXMATRIX	m_mTrans;
	D3DXMATRIX	m_mRot;
	D3DXMATRIX	m_mScale;
	D3DXMATRIX	m_mParentTM;

	int m_iFaceCnt;
	float	m_fSpeed;

	float m_fAlpha;

};
