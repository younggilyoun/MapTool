#include "DXCommon.h"
#include "WinCommon.h"
#include "CameraBase.h"
#include "CameraFree.h"

CameraFree::CameraFree(CameraInfo _info)
: CameraBase(_info)
{
}

CameraFree::~CameraFree(void)
{
}

void CameraFree::KeyControl( float dTime )
{
	// 마우스
	LONG	_nx, _ny, _nz;
	GetMouseRelativePt(&_nx, &_ny, &_nz);
	RotateX(_ny * 0.003f);
	RotateY(_nx * 0.003f);

	// 이동
	static float fMove = 0.0f;
	fMove = 10.0f * dTime;

	if( KeyDown(DIK_A) )
		MoveX(-fMove);

	if( KeyDown(DIK_D) )
		MoveX(fMove);

	if( KeyDown(DIK_W) )
		MoveZ(fMove);

	if( KeyDown(DIK_S) )
		MoveZ(-fMove);
}