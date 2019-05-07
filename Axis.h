#pragma once

struct _AXISINFO 
{
	float	length;			// ����
	int		width;			// ����
	int		height;			// ����
};


class Axis
{
	LPDIRECT3DVERTEXBUFFER9		m_pVB;
	D3DFVF_XYZ_COLOR*			m_pVtxs;	
	D3DXVECTOR3					m_vTextPos[3]; 

	D3DXMATRIX					m_mTM;	

	_AXISINFO					m_AxisInfo;

public:
	void Init(_AXISINFO info);
	void Update(void);		
	void Render(DWORD width, DWORD heigh);
	void Release();
public:
	Axis(void);
	virtual ~Axis(void);
};
