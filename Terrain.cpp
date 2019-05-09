#include "DXCommon.h"
#include "WinCommon.h"
#include "QuadNode.h"
#include "QuadTree.h"
#include "MouseRay.h"
#include "CameraBase.h"
#include "Tri.h"
#include "Terrain.h"

Terrain::Terrain(void)
:m_TerrUpDown(1),
m_iPatchCnt(0),
m_iVertexCnt(0),
m_iTotalVertexCnt(0),
m_iTotalFaceCnt(0),
m_pVB(NULL),
m_pIB(NULL),
m_pTexture(NULL),
m_pTerrainVB(NULL),
m_pTerrainIB(NULL),
m_pQuadTree(0),
m_iQTTotalFaceCnt(0),
m_pQTIB(NULL),
m_pQTTerrainIB(NULL),
m_iCircleCnt(0),
m_vMouse(D3DXVECTOR3(0, 0, 0)),
m_ieditMode(0),
m_pSplatTexture(NULL),
m_pAlphaTexture(NULL),
m_iAlphaSize(256),
m_fQuadSize(10)
{
}

Terrain::~Terrain(void)
{
	Release();
	ReleaseCircle();
}

void Terrain::Init( int _patchCnt ,char* name)
{
	m_iPatchCnt			= _patchCnt;
	m_iVertexCnt		= _patchCnt + 1;

	m_iTotalVertexCnt	= m_iVertexCnt * m_iVertexCnt;
	m_iTotalFaceCnt		= m_iPatchCnt * m_iPatchCnt * 2;

	InitVB();
	InitIB();

	D3DXCreateTextureFromFile(DEVICE, name, &m_pTexture);
	name = NULL;

	QuadTreeCreate(6);
	m_pInfo.iPatchCnt			=m_iPatchCnt;
	m_pInfo.piQTTotalFaceCnt	=&m_iQTTotalFaceCnt;
	m_pInfo.pQTTerrainIB		=m_pQTTerrainIB;
	m_pInfo.pTerrainIB			=m_pTerrainIB;

	CreateAlphaTexture();
}

void Terrain::InitVB( void )
{
	m_pTerrainVB = new D3DFVF_XYZ_NORMAL_TEX1[m_iTotalVertexCnt];
	ZeroMemory(m_pTerrainVB, sizeof(D3DFVF_XYZ_NORMAL_TEX1)*m_iTotalVertexCnt);

	float fStartX = -(m_iPatchCnt/2);
	float fStartZ =  (m_iPatchCnt/2);

	for( int j = 0; j < m_iVertexCnt; ++j )
	{
		for( int i = 0; i < m_iVertexCnt; ++i )
		{
			int iPos = j * m_iVertexCnt + i;

			m_pTerrainVB[iPos].vPos.x	= fStartX + i;
			m_pTerrainVB[iPos].vPos.y	= 0.0f;
			m_pTerrainVB[iPos].vPos.z	= fStartZ - j;

			m_pTerrainVB[iPos].vNormal	= D3DXVECTOR3(0,1,0);

			m_pTerrainVB[iPos].u		= (float)i / m_iPatchCnt;
			m_pTerrainVB[iPos].v		= (float)j / m_iPatchCnt;
		}
	}

	DEVICE->CreateVertexBuffer(sizeof(D3DFVF_XYZ_NORMAL_TEX1)*m_iTotalVertexCnt,
								0, FVF_XYZ_NORMAL_TEX1, D3DPOOL_MANAGED,
								&m_pVB, NULL);

	void* pBuff = NULL;
	m_pVB->Lock(0, NULL, (void**)&pBuff, 0);

	memcpy(pBuff, m_pTerrainVB, 
			sizeof(D3DFVF_XYZ_NORMAL_TEX1)*m_iTotalVertexCnt);

	m_pVB->Unlock();

	initCircle();
}

