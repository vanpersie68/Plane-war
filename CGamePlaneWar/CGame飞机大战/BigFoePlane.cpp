#include "BigFoePlane.h"


CBigFoePlane::CBigFoePlane(void)
{
	m_nBlood = 5;
	x = rand()%(380-108);
	y = -128;
	m_nShowID = 3;
}


CBigFoePlane::~CBigFoePlane(void)
{

}

bool CBigFoePlane::IsGunnerHitFoePlane(const CGunner* pGunner)	//是否被炮弹击中‎()
{
	if(pGunner->x >= this->x && pGunner->x <= this->x + 108 && pGunner->y >= this->y && pGunner->y <= this->y + 128)
		return true;
	return false;
}

bool CBigFoePlane::IsHitPlayer(const CPlayer& plane)			//是否撞玩家飞机‎()
{
	//x+30，y
	if(plane.x+30 >= this->x && plane.x+30 <= this->x+108 && plane.y >= this->y && plane.y <= this->y+128)
	{
		return false; 
	}
	//x+60,y+50
	if(plane.x+60 >= this->x && plane.x+60 <= this->x+108 && plane.y+50 >= this->y && plane.y+50 <= this->y+128)
	{
		return false; 
	}
	//x,y+50
	if(plane.x >= this->x && plane.x <= this->x+108 && plane.y+50 >= this->y && plane.y+50 <= this->y+128)
	{
		return false; 
	}
	return true;
}

void CBigFoePlane::InitFoePlane(HINSTANCE hIns)					//初始化敌人飞机‎()
{
	m_hBmpFoePlane = LoadBitmap(hIns,MAKEINTRESOURCE(IDB_BIG));
}

void CBigFoePlane::MoveFoePlane()								//飞机移动‎()
{
	y = y + 2;
}

void CBigFoePlane::ShowFoePlane(HDC hdc)						//贴图()
{
	HDC hMenDC = CreateCompatibleDC(hdc);
	SelectObject(hMenDC,m_hBmpFoePlane);
	BitBlt(hdc,x,y,108,128,hMenDC,0,(3-m_nShowID)*128,SRCAND);

	DeleteDC(hMenDC);
	hMenDC = NULL;
}