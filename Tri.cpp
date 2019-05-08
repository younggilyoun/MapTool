#include "DXCommon.h"
#include "WinCommon.h"

#include "Tri.h"

Tree::Tree(void)
{
	m_iFaceCnt		= 0;
	m_fSpeed		= 5.0f;

	m_pVB			= NULL;

	m_vPos			= D3DXVECTOR3(0,0,0);
	m_vRot			= D3DXVECTOR3(0,0,0);
	m_vDir			= D3DXVECTOR3(0,0,1);
	m_vOrgDir		= m_vDir;

	D3DXMatrixIdentity(&m_mTM);
}

Tree::~Tree(void)
{
	Release();
}

void Tree::Init( void )
{
	D3DFVF_XYZ_COLOR Vertices[] =
	{
		{ D3DXVECTOR3(-1.0f, 0.0f, 0.0f), 0xffff0000 },
		{ D3DXVECTOR3( 0.0f, 1.0f, 0.0f), 0xffff0000 },
		{ D3DXVECTOR3( 1.0f, 0.0f, 0.0f), 0xffff0000 }
	};

	DEVICE->CreateVertexBuffer(sizeof(Vertices), 0, FVF_XYZ_COLOR,
								D3DPOOL_MANAGED, &m_pVB, NULL);
	if( m_pVB == NULL )
		MessageBox(NULL, "버텍스버퍼 생성실패", "실패", MB_OK);

	void* pBuff = NULL;
	m_pVB->Lock(0, sizeof(Vertices), (void**)&pBuff, 0);
	memcpy(pBuff, Vertices, sizeof(Vertices));
	m_pVB->Unlock();

	m_iFaceCnt = sizeof(Vertices) / (sizeof(D3DFVF_XYZ_COLOR)*3);
}

void Tree::Update( float dTime )
{
	D3DXVec3TransformNormal(&m_vDir, &m_vOrgDir, &m_mTM);

 	if( KeyDown(DIK_UP) )
 		m_vPos += m_vDir * m_fSpeed * dTime;
 	if( KeyDown(DIK_DOWN) )
 		m_vPos -= m_vDir * m_fSpeed * dTime;

	if( KeyDown(DIK_LEFT) )
		m_vRot.y -= D3DX_PI * dTime;
	if( KeyDown(DIK_RIGHT) )
		m_vRot.y += D3DX_PI * dTime;

	

	D3DXMatrixTranslation(&m_mTrans, m_vPos.x, m_vPos.y, m_vPos.z);
	D3DXMatrixRotationY(&m_mRot, m_vRot.y);

	m_mTM = m_mRot * m_mTrans;
}

void Tree::Render( void )
{
	DEVICE->SetStreamSource(0, m_pVB, 0, sizeof(D3DFVF_XYZ_COLOR));
	DEVICE->SetFVF(FVF_XYZ_COLOR);
	DEVICE->SetTransform(D3DTS_WORLD, &m_mTM);

	DEVICE->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);

	DEVICE->DrawPrimitive(D3DPT_TRIANGLELIST, 0, m_iFaceCnt);

	DEVICE->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
}

void Tree::Release( void )
{
	SAFE_RELEASE(m_pVB);
}

float Tree::MyLerp( float _sx, float _ey, float _time )
{
	float _rx = 0.0f;

	_rx = _sx * (1 - _time) + _ey * _time;

	return _rx;
}