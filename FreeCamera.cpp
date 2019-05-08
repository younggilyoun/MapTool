#include "DXCommon.h"
#include "WinCommon.h"

#include "FreeCamera.h"

FreeCamera::FreeCamera(CamInfo _info)
:m_vEye(_info._vEye), m_vLookAt(_info._vLookAt), m_vUp(_info._vUp), m_vOrgUp(m_vUp)
{
	SetCamVectors();
}

FreeCamera::~FreeCamera(void)
{
}

void FreeCamera::SetTransView( void )
{
	D3DXMatrixLookAtLH(&m_mView, &m_vEye, &m_vLookAt, &m_vUp);
	DEVICE->SetTransform(D3DTS_VIEW, &m_mView);
}

void FreeCamera::SetTransProj( void )
{
	D3DXMATRIX		mProj;
	D3DXMatrixPerspectiveFovLH(&mProj, D3DXToRadian(45), 
				(float)WINDOWMGR->GetWidth() / WINDOWMGR->GetHeight(),
				1.0f, 1000.0f);

	DEVICE->SetTransform(D3DTS_PROJECTION, &mProj);
}

void FreeCamera::KeyControl( float dTime )
{
	// ¿Ãµø
	if( KeyDown(DIK_W) )
	{
		m_vEye += m_vDir * 5.0f * dTime;
		m_vLookAt += m_vDir * 5.0f * dTime;
		SetTransView();
	}

	if( KeyDown(DIK_S) )
	{
		m_vEye -= m_vDir * 5.0f * dTime;
		m_vLookAt -= m_vDir * 5.0f * dTime;
		SetTransView();
	}


	if( KeyDown(DIK_A) )
	{
		m_vEye -= m_vHorz * 3.0f * dTime;
		m_vLookAt -= m_vHorz * 3.0f * dTime;
		SetTransView();
	}

	if( KeyDown(DIK_D) )
	{
		m_vEye += m_vHorz * 3.0f * dTime;
		m_vLookAt += m_vHorz * 3.0f * dTime;
		SetTransView();
	}

	// ∏∂øÏΩ∫
	LONG	_nx, _ny, _nz;
	GetMouseRelativePt(&_nx, &_ny, &_nz);
	RotateX(_ny * 0.003f);
	RotateY(_nx * 0.003f);
}

void FreeCamera::SetCamVectors( void )
{
	// Ω√º±∫§≈Õ
	m_vDir = m_vLookAt - m_vEye;
	D3DXVec3Normalize(&m_vDir, &m_vDir);

	// ºˆ∆Ú∫§≈Õ
	D3DXVec3Cross(&m_vHorz, &m_vUp, &m_vDir);
	D3DXVec3Normalize(&m_vHorz, &m_vHorz);

	// up∫§≈Õ
	D3DXVec3Cross(&m_vUp, &m_vDir, &m_vHorz);
	D3DXVec3Normalize(&m_vUp, &m_vUp);
}

void FreeCamera::RotateX( float _angle )
{
	D3DXMATRIX		_mRot;

	D3DXMatrixRotationAxis(&_mRot, &m_vHorz, _angle);

	D3DXVec3TransformNormal(&m_vDir, &m_vDir, &_mRot);
	D3DXVec3Normalize(&m_vDir, &m_vDir);

	D3DXVec3Cross(&m_vUp, &m_vDir, &m_vHorz);
	D3DXVec3Normalize(&m_vUp, &m_vUp);

	m_vLookAt = m_vEye + m_vDir * 10.0f;

	SetTransView();
}

void FreeCamera::RotateY( float _angle )
{
	D3DXMATRIX		_mRot;

	D3DXMatrixRotationAxis(&_mRot, &m_vOrgUp, _angle);

	D3DXVec3TransformNormal(&m_vDir, &m_vDir, &_mRot);
	D3DXVec3Normalize(&m_vDir, &m_vDir);

	D3DXVec3Cross(&m_vHorz, &m_vOrgUp, &m_vDir);
	D3DXVec3Normalize(&m_vHorz, &m_vHorz);

	m_vLookAt = m_vEye + m_vDir * 10.0f;

	SetTransView();
}