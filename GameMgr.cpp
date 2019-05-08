
#include "DXCommon.h"
#include "WinCommon.h"

#include "CameraBase.h"
#include "CameraFree.h"
#include "CameraFPS.h"
#include "CameraTarget.h"

#include "FreeCamera.h"
#include "Camera.h"
#include "Axis.h"
#include "Grid.h"
#include "Tri.h"
#include "QuadNode.h"
#include "Terrain.h"
#include "GameMgr.h"



GameMgr::GameMgr(void)
:m_pCurrCamera(NULL), 
m_pAxis(NULL), 
m_pGrid(NULL),
m_pTree(NULL),
m_bDebugTextShow(true),
m_bWire(false),
m_enCamType(CT_FPS),
m_Terrain(NULL)
{
	for( int i = 0; i < CT_MAX; ++i )
		m_pCamera[i] = NULL;	
}

GameMgr::~GameMgr(void)
{
	Release();
}

void GameMgr::Init(char* _name)
{

	m_Terrain = new Terrain;
	m_Terrain->Init(128,_name);

	// TRI
	m_pTree = new Tree;
	m_pTree->Init();

	// 카메라 //

	// Free Cam
	CameraInfo _info;
	ZeroMemory(&_info, sizeof(_info));

	_info._vEye		= D3DXVECTOR3(5, 10, -15);
	_info._vLookAt	= D3DXVECTOR3(0, 0, 0);
	_info._vUp		= D3DXVECTOR3(0, 1, 0);
	strcpy(_info._strName, "Free Cam");

	m_pCamera[CT_FREE] = new CameraFree(_info);

	// FPS Cam
	strcpy(_info._strName, "FPS Cam");
	m_pCamera[CT_FPS] = new CameraFPS(_info);


	// Target Cam
	strcpy(_info._strName, "Target Cam");
	_info._vEye		= D3DXVECTOR3(0, 5, -15);
	m_pCamera[CT_TARGET] = new CameraTarget(_info);
	
	CameraTarget* pTarget = (CameraTarget*)m_pCamera[CT_TARGET];
	pTarget->m_pTarget = m_pTree;


	m_pCurrCamera = m_pCamera[m_enCamType];


	// 좌표축 //
	m_pAxis		= new Axis;

	_AXISINFO info;

	info.length = 5.0f;
	info.width	= WINDOWMGR->GetWidth();
	info.height = WINDOWMGR->GetHeight();

	m_pAxis->Init(info);


	// 그리드 //
	m_pGrid		= new Grid;

	GRIDINFO gInfo;
	gInfo._color	= D3DXCOLOR(0.3f, 0.3f, 0.3f, 1.0f);
	gInfo._w		= 100;
	gInfo._h		= 100;
	gInfo._scale	= 10;

	m_pGrid->Init_Grid(gInfo);

	
}

void GameMgr::Update( float dTime )
{	
	m_pAxis->Update();
	m_pTree->Update(dTime);
	TREEMGR->Update(dTime);
	m_Terrain->Update(dTime);
	//m_pCamera->UpdateCamera(dTime);
	//m_pCamera->KeyControl(dTime);
	m_pCurrCamera->Update(dTime);
}

void GameMgr::Render( void )
{	
	DIRECTMGR->Begin();
	DIRECTMGR->Clear();

	// 대괄호 안에 객체 그리기
	{
		m_Terrain->Render();
		m_pTree->Render();

		m_pGrid->Render_Grid();
		m_pAxis->Render( WINDOWMGR->GetWidth(), WINDOWMGR->GetHeight());

		TREEMGR->Render();

		// 폰트는 마지막
		if( m_bDebugTextShow == true )
			DebugText();
	}

	DIRECTMGR->End();
	DIRECTMGR->Present();
}

void GameMgr::GameLoop( void )
{
	float dTime = GetDeltaTime();

	SystemUpdate();
	Update(dTime);
	Render();
}

void GameMgr::Release( void )
{
	SAFE_DELETE(m_pTree);

	SAFE_DELETE(m_pGrid);
	//SAFE_DELETE(m_pCamera);
	SAFE_DELETE(m_pAxis);

	for( int i = 0; i < CT_MAX;  ++i)
		SAFE_DELETE(m_pCamera[i]);

	SAFE_DELETE(m_Terrain);
}

void GameMgr::DebugText( void )
{
	DrawFPS();
	
	int x = 1;
	int y = 30;
	
	FONTMGR->DrawText(x, y, D3DXCOLOR(1,0,0,1), "PAGEUP키 : 지형올리기");
	FONTMGR->DrawText(x, y+=14, D3DXCOLOR(1,0,0,1), "CamType : %s", 
									m_pCurrCamera->m_strName);

	//FONTMGR->DrawText(x, y+=14, D3DXCOLOR(0,0,1,1), "%f %f",d);
	FONTMGR->DrawText(x, y+=14, D3DXCOLOR(0,0,1,1), "- 와이어모드(F2키) : %s", m_bWire ? "ON" : "OFF");
}

float GameMgr::GetDeltaTime( void )
{
	static int oldTime = GetTickCount();
	int nowTime = GetTickCount();

	float dTime = (nowTime - oldTime) * 0.001f;

	oldTime = nowTime;

	return dTime;
}

void GameMgr::DrawFPS( void )
{
	static int oldTime = GetTickCount();
	int nowTime = GetTickCount();

	static int frmcnt = 0;
	static float fps = 0.0f;

	frmcnt++;

	if( (nowTime - oldTime) >= 1000 )
	{
		fps		= (float)frmcnt;
		frmcnt	= 0;
		oldTime = nowTime;
	}

	char msg[64] = {0,};
	sprintf(msg, "FPS : %.1f", fps);

	FONTMGR->DrawText(1, 1, D3DXCOLOR(0,1,0,1), msg);
}

void GameMgr::SystemUpdate( void )
{
	if( KeyUp(DIK_F1) )
		m_bDebugTextShow ^= true;

	if( KeyUp(DIK_F2) )
	{
		m_bWire ^= true;

		m_bWire ? 
			DEVICE->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME)
			: DEVICE->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);
	}

	if( KeyUp(DIK_1) )
	{
		m_enCamType = CT_FREE;
		m_pCurrCamera = m_pCamera[m_enCamType];
	}

	if( KeyUp(DIK_2) )
	{
		m_enCamType = CT_FPS;
		m_pCurrCamera = m_pCamera[m_enCamType];
	}

	if( KeyUp(DIK_3) )
	{
		m_enCamType = CT_TARGET;
		m_pCurrCamera = m_pCamera[m_enCamType];
	}
}