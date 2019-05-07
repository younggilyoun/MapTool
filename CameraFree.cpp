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
	// ���콺
	LONG	_x, _y, _z;
	GetMouseRelativePt(&_x, &_y, &_z);
	RotateX(_y * 0.003f);
	RotateY(_x * 0.003f);

	// �̵�
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