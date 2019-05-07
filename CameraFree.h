#pragma once


class CameraFree : public CameraBase
{
public:
	void KeyControl(float dTime);

public:
	CameraFree(CameraInfo _info);
	virtual ~CameraFree(void);
};
