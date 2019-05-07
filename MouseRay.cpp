#include "DXCommon.h"
#include "WinCommon.h"

#include "MouseRay.h"

MouseRay::MouseRay(void)
{
	m_vPos=D3DXVECTOR3(0,0,0);
	m_vDir=D3DXVECTOR3(0,0,0);
}

MouseRay::~MouseRay(void)
{
}

void MouseRay::RayCreate( int _x, int _y )
{
	D3DVIEWPORT9		viewport;
	D3DXMATRIX			mProj;

	DEVICE->GetViewport(&viewport);
	DEVICE->GetTransform(D3DTS_PROJECTION,&mProj);

	m_vPos.x = _x;
	m_vPos.y = _y;
	m_vPos.z = 0;

	m_vDir = D3DXVECTOR3(0,0,1);

	D3DXVec3Unproject(&m_vDir,&m_vPos,&viewport,&mProj,NULL,NULL);

	D3DXVec3Normalize(&m_vDir,&m_vDir);

	m_vPos = D3DXVECTOR3(0,0,0);
}

void MouseRay::RayTransform( D3DXMATRIX* mInv )
{
	D3DXVec3TransformCoord(&m_vPos,&m_vPos,mInv);
	D3DXVec3TransformNormal(&m_vDir, &m_vDir,mInv);

	D3DXVec3Normalize(&m_vDir,&m_vDir);
}