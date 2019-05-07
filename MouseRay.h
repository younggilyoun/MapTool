#pragma once

class MouseRay
{
public:

D3DXVECTOR3		m_vPos;
D3DXVECTOR3		m_vDir;

public:
	void RayCreate(int _x, int _y);
	void RayTransform(D3DXMATRIX* mInv);
public:
	MouseRay(void);
public:
	virtual ~MouseRay(void);
};
