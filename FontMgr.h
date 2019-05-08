#pragma once

#include "MySingleton.h"

class FontMgr : public MySingleton<FontMgr>
{	
public:
	void Init(void);
	void DrawText(int _x, int _y, D3DXCOLOR _color, char* msg, ...);

public:
	FontMgr(void);
	virtual ~FontMgr(void);
private:
	LPD3DXFONT			m_pFont;
};
