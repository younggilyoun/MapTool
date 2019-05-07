#pragma once


class Tri;
class CameraTarget : public CameraBase
{
public:
	Tri*		m_pTarget;

public:
	void KeyControl(float dTime);

public:
	CameraTarget(CameraInfo _info);
	virtual ~CameraTarget(void);
};
