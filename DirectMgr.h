#pragma once

#include "MySingleton.h"

class DirectMgr : public MySingleton<DirectMgr>
{	
public:
	LPDIRECT3DDEVICE9	GetDevice(void) { return m_pDevice; }
	void Begin(void);
	void End(void);
	void Clear(void);
	void Present(void);
	void Init(void);

public:
	DirectMgr(void);
	virtual ~DirectMgr(void);

private:
	LPDIRECT3D9				m_pD3D;
	LPDIRECT3DDEVICE9		m_pDevice;

	bool CreateDX(void);
	void CreateDevice(void);
	void Release(void);
};
