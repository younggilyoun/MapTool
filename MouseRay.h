#pragma once

class MouseRay
{
public:
	void RayCreate(int _x, int _y);
	void RayTransform(D3DXMATRIX* mInv);
	void SetPos(D3DXVECTOR3 vPos) { m_vPos = vPos; }

	D3DXVECTOR3 GetPos() { return m_vPos; }
	D3DXVECTOR3 GetDir() { return m_vDir; }
public:
	MouseRay(void);
public:
	virtual ~MouseRay(void);

private:

	D3DXVECTOR3		m_vPos;
	D3DXVECTOR3		m_vDir;
};