void Terrain::InitIB( void )
{
	m_pTerrainIB = new D3DINDEX[m_iTotalFaceCnt];
	m_pQTTerrainIB = new D3DINDEX[m_iTotalFaceCnt];

	D3DINDEX*	pIndex = m_pTerrainIB;
	D3DINDEX	_index;

	for( int j = 0; j < m_iPatchCnt; ++j )
	{
		for( int i = 0; i < m_iPatchCnt; ++i )
		{
			_index._0 = j * m_iVertexCnt + i;
			_index._1 = j * m_iVertexCnt + (i+1);
			_index._2 = (j+1) * m_iVertexCnt + i;

			*pIndex++ = _index;

			_index._0 = (j+1) * m_iVertexCnt + i;
			_index._1 = j * m_iVertexCnt + (i+1);
			_index._2 = (j+1) * m_iVertexCnt + (i+1);

			*pIndex++ = _index;
			
		}
	}

	DEVICE->CreateIndexBuffer(sizeof(D3DINDEX)*m_iTotalFaceCnt, 0,
		D3DFMT_INDEX32, D3DPOOL_MANAGED,
		&m_pIB, NULL);

	DEVICE->CreateIndexBuffer(sizeof(D3DINDEX)*m_iTotalFaceCnt, 0,
		D3DFMT_INDEX32, D3DPOOL_MANAGED,
		&m_pQTIB, NULL);

	void* pBuff = NULL;
	m_pIB->Lock(0, sizeof(D3DINDEX)*m_iTotalFaceCnt, (void**)&pBuff, 0);

	memcpy(pBuff, m_pTerrainIB, sizeof(D3DINDEX)*m_iTotalFaceCnt);

	m_pIB->Unlock();
}

void Terrain::Update( float dTime )
{
	QuadCulling(m_vMouse);

	if(KeyDown(DIK_PGUP))
		TerrainUpDown(dTime,true);
	else if(KeyDown(DIK_PGDN))
		TerrainUpDown(dTime, false);

	UpdateCircle();

	for( int j = 0; j < m_iVertexCnt; ++j )
	{
		for( int i = 0; i < m_iVertexCnt; ++i )
		{
			int iPos = j * m_iVertexCnt + i;

			if(Collison(m_pTerrainVB[iPos].vPos))
			{
				m_vMouse = m_pTerrainVB[iPos].vPos;

				GAMEMGR->GetTree()->SetPos(m_vMouse);
			}			
		}
	}

	if(m_ieditMode==2){
		UpdateAlphaTexture();
	}
}

void Terrain::Render( void )
{
	DEVICE->SetRenderState(D3DRS_LIGHTING, false);
	DEVICE->SetTexture(0, m_pTexture);
	DEVICE->SetStreamSource(0, m_pVB, 0, sizeof(D3DFVF_XYZ_NORMAL_TEX1));
	DEVICE->SetFVF(FVF_XYZ_NORMAL_TEX1);

	D3DXMATRIX		m;
	D3DXMatrixIdentity(&m);
	DEVICE->SetTransform(D3DTS_WORLD, &m);
	
	DEVICE->SetIndices(m_pIB);
	DEVICE->DrawIndexedPrimitive(D3DPT_TRIANGLELIST,
		0, 0, m_iTotalVertexCnt, 0, m_iTotalFaceCnt);
	RenderAlphaTexture();

	//쿼드 트리
	DEVICE->SetRenderState(D3DRS_FILLMODE,D3DFILL_WIREFRAME);

	m._42 = 0.01f;
	DEVICE->SetTransform(D3DTS_WORLD, &m);
	DEVICE->SetTexture(0,NULL);
	DEVICE->SetIndices(m_pQTIB);
	DEVICE->DrawIndexedPrimitive(D3DPT_TRIANGLELIST,
		0, 0, m_iTotalVertexCnt, 0, m_iQTTotalFaceCnt);
	DEVICE->SetRenderState(D3DRS_FILLMODE,D3DFILL_SOLID);
	RenderCircle();
	
}

void Terrain::Release( void )
{
	SAFE_RELEASE(m_pVB);
	SAFE_RELEASE(m_pIB);
	SAFE_RELEASE(m_pTexture);

	SAFE_DELETE_ARRAY(m_pTerrainVB);
	SAFE_DELETE_ARRAY(m_pTerrainIB);
}

