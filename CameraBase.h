#pragma once

struct CameraInfo
{
	char			_strName[256];
	D3DXVECTOR3		_vEye;
	D3DXVECTOR3		_vLookAt;
	D3DXVECTOR3		_vUp;
};

class CameraBase
{
protected:
	D3DXVECTOR3			m_vEye;
	D3DXVECTOR3			m_vLookAt;
	D3DXVECTOR3			m_vOrgEye;
	D3DXVECTOR3			m_vOrgLookAt;
	D3DXVECTOR3			m_vUp;
	D3DXVECTOR3			m_vOrgUp;
	D3DXVECTOR3			m_vDir;
	D3DXVECTOR3			m_vHorz;
	D3DXMATRIX			m_mView;
	char				m_strName[256];

public:
	void SetTransView(void);
	void SetTransProj(void);
	void Update(float dTime);
	void SetCamVectors(void);

	virtual void KeyControl(float dTime) = 0;
	virtual void RotateX(float _angle);
	virtual void RotateY(float _angle);
	virtual void MoveX(float _move);
	virtual void MoveY(float _move);
	virtual void MoveZ(float _move);
	char*		GetName() { return m_strName; }
	D3DXMATRIX  GetView() { return m_mView;}
public:
	CameraBase(CameraInfo _info);
	virtual ~CameraBase(void);
};
