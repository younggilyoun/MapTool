#include "DXCommon.h"
#include "WinCommon.h"

#include "CameraBase.h"

CameraBase::CameraBase(CameraInfo _info)
:m_vEye(_info._vEye), m_vLookAt(_info._vLookAt),
m_vUp(_info._vUp), m_vOrgUp(m_vUp), m_vOrgEye(m_vEye),
m_vOrgLookAt(m_vLookAt)
{
	strcpy(m_strName, _info._strName);
	SetCamVectors();
	SetTransView();
	SetTransProj();
}

CameraBase::~CameraBase(void)
{
}

void CameraBase::SetTransView( void )
{
	D3DXMatrixLookAtLH(&m_mView, &m_vEye, &m_vLookAt, &m_vOrgUp);
	DEVICE->SetTransform(D3DTS_VIEW, &m_mView);
}

void CameraBase::SetTransProj( void )
{
	D3DXMATRIX		mProj;
	D3DXMatrixPerspectiveFovLH(&mProj, D3DXToRadian(45), 
							(float)WINDOWMGR->GetWidth() / WINDOWMGR->GetHeight(),
							1.0f, 1000.0f);

	DEVICE->SetTransform(D3DTS_PROJECTION, &mProj);
}


void CameraBase::SetCamVectors( void )
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

void CameraBase::RotateX( float _angle )
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

void CameraBase::RotateY( float _angle )
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

void CameraBase::Update( float dTime )
{
	KeyControl(dTime);
}

void CameraBase::MoveX( float _move )
{
	D3DXVECTOR3 vMove;
	D3DXVec3Normalize(&vMove, &m_vHorz);

	vMove = vMove * _move;

	m_vEye += vMove;
	m_vLookAt += vMove;

	SetTransView();
}

void CameraBase::MoveY( float _move )
{
	D3DXVECTOR3 vMove;
	D3DXVec3Normalize(&vMove, &m_vOrgUp);

	vMove = vMove * _move;

	m_vEye += vMove;
	m_vLookAt += vMove;

	SetTransView();
}

void CameraBase::MoveZ( float _move )
{
	D3DXVECTOR3 vMove;
	D3DXVec3Normalize(&vMove, &m_vDir);

	vMove = vMove * _move;

	m_vEye += vMove;
	m_vLookAt += vMove;

	SetTransView();
}