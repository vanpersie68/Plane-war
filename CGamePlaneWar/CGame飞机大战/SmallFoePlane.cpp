#include "SmallFoePlane.h"


CSmallFoePlane::CSmallFoePlane(void)
{
	m_nBlood = 1;
	x = rand()%(380-34);
	y = -28;
	m_nShowID = 1;
}


CSmallFoePlane::~CSmallFoePlane(void)
{
}


bool CSmallFoePlane::IsGunnerHitFoePlane(const CGunner* pGunner)	//是否被炮弹击中‎()
{
	if(pGunner->x >= this->x && pGunner->x <= this->x + 34 && pGunner->y >= this->y && pGunner->y <= this->y +  28)
		return true;
	return false;
}

bool CSmallFoePlane::IsHitPlayer(const CPlayer& plane)				//是否撞玩家飞机‎()
{
	//x+30，y
	if(plane.x+30 >= this->x && plane.x+30 <= this->x+34 && plane.y >= this->y && plane.y <= this->y+28)
	{
		return false; 
	}
	//x+60,y+50
	if(plane.x+60 >= this->x && plane.x+60 <= this->x+34 && plane.y+50 >= this->y && plane.y+50 <= this->y+28)
	{
		return false; 
	}
	//x,y+50
	if(plane.x >= this->x && plane.x <= this->x+34 && plane.y+50 >= this->y && plane.y+50 <= this->y+28)
	{
		return false; 
	}
	return true;
}

void CSmallFoePlane::InitFoePlane(HINSTANCE hIns)				//初始化敌人飞机‎()
{
	m_hBmpFoePlane = LoadBitmap(hIns,MAKEINTRESOURCE(IDB_SMALL));
}

void CSmallFoePlane::MoveFoePlane()								//飞机移动‎()
{
	y = y + 6;
}

void CSmallFoePlane::ShowFoePlane(HDC hdc)							//贴图()
{
	HDC hMenDC = CreateCompatibleDC(hdc);
	SelectObject(hMenDC,m_hBmpFoePlane);
	BitBlt(hdc,x,y,34,28,hMenDC,0,(1-m_nShowID)*28,SRCAND);

	DeleteDC(hMenDC);
	hMenDC = NULL;
}