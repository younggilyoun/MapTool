#pragma once

#include "d3d9.h"
#include "d3dx9.h"

#pragma comment(lib, "d3d9.lib")
#pragma comment(lib, "d3dx9.lib")




struct D3DFVF_XYZ_COLOR
{
	D3DXVECTOR3		vPos;
	DWORD			color;
};
#define FVF_XYZ_COLOR ( D3DFVF_XYZ | D3DFVF_DIFFUSE )



struct D3DFVF_XYZ_NORMAL_TEX1
{
	D3DXVECTOR3		vPos;
	D3DXVECTOR3		vNormal;
	float			u, v;
};
#define FVF_XYZ_NORMAL_TEX1 ( D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_TEX1 )

struct D3DINDEX
{
	DWORD _0, _1, _2;
};