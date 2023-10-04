#include "Gunner.h"


CGunner::CGunner(void)
{
	m_hBmpGunner = NULL;
	x = 0;
	y = 0;
}


CGunner::~CGunner(void)
{
	::DeleteObject(m_hBmpGunner);
	m_hBmpGunner = NULL;
}

void CGunner::GunnerInit(HINSTANCE hIns, int x1, int y1) //初始化炮弹‎()
{
	m_hBmpGunner = LoadBitmap(hIns,MAKEINTRESOURCE(IDB_GUNNER));
	x = x1;
	y = y1;
}

void CGunner::GunnerMove()
{
	y = y - 10;
}

void CGunner::GunnerShow(HDC hdc)
{
	HDC hMenDC = CreateCompatibleDC(hdc);
	::SelectObject(hMenDC,m_hBmpGunner);
	::BitBlt(hdc,x,y,6,9,hMenDC,0,0,SRCAND);

	::DeleteDC(hMenDC);
	hMenDC = NULL;
}