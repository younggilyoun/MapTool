#pragma once

#include "MySingleton.h"

class DirectMgr : public MySingleton<DirectMgr>
{
	LPDIRECT3D9				m_pD3D;
	LPDIRECT3DDEVICE9		m_pDevice;

public:
	void Init(void);
	bool CreateDX(void);
	void CreateDevice(void);
	void Release(void);

	void Begin(void);
	void End(void);
	void Clear(void);
	void Present(void);

public:
	LPDIRECT3DDEVICE9	GetDevice(void) { return m_pDevice; }


public:
	DirectMgr(void);
	virtual ~DirectMgr(void);
};
