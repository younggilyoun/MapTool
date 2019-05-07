#pragma once

#include "MySingleton.h"

enum CAMTYPE { CT_FREE, CT_FPS, CT_TARGET, CT_MAX };

class CameraBase;
class Tri;
class FreeCamera;
class Camera;
class Axis;
class Grid;
class Terrain;
class GameMgr : public MySingleton<GameMgr>
{
public:
	Terrain*		g_Terrain;
	CAMTYPE			m_enCamType;
	CameraBase*		m_pCurrCamera;
	CameraBase*		m_pCamera[CT_MAX];
	Axis*			m_pAxis;
	Grid*			m_pGrid;

	Tri*			m_pTri;

	bool			m_bDebugTextShow;
	bool			m_bWire;

public:
	void Init(char* _name);
	void Update(float dTime);
	void Render(void);
	void Release(void);
	void GameLoop(void);
	void DebugText(void);
	float GetDeltaTime(void);
	void DrawFPS(void);
	void SystemUpdate(void);

	CameraBase* GetCurrCamera(void) { return m_pCurrCamera; }

public:
	GameMgr(void);
	virtual ~GameMgr(void);
};
