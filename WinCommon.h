#pragma once

#include <Windows.h>
#include <stdio.h>
#include <set>
#include <list>

using namespace std;


#define SAFE_RELEASE(p)		{ if(p) (p)->Release(); (p) = NULL; }
#define SAFE_DELETE(p)		{ if(p) delete (p); (p) = NULL;	}
#define SAFE_DELETE_ARRAY(p){ if(p) delete [] (p); (p) = NULL; }

#include "DXCommon.h"

#include "FontMgr.h"
#include "DXinput.h"
#include "WindowsMgr.h"
#include "DirectMgr.h"
#include "TreeMgr.h"
#include "GameMgr.h"



// µðÆÄÀÎ
#define WINDOWMGR	WindowsMgr::GetInstance()
#define DIRECTMGR	DirectMgr::GetInstance()
#define GAMEMGR		GameMgr::GetInstance()
#define DEVICE		DirectMgr::GetInstance()->GetDevice()
#define MYINPUT		DXinput::GetInstance()
#define TREEMGR		TreeMgr::GetInstance()
#define FONTMGR		FontMgr::GetInstance()


POINT GetMousePos(void);
void PathDivision(char* name, char* path, char* rname);