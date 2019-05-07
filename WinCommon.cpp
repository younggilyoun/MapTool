#include "WinCommon.h"


POINT GetMousePos(void)
{
	POINT pt;

	GetCursorPos(&pt);
	ScreenToClient(WINDOWMGR->GetHwnd(),&pt);

	return pt;
}

void PathDivision( char* name, char* path, char* rname )
{
	char* p = strrchr(name, '/');
	if(p == NULL)
	{
		p = strrchr(name, '\\');
	}

	UINT n = (UINT)(p - name);		// ex)       "../data/airplane/hero.x"
	if(n>0 && n<100){
		strncpy(path, name, n);			// 경로얻기  "../data/airplane"
		strcpy(rname, p+1);
	}
}