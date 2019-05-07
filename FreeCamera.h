#pragma once

struct CamInfo
{
	D3DXVECTOR3		_vEye;
	D3DXVECTOR3		_vLookAt;
	D3DXVECTOR3		_vUp;
};

class FreeCamera
{
	D3DXVECTOR3			m_vEye;
	D3DXVECTOR3			m_vLookAt;
	D3DXVECTOR3			m_vUp;
	D3DXVECTOR3			m_vOrgUp;
	D3DXVECTOR3			m_vDir;
	D3DXVECTOR3			m_vHorz;

	D3DXMATRIX			m_mView;

public:
	void SetTransView(void);
	void SetTransProj(void);
	void KeyControl(float dTime);
	void SetCamVectors(void);
	void RotateX(float _angle);
	void RotateY(float _angle);

public:
	FreeCamera(CamInfo _info);
	virtual ~FreeCamera(void);
};
