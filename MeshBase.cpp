#include "DXCommon.h"
#include "WinCommon.h"
#include "QuadNode.h"
#include "Terrain.h"
#include "MeshBase.h"

MeshBase::MeshBase(void)
:m_pMesh(NULL), m_pMaterials(NULL), m_pTexture(NULL), m_pvTempPos(NULL),
m_dMtricnt(0), m_fSpeed(5.0), m_iFaceCnt(0), m_fAlpha(1.0), m_iNum(1),
m_vPos(D3DXVECTOR3(0, 0, 0)), m_vRot(D3DXVECTOR3(D3DX_PI / 2, 0, 0)), m_vScale(D3DXVECTOR3(1, 1, 1)), m_vDir(D3DXVECTOR3(0, 0, -1)),
m_vOrgDir(m_vDir)
{		
	
}

MeshBase::~MeshBase(void)
{
	Release();
}


void MeshBase::init(char* name)
{
	D3DXMatrixIdentity(&m_mTM);
	D3DXMatrixIdentity(&m_mTrans);
	D3DXMatrixIdentity(&m_mRot);
	D3DXMatrixIdentity(&m_mScale);
	D3DXMatrixIdentity(&m_mParentTM);
	D3DXMatrixIdentity(&m_mTempTrans);

	char chDir[256]		= "";
	char chMeshPath[256]	= "";
	char chMeshName[256]	= "";

	PathDivision(name, chMeshPath, chMeshName);

	LPD3DXBUFFER pMtrlBuffer = NULL;
	char		 szDebugString[256] = {0,};

	D3DXLoadMeshFromX(name, D3DXMESH_MANAGED, DEVICE, NULL,	&pMtrlBuffer,NULL,&m_dMtricnt,&m_pMesh);

	if(m_pMesh == NULL)
	{
		MessageBox(NULL, "why error???", "error", MB_OK);
		return;
	}

	GetCurrentDirectory(256, chDir);
	SetCurrentDirectory(chMeshPath);
	//Material 할당
	m_pMaterials = new D3DMATERIAL9[m_dMtricnt];
	m_pTexture = new LPDIRECT3DTEXTURE9[m_dMtricnt];

	ZeroMemory(m_pMaterials, sizeof(D3DMATERIAL9)*m_dMtricnt);
	ZeroMemory(m_pTexture, sizeof(LPDIRECT3DTEXTURE9)*m_dMtricnt);

	//재질 정보
	D3DXMATERIAL* pMtrls = (D3DXMATERIAL*)pMtrlBuffer->GetBufferPointer();

	for(int i = 0; i<m_dMtricnt; i++)
	{
		m_pMaterials[i] = pMtrls[i].MatD3D;

		if(pMtrls[i].pTextureFilename != NULL && 
			strlen(pMtrls[i].pTextureFilename) > 0)
		{
			D3DXCreateTextureFromFile(DEVICE,pMtrls[i].pTextureFilename,
				&m_pTexture[i]);

			if(m_pTexture == NULL)
			{
				MessageBox(NULL, "TEX Load error", "error", MB_OK);
				return;
			}
		}
	}	
	SetCurrentDirectory(chDir);
}

void MeshBase::Update( float dTime )
{	
	if (m_iNum==4)
	{
		m_vRot.x=0;
	}
	D3DXVECTOR3 temp;
	temp.x = m_mTM._41;
	temp.y = m_mTM._42;
	temp.z = m_mTM._43;

	m_vPos.y = GAMEMGR->GetTerrain()->GetPlayerHeight(temp);
	D3DXMatrixTranslation(&m_mTrans, m_vPos.x,m_vPos.y,m_vPos.z);
	D3DXMatrixRotationYawPitchRoll(&m_mRot,m_vRot.y,m_vRot.x,m_vRot.z);
	D3DXMatrixScaling(&m_mScale,m_vScale.x,m_vScale.y,m_vScale.z);
	D3DXVec3TransformNormal(&m_vDir,&m_vOrgDir,&m_mRot);

	m_mTM = m_mScale* m_mRot * m_mTrans * m_mParentTM;
	if(m_pvTempPos != NULL)
	{
		D3DXMATRIX temp;
		D3DXMatrixTranslation(&temp, m_pvTempPos->x, m_pvTempPos->y, m_pvTempPos->z);

		m_mTM = m_mTM*temp;
	}
	
}

void MeshBase::Render( void )
{
	DEVICE->SetTransform(D3DTS_WORLD, &m_mTM);
	DEVICE->SetRenderState(D3DRS_LIGHTING,false);

	DEVICE->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);

	for(int i=0; i< (int)m_dMtricnt;i++)
	{
		DEVICE->SetMaterial(&m_pMaterials[i]);
		DEVICE->SetTexture(0,m_pTexture[i]);
		// 블렌드

		DEVICE->SetRenderState(D3DRS_ALPHABLENDENABLE, true);
		DEVICE->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
		DEVICE->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

		// 알파 연산
		DEVICE->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_SELECTARG1);
		DEVICE->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_CONSTANT);
		DEVICE->SetTextureStageState(0, D3DTSS_CONSTANT, D3DXCOLOR(0,0,0, m_fAlpha));
		DEVICE->DrawPrimitive(D3DPT_TRIANGLELIST, 0, m_iFaceCnt);
		m_pMesh->DrawSubset(i);
	}

	DEVICE->SetRenderState(D3DRS_ALPHABLENDENABLE, false);

	DEVICE->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_ONE);
	DEVICE->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ZERO);

	DEVICE->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_SELECTARG1);
	DEVICE->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);

}

void MeshBase::Release( void )
{
	SAFE_RELEASE(m_pMesh);
	SAFE_DELETE_ARRAY(m_pMaterials);
	for(int i=0; i<(int)m_dMtricnt;++i)
	{
		SAFE_RELEASE(m_pTexture[i]);
	}
	SAFE_DELETE_ARRAY(m_pTexture);
}