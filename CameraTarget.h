#pragma once


class Tree;
class CameraTarget : public CameraBase
{
public:
	Tree*		m_pTarget;

public:
	void KeyControl(float dTime);

public:
	CameraTarget(CameraInfo _info);
	virtual ~CameraTarget(void);
};
