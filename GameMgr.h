#pragma once

#include "MySingleton.h"

enum CAMTYPE { CT_FREE, CT_FPS, CT_TARGET, CT_MAX };

class CameraBase;
class Tree;
class FreeCamera;
class Camera;
class Axis;
class Grid;
class Terrain;
class GameMgr : public MySingleton<GameMgr>
{

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
	Terrain*    GetTerrain() {		return m_Terrain;	}
	Tree*		GetTree() { return m_pTree; }

public:
	GameMgr(void);
	virtual ~GameMgr(void);

protected:
	Terrain*		m_Terrain;

private:
	CAMTYPE			m_enCamType;
	CameraBase*		m_pCurrCamera;
	CameraBase*		m_pCamera[CT_MAX];
	Axis*			m_pAxis;
	Grid*			m_pGrid;

	Tree*			m_pTree;

	bool			m_bDebugTextShow;
	bool			m_bWire;
};