void Terrain::QuadTreeCreate( int _lev )
{
	m_pQuadTree = new QuadTree;
	m_pQuadTree->QuadCreate(m_pTerrainVB,_lev,m_iVertexCnt);
}

void Terrain::QuadCulling( D3DXVECTOR3 _vPos )
{
	ZeroMemory(m_pQTTerrainIB, sizeof(m_pQTTerrainIB)*m_iTotalFaceCnt);
	m_iQTTotalFaceCnt = 0;

	m_pQuadTree->FindQuadNode(_vPos,m_pInfo,&Terrain::SetQTIndex,m_fQuadSize);

	void* pBuff = NULL;

	m_pQTIB->Lock(0,sizeof(D3DINDEX)*m_iQTTotalFaceCnt,(void**)&pBuff,0);
	memcpy(pBuff, m_pQTTerrainIB,sizeof(D3DINDEX)*m_iQTTotalFaceCnt);
	m_pQTIB->Unlock();
}

void Terrain::TerrainUpDown( float dTime, bool bUP)
{
	set<int> setIndex;

	for(int i =0; i<m_iQTTotalFaceCnt; ++i)
	{
		int _0 = m_pQTTerrainIB[i]._0;
		int _1 = m_pQTTerrainIB[i]._1;
		int _2 = m_pQTTerrainIB[i]._2;

		setIndex.insert(_0);
		setIndex.insert(_1);
		setIndex.insert(_2);
	}

	for(auto nIndex : setIndex)
	{
		float _fx = 0.0,_fz = 0.0, _flen = 0.0,_finvlen = 0.0;

		if(m_ieditMode==0)
			_finvlen =1;
		if(m_ieditMode==1){
			_finvlen= 11;

			_fx = m_pTerrainVB[nIndex].vPos.x - m_vMouse.x;
			_fz = m_pTerrainVB[nIndex].vPos.z - m_vMouse.z;
			
			_flen = sqrt(_fx*_fx + _fz*_fz);
			
			_finvlen-=_flen/2;
		}
		if(bUP)
			m_pTerrainVB[nIndex].vPos += D3DXVECTOR3(0,_finvlen,0)*dTime*m_TerrUpDown;
		else
			m_pTerrainVB[nIndex].vPos -= D3DXVECTOR3(0, _finvlen, 0)*dTime*m_TerrUpDown;
	}

	void* pBuff = NULL;
	m_pVB->Lock(0, sizeof(D3DFVF_XYZ_NORMAL_TEX1)*m_iTotalVertexCnt,(void**)&pBuff,0);

	memcpy(pBuff,m_pTerrainVB,sizeof(D3DFVF_XYZ_NORMAL_TEX1)*m_iTotalVertexCnt);
	m_pVB->Unlock();
}

void Terrain::initCircle( void )
{
	m_iCircleCnt = 46;

	DEVICE->CreateVertexBuffer(sizeof(D3DFVF_XYZ_COLOR)*m_iCircleCnt,0,FVF_XYZ_COLOR,D3DPOOL_MANAGED,&m_pCircleVB,NULL);

}

void Terrain::UpdateCircle( void )
{
	D3DFVF_XYZ_COLOR* pBuff = NULL;
	m_pCircleVB->Lock(0,sizeof(D3DFVF_XYZ_COLOR)*m_iCircleCnt,(void**)&pBuff,0);
	
	for(int i=0; i<m_iCircleCnt;i++)
	{
		pBuff[i].vPos.x = m_fQuadSize*cos(i*D3DX_PI*8/180) + m_vMouse.x;
		pBuff[i].vPos.z = m_fQuadSize*sin(i*D3DX_PI*8/180) + m_vMouse.z;
		pBuff[i].vPos.y = 0;
		pBuff[i].color  = D3DXCOLOR(1,1,0,1);
	}	

	m_pCircleVB->Unlock();
}

