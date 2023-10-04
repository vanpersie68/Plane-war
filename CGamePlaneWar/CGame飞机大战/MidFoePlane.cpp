#include "MidFoePlane.h"


CMidFoePlane::CMidFoePlane(void)
{
	m_nBlood = 3;
	x = rand()%(380-70);
	y = -90;
	m_nShowID = 2;
}


CMidFoePlane::~CMidFoePlane(void)
{
}

bool CMidFoePlane::IsGunnerHitFoePlane(const CGunner* pGunner)	//是否被炮弹击中‎()
{
	if(pGunner->x >= this->x && pGunner->x <= this->x + 70 && pGunner->y >= this->y && pGunner->y <= this->y + 90)
		return true;
	return false;
}

bool CMidFoePlane::IsHitPlayer(const CPlayer& plane)				//是否撞玩家飞机‎()
{
	//x+30，y
	if(plane.x+30 >= this->x && plane.x+30 <= this->x+70 && plane.y >= this->y && plane.y <= this->y+70)
	{
		return false; 
	}
	//x+60,y+50
	if(plane.x+60 >= this->x && plane.x+60 <= this->x+70 && plane.y+50 >= this->y && plane.y+50 <= this->y+70)
	{
		return false; 
	}
	//x,y+50
	if(plane.x >= this->x && plane.x <= this->x+70 && plane.y+50 >= this->y && plane.y+50 <= this->y+70)
	{
		return false; 
	}
	return true;
}

void CMidFoePlane::InitFoePlane(HINSTANCE hIns)				//初始化敌人飞机‎()
{
	m_hBmpFoePlane = LoadBitmap(hIns,MAKEINTRESOURCE(IDB_MID));
}

void CMidFoePlane::MoveFoePlane()								//飞机移动‎()
{
	y = y + 4;
}

void CMidFoePlane::ShowFoePlane(HDC hdc)							//贴图()
{
	HDC hMenDC = CreateCompatibleDC(hdc);
	SelectObject(hMenDC,m_hBmpFoePlane);
	BitBlt(hdc,x,y,70,90,hMenDC,0,(2-m_nShowID)*90,SRCAND);

	DeleteDC(hMenDC);
	hMenDC = NULL;
}