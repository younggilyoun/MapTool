#include "DXCommon.h"
#include "WinCommon.h"

#include "FontMgr.h"

FontMgr::FontMgr(void)
{
	m_pFont		= NULL;
}

FontMgr::~FontMgr(void)
{
	SAFE_RELEASE(m_pFont);
}

void FontMgr::Init( void )
{
	D3DXCreateFont(DEVICE, 12, 6, 1, 0, false, DEFAULT_CHARSET,
					OUT_DEFAULT_PRECIS, DEFAULT_QUALITY,
					DEFAULT_PITCH | FF_DONTCARE, 
					(LPSTR)"굴림", &m_pFont
					);

	if( m_pFont == NULL )
		MessageBox(NULL, "폰트생성실패", "실패", MB_OK);
}

void FontMgr::DrawText( int _x, int _y, D3DXCOLOR _color, char* msg, ... )
{
	char _szBuff[256] = {0,};
	va_list vl;
	va_start(vl, msg);
	vsprintf(_szBuff, msg, vl);
	va_end(vl);

	RECT rc = { _x, _y, 0, 0 };
	m_pFont->DrawText(NULL, _szBuff, strlen(_szBuff),
						&rc, DT_NOCLIP, _color);
}