void Terrain::RenderCircle( void )
{
	D3DXMATRIX m;
	D3DXMatrixIdentity(&m);
	m._42 = 0.01f;
	DEVICE->SetTransform(D3DTS_WORLD,&m);

	DEVICE->SetStreamSource(0,m_pCircleVB,0,sizeof(D3DFVF_XYZ_COLOR));
	DEVICE->SetFVF(FVF_XYZ_COLOR);
	DEVICE->SetRenderState(D3DRS_LIGHTING,false);

	DEVICE->DrawPrimitive(D3DPT_LINELIST,0,m_iCircleCnt/2);
	DEVICE->DrawPrimitive(D3DPT_LINELIST,1,(m_iCircleCnt/2-1));
}

void Terrain::ReleaseCircle()
{
	SAFE_RELEASE(m_pCircleVB);
}



bool Terrain::Collison(D3DXVECTOR3 _vPos)
{
	MouseRay ray;

	POINT pt = GetMousePos();

	ray.RayCreate(pt.x,pt.y);

	D3DXMATRIX minvView;
	DEVICE->GetTransform(D3DTS_VIEW, &minvView);
	D3DXMatrixInverse(&minvView,0,&minvView);

	ray.RayTransform(&minvView);

	float vSphereRadius = 1;

	//1. 레이부터 타겟까지 벡터
	D3DXVECTOR3 vRay_Target  = _vPos - ray.GetPos();

	//2. 레이와 타겟벡터의 직교길이
	float fRayDirLen  = D3DXVec3Dot(&vRay_Target,&ray.GetDir());

	//3. 직교하는 벡터
	D3DXVECTOR3 vRayResultPos = ray.GetPos() +(ray.GetDir()*fRayDirLen);

	//4. 직교벡터와 타겟과의 거리
	float fResultLen  = D3DXVec3Length(&(_vPos-vRayResultPos));

	if(fResultLen < vSphereRadius)
		return true;
	else
		return false;
}

void Terrain::LockVB()
{
	void* pBuff = NULL;
	m_pVB->Lock(0, sizeof(D3DFVF_XYZ_NORMAL_TEX1)*m_iTotalVertexCnt,(void**)&pBuff,0);

	memcpy(pBuff,m_pTerrainVB,sizeof(D3DFVF_XYZ_NORMAL_TEX1)*m_iTotalVertexCnt);
	m_pVB->Unlock();
}


float Terrain::GetPlayerHeight( D3DXVECTOR3 _vPos )
{
	float fHeight = 0.0f;
	float fDist = 0.0f;
	float u,v;
	D3DXVECTOR3 vPos[3];

	D3DXVECTOR3 vRayPos = _vPos + D3DXVECTOR3(0,100,0);
	D3DXVECTOR3 vRayDir = D3DXVECTOR3(0,-1,0);

	for(int i=0; i<m_iTotalFaceCnt; ++i)
	{
		int _0= m_pTerrainIB[i]._0;
		int _1= m_pTerrainIB[i]._1;
		int _2= m_pTerrainIB[i]._2;

		vPos[0] = m_pTerrainVB[_0].vPos;
		vPos[1] = m_pTerrainVB[_1].vPos;
		vPos[2] = m_pTerrainVB[_2].vPos;

		if(D3DXIntersectTri(&vPos[0],&vPos[1],&vPos[2],&vRayPos,&vRayDir,&u,&v,&fDist))
		{
			fHeight = vPos[0].y + (u*(vPos[1].y-vPos[0].y)) + (v*(vPos[2].y-vPos[0].y));

			return fHeight;
		}
	}

	return fHeight;
}

