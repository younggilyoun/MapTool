#include "DXCommon.h"
#include "WinCommon.h"

#include "DirectMgr.h"

DirectMgr::DirectMgr(void)
:m_pD3D(NULL), m_pDevice(NULL)
{

}

DirectMgr::~DirectMgr(void)
{
	Release();
}

void DirectMgr::Init( void )
{
	if( CreateDX() == true )
		CreateDevice();
}

bool DirectMgr::CreateDX( void )
{
	if( (m_pD3D = Direct3DCreate9(D3D_SDK_VERSION)) == NULL )
	{
		MessageBox(NULL, "3D객체생성 실패", "실패", MB_OK);
		return false;
	}

	return true;
}

void DirectMgr::CreateDevice( void )
{
	D3DPRESENT_PARAMETERS d3dpp;
	ZeroMemory(&d3dpp, sizeof(d3dpp));

	WindowsMgr* pWinMgr = WINDOWMGR;

	d3dpp.BackBufferWidth	= pWinMgr->GetWidth();
	d3dpp.BackBufferHeight	= pWinMgr->GetHeight();
	d3dpp.BackBufferCount	= 1;
	d3dpp.Windowed			= true;
	d3dpp.SwapEffect		= D3DSWAPEFFECT_DISCARD;
	d3dpp.PresentationInterval	= D3DPRESENT_INTERVAL_IMMEDIATE;
	d3dpp.EnableAutoDepthStencil = true;
	d3dpp.AutoDepthStencilFormat = D3DFMT_D24X8;

	m_pD3D->CreateDevice(
						D3DADAPTER_DEFAULT,
						D3DDEVTYPE_HAL,
						pWinMgr->GetViewHwnd(),
						D3DCREATE_HARDWARE_VERTEXPROCESSING,
						&d3dpp,
						&m_pDevice
						);

	if( m_pDevice == NULL )
		MessageBox(NULL, "디바이스 생성 실패", "실패", MB_OK);

}

void DirectMgr::Release( void )
{
	m_pDevice->Release();
	m_pD3D->Release();
}

void DirectMgr::Begin( void )
{
	m_pDevice->BeginScene();
}

void DirectMgr::End( void )
{
	m_pDevice->EndScene();
}

void DirectMgr::Clear( void )
{
	m_pDevice->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER,
		D3DXCOLOR(0.6f,0.6f,0.6f,1), 1.0f, 0);
}

void DirectMgr::Present( void )
{
	m_pDevice->Present(NULL, NULL, NULL, NULL);
}