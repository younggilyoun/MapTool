#include "DXCommon.h"
#include "WinCommon.h"
#include "CameraBase.h"
#include "Tri.h"
#include "CameraTarget.h"

CameraTarget::CameraTarget(CameraInfo _info)
: CameraBase(_info)
{
	m_pTarget	= NULL;
}

CameraTarget::~CameraTarget(void)
{
}

void CameraTarget::KeyControl( float dTime )
{
	D3DXVec3TransformCoord(&m_vEye, &m_vOrgEye, &m_pTarget->m_mTM);
	D3DXVec3TransformCoord(&m_vLookAt, &m_vOrgLookAt, &m_pTarget->m_mTM);

	SetTransView();
}