void Terrain::CreateAlphaTexture(void)
{
	D3DXCreateTextureFromFile(DEVICE, "Grass.jpg", &m_pSplatTexture);

	DEVICE->CreateTexture(m_iAlphaSize,m_iAlphaSize, 1, 0, D3DFMT_A8R8G8B8,
		D3DPOOL_MANAGED, &m_pAlphaTexture, NULL);

	D3DLOCKED_RECT _locked;
	ZeroMemory(&_locked, sizeof(_locked));

	m_pAlphaTexture->LockRect(0, &_locked, NULL, 0);

	BYTE* pData = (BYTE*)_locked.pBits;

	for( int j = 0; j < m_iAlphaSize; ++j )
	{
		DWORD* dwStartData = (DWORD*)(pData + j * _locked.Pitch );

		for( int i = 0; i < m_iAlphaSize; ++i )
		{
			*(dwStartData+i) = 0x00000000;
		}
	}

	m_pAlphaTexture->UnlockRect(0);
}

void Terrain::RenderAlphaTexture(void)
{
	DEVICE->SetRenderState(D3DRS_ALPHABLENDENABLE, true);
	DEVICE->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	DEVICE->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

	DEVICE->SetTextureStageState(0, D3DTSS_COLOROP, D3DTOP_SELECTARG1);
	DEVICE->SetTextureStageState(0, D3DTSS_COLORARG1, D3DTA_TEXTURE);
	DEVICE->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_SELECTARG1);
	DEVICE->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);
	DEVICE->SetTexture(0, m_pAlphaTexture);


	DEVICE->SetTextureStageState(1, D3DTSS_COLOROP, D3DTOP_MODULATE);
	DEVICE->SetTextureStageState(1, D3DTSS_COLORARG1, D3DTA_TEXTURE);
	DEVICE->SetTextureStageState(1, D3DTSS_COLORARG2, D3DTA_CURRENT);
	DEVICE->SetTextureStageState(1, D3DTSS_ALPHAOP, D3DTOP_MODULATE);
	DEVICE->SetTextureStageState(1, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);
	DEVICE->SetTextureStageState(1, D3DTSS_ALPHAARG2, D3DTA_CURRENT);
	DEVICE->SetTextureStageState(1, D3DTSS_TEXCOORDINDEX, 0);
	DEVICE->SetTexture(1, m_pSplatTexture);

	DEVICE->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, m_iTotalVertexCnt, 
		0, m_iTotalFaceCnt);

	DEVICE->SetTextureStageState(0, D3DTSS_COLOROP, D3DTOP_MODULATE);
	DEVICE->SetTextureStageState(0, D3DTSS_COLORARG1, D3DTA_TEXTURE);
	DEVICE->SetTextureStageState(0, D3DTSS_COLORARG2, D3DTA_DIFFUSE);
	DEVICE->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);
	DEVICE->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);
	DEVICE->SetTextureStageState(0, D3DTSS_ALPHAARG2, D3DTA_DIFFUSE);
	DEVICE->SetTextureStageState(1, D3DTSS_COLOROP, D3DTOP_DISABLE);
	DEVICE->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_ONE);
	DEVICE->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ZERO);

	DEVICE->SetTexture(0, NULL);
	DEVICE->SetTexture(1, NULL);


	DEVICE->SetRenderState(D3DRS_ALPHABLENDENABLE, false);
}

