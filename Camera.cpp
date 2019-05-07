#include "DXCommon.h"
#include "WinCommon.h"
#include "Camera.h"

//////////////////////////////////////////////////////////////////////////
//
// ���� �� �Ҹ���
//
Camera::Camera(void)
{
	m_vEye		= D3DXVECTOR3(5,5,-15);
	m_vLookAt	= D3DXVECTOR3(0,0,0);
	m_vUp		= D3DXVECTOR3(0,1,0);
	m_vViewDir	= D3DXVECTOR3(0,0,0);

	m_vOrgEye	= m_vEye;
	m_vOrgLookAt= m_vLookAt;

	m_fFov		= D3DXToRadian(45);		
	m_fAspect	= (float)WINDOWMGR->GetWidth() / WINDOWMGR->GetHeight();
	m_fZnear	= 1.0f;	
	m_fZfar		= 1000.0f;	

	D3DXMatrixIdentity(&m_mView);
	D3DXMatrixIdentity(&m_mInvView);
	D3DXMatrixIdentity(&m_mProj);
	D3DXMatrixIdentity(&m_mRotate);

	m_bCameraAutoRotate	= false;

	m_vViewDir = m_vLookAt - m_vEye;
	D3DXVec3Normalize(&m_vViewDir, &m_vViewDir);
}

Camera::Camera( D3DXVECTOR3 _vEye, D3DXVECTOR3 _vLookAt, D3DXVECTOR3 _vUp,
			   float _Fov, float _Aspect, float _near, float _far )
{
	m_vEye		= _vEye;
	m_vLookAt	= _vLookAt;
	m_vUp		= _vUp;

	m_fFov		= _Fov;
	m_fAspect	= _Aspect;
	m_fZnear	= _near;
	m_fZfar		= _far;

	D3DXMatrixIdentity(&m_mView);
	D3DXMatrixIdentity(&m_mInvView);
	D3DXMatrixIdentity(&m_mProj);
	D3DXMatrixIdentity(&m_mRotate);

	m_bCameraAutoRotate	= false;
}

Camera::~Camera(void)
{
}



//////////////////////////////////////////////////////////////////////////
//
// �ܺ� ȣ�� �Լ�
//

// �亯ȯ //
void Camera::ViewTransFrom( void )
{
	D3DXMatrixLookAtLH(&m_mView, &m_vEye, &m_vLookAt, &m_vUp);
	DEVICE->SetTransform(D3DTS_VIEW, &m_mView);
}

// �������� ��ȯ //
void Camera::ProjectionTransFrom( void )
{
	D3DXMatrixPerspectiveFovLH(&m_mProj, m_fFov, m_fAspect, m_fZnear, m_fZfar);		
	DEVICE->SetTransform(D3DTS_PROJECTION, &m_mProj);	
}

// ī�޶� ������Ʈ //
void Camera::UpdateCamera( float dTime )
{
	if( KeyDown(DIK_W) )
	{
		m_vEye += m_vViewDir * dTime;
		ViewTransFrom();
	}
}