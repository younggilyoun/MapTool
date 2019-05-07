#pragma once

class BoneSphere;
class TreeSphere;
class MeshBase
{

	
	LPD3DXMESH			m_pMesh;
	DWORD				m_dMtricnt;
	D3DMATERIAL9*		m_pMaterials;

	LPDIRECT3DTEXTURE9* m_pTexture;

	
	D3DXVECTOR3* m_vTempPos;
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

public:
	D3DXVECTOR3  m_vPos;
	int					m_iNum;	
	//TreeSphere*			m_pSphere;
	void init(char * name);
	void Update(float dTime);
	void Render(void);
	void Release(void);


	D3DXVECTOR3 GetPos(void) {
		return m_vPos;
	}
	D3DXVECTOR3 GetDir(void) {return m_vDir;}
	D3DXMATRIX	GetTM(void){return m_mTM;}
	void SetDir(D3DXVECTOR3 _vRot);
	void SetPos(D3DXVECTOR3 _vPos){m_vPos = _vPos;}
	void SetTempPos(D3DXVECTOR3* _vPos){m_vTempPos= _vPos;}
	void SetRot(D3DXVECTOR3 _vRot){m_vRot = _vRot;}
	void SetTM(D3DXMATRIX _TM){m_mParentTM = _TM;}
public:
	MeshBase(void);
public:
	~MeshBase(void);
};
