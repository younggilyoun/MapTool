#pragma once


class CameraFPS : public CameraBase
{
public:
	void KeyControl(float dTime);
	void MoveZ(float _move);

public:
	CameraFPS(CameraInfo _info);
	virtual ~CameraFPS(void);
};
