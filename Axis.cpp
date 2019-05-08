#include "DXCommon.h"
#include "WinCommon.h"
#include "Axis.h"

Axis::Axis(void)
	:m_pVB(NULL), m_pVtxs(NULL)
{

}

Axis::~Axis(void)
{
	Release();
}

void Axis::Init( _AXISINFO info)
{
	D3DXMatrixIdentity(&m_mTM); 

	m_AxisInfo	= info;

	//���� 3�� + ���� ��� ��ǥ 3��.
	m_pVtxs = new D3DFVF_XYZ_COLOR[6+3];

	// x��
	m_pVtxs[0].vPos = D3DXVECTOR3(0, 0, 0);		
	m_pVtxs[1].vPos = D3DXVECTOR3(m_AxisInfo.length, 0, 0);
	m_pVtxs[0].color = D3DXCOLOR(1, 0, 0, 1);
	m_pVtxs[1].color = D3DXCOLOR(1, 0, 0, 1);

	// y��
	m_pVtxs[2].vPos = D3DXVECTOR3(0, 0, 0);		
	m_pVtxs[3].vPos = D3DXVECTOR3(0, m_AxisInfo.length, 0);
	m_pVtxs[2].color = D3DXCOLOR(0, 1, 0, 1);
	m_pVtxs[3].color = D3DXCOLOR(0, 1, 0, 1);

	// z��
	m_pVtxs[4].vPos = D3DXVECTOR3(0, 0, 0);		
	m_pVtxs[5].vPos = D3DXVECTOR3(0, 0, m_AxisInfo.length);
	m_pVtxs[4].color = D3DXCOLOR(0, 0.3f, 1, 1);
	m_pVtxs[5].color = D3DXCOLOR(0, 0.3f, 1, 1);


	// ��ǥ�� ����
	m_pVtxs[6].vPos = D3DXVECTOR3(m_AxisInfo.length+0.1f, 0, 0);
	m_pVtxs[7].vPos = D3DXVECTOR3(0, m_AxisInfo.length+0.1f, 0);
	m_pVtxs[8].vPos = D3DXVECTOR3(0, 0, m_AxisInfo.length+0.1f);
	m_pVtxs[6].color = D3DXCOLOR(1, 0, 0, 1);
	m_pVtxs[7].color = D3DXCOLOR(0, 1, 0, 1);
	m_pVtxs[8].color = D3DXCOLOR(0, 0.3f, 1, 1);
}


void Axis::Update(void) 
{
	// �� ��� ���
	D3DXMATRIX mView;			
	DEVICE->GetTransform(D3DTS_VIEW, &mView);	 

	// �������� ��� ���
	D3DXMATRIX mProj;	
	DEVICE->GetTransform(D3DTS_PROJECTION, &mProj);


	D3DXMATRIX mVP; 							 
	D3DXMatrixIdentity(&mVP);

	// 3D��ǥ�� -> 2D��ǥ�� ��ȯ ���
	mVP._11 = m_AxisInfo.width * 0.5f;				
	mVP._22 = -(m_AxisInfo.height * 0.5f);			
	mVP._41 = m_AxisInfo.width * 0.5f;				
	mVP._42 = m_AxisInfo.height - m_AxisInfo.height * 0.5f;	

	// ���� ���
	D3DXMATRIX mTM;			
	D3DXMatrixIdentity(&mTM);

	//���� �����ġ ���� ���.
	mTM = mView * mProj * mVP; 

	for(int i=6, k=0; i<9; i++ , k++)
		D3DXVec3TransformCoord(&m_vTextPos[k], &m_pVtxs[i].vPos, &mTM);
}

void Axis::Render(DWORD width, DWORD height)
{
	DEVICE->SetTransform(D3DTS_WORLD, &m_mTM);

	DEVICE->SetRenderState(D3DRS_LIGHTING, false);
	DEVICE->SetRenderState(D3DRS_ZENABLE, false); 	
	DEVICE->SetFVF(FVF_XYZ_COLOR);	

	DEVICE->DrawPrimitiveUP(D3DPT_LINELIST, 3, m_pVtxs, sizeof(D3DFVF_XYZ_COLOR)); 

	DEVICE->SetRenderState(D3DRS_LIGHTING, false);
	DEVICE->SetRenderState(D3DRS_ZENABLE, true);

	// ���� ���
	FONTMGR->DrawText((int)m_vTextPos[0].x,		(int)m_vTextPos[0].y-5, m_pVtxs[6].color,  "X");
	FONTMGR->DrawText((int)m_vTextPos[1].x-4,	(int)m_vTextPos[1].y-5, m_pVtxs[7].color,  "Y" );
	FONTMGR->DrawText((int)m_vTextPos[2].x,		(int)m_vTextPos[2].y-5, m_pVtxs[8].color,  "Z" );
}

void Axis::Release()
{
	SAFE_RELEASE(m_pVB);
	SAFE_DELETE(m_pVtxs);	
}