void Terrain::UpdateAlphaTexture(void)
{
	MouseRay _ray;
	POINT pt;
	GetCursorPos(&pt);
	ScreenToClient(WINDOWMGR->GetHwnd(), &pt);

	if( LButtonDown(0) )
	{

		_ray.RayCreate(pt.x, pt.y);

		D3DXMATRIX m;
		D3DXMatrixInverse(&m, 0, &((GAMEMGR->GetCurrCamera()->GetView())));
		_ray.RayTransform(&m);

		float iDist = 0;
		D3DXVECTOR3 vTargetPos;
		for( int i = 0; i < m_iTotalFaceCnt; ++i )
		{
			int _0 = m_pTerrainIB[i]._0;
			int _1 = m_pTerrainIB[i]._1;
			int _2 = m_pTerrainIB[i]._2;

			D3DXVECTOR3 v0 = m_pTerrainVB[_0].vPos;
			D3DXVECTOR3 v1 = m_pTerrainVB[_1].vPos;
			D3DXVECTOR3 v2 = m_pTerrainVB[_2].vPos;

			if( D3DXIntersectTri(&v0, &v1, &v2, 
				&_ray.GetPos(), &_ray.GetDir(), NULL, NULL, &iDist))
			{
				vTargetPos = _ray.GetPos() + _ray.GetDir() * iDist;
				break;
			}
		}
		// 지형과 알파맵 비율
		float fPixelSize = (float)m_iAlphaSize / (float)m_iPatchCnt;

		// 2d좌표계 변환
		float f2DPosX = (vTargetPos.x / (m_iPatchCnt/2))
			* (m_iAlphaSize/2) + (m_iAlphaSize/2);

		float f2DPosZ = -(vTargetPos.z / (m_iPatchCnt/2))
			* (m_iAlphaSize/2) + (m_iAlphaSize/2);

		float fAlphaCircleSize = 5.0f * fPixelSize;

		int iStartX, iStartZ, iEndX, iEndZ;

		if( f2DPosX - fAlphaCircleSize < 0 )
			iStartX = 0;
		else
			iStartX = f2DPosX - fAlphaCircleSize;

		if( f2DPosZ - fAlphaCircleSize < 0 )
			iStartZ = 0;
		else
			iStartZ = f2DPosZ - fAlphaCircleSize;

		if( f2DPosX + fAlphaCircleSize > m_iAlphaSize )
			iEndX = m_iAlphaSize;
		else
			iEndX = f2DPosX + fAlphaCircleSize;

		if( f2DPosZ + fAlphaCircleSize > m_iAlphaSize )
			iEndZ = m_iAlphaSize;
		else
			iEndZ = f2DPosZ + fAlphaCircleSize;

		D3DLOCKED_RECT _rected;
		ZeroMemory(&_rected, sizeof(D3DLOCKED_RECT));

		m_pAlphaTexture->LockRect(0, &_rected, NULL, 0);

		BYTE* pData = (BYTE*)_rected.pBits;

		for( int j = iStartZ; j < iEndZ; ++j )
		{
			DWORD* pStartData = (DWORD*)(pData + j * _rected.Pitch );

			for( int i = iStartX; i < iEndX; ++i )
			{
				int _length = sqrt((f2DPosX-i)*(f2DPosX-i)+(f2DPosZ-j)*(f2DPosZ-j));
			
				if(_length>fAlphaCircleSize)
					_length=fAlphaCircleSize;

				int _inv = (fAlphaCircleSize-_length)*2;
				
				float _temp = *(pStartData+i);

				_temp = (((((_temp-255)/256)-255)/256)-255)/256;

				_inv += _temp;

				if(_inv>=255)
					_inv =255;
				*(pStartData+i) = ((_inv*256+255)*256+255)*256+255;
				
			}
		}
		m_pAlphaTexture->UnlockRect(0);
	}

}

void Terrain::setUpDown( bool _TerrUpDown )
{	
	if(_TerrUpDown)
		m_TerrUpDown = -1;
	else
		m_TerrUpDown = 1;
}


void Terrain::SetQTIndex(QuadNode* pNode, QTINFO& data) {

	//1. 2차원 형식의 인덱스 x y 위치
	int iStartidxX = pNode->GetCorner(QT_LT) % (data.iPatchCnt + 1);
	int iStartidxY = pNode->GetCorner(QT_LT) / (data.iPatchCnt + 1);

	//2. 인덱스 너비
	int iQuadInterval = pNode->GetCorner(QT_RT) - pNode->GetCorner(QT_LT);

	//3. 1차원의 인덱스버퍼의 시작위치
	int iStartidx = (iStartidxY*data.iPatchCnt * 2) + (iStartidxX * 2);

	//4. 쿼드 인덱스 버퍼 셋팅
	int idx = *(data.piQTTotalFaceCnt);
	for (int j = 0; j < iQuadInterval; ++j) {
		for (int i = 0; i < iQuadInterval * 2; ++i)
		{
			data.pQTTerrainIB[idx] = data.pTerrainIB[iStartidx + i];
			idx++;
		}
		iStartidx += data.iPatchCnt * 2;
	}
	*data.piQTTotalFaceCnt = idx;
}