#pragma once

class Tree
{

public:
	void Init(void);
	void Update(float dTime);
	void Render(void);
	void Release(void);

	float MyLerp(float _sx, float _ey, float _time);
	void SetPos(D3DXVECTOR3 vPos) {	m_vPos = vPos;}

	D3DXMATRIX GetTM() {return m_mTM;}

public:
	Tree(void);
	virtual ~Tree(void);

private:
	LPDIRECT3DVERTEXBUFFER9		m_pVB;

	D3DXVECTOR3					m_vPos;
	D3DXVECTOR3					m_vRot;
	D3DXVECTOR3					m_vDir;
	D3DXVECTOR3					m_vOrgDir;
	D3DXMATRIX					m_mTM;
	D3DXMATRIX					m_mTrans;
	D3DXMATRIX					m_mRot;

	float						m_fSpeed;
	int							m_iFaceCnt;
};
