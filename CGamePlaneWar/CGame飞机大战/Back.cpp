#include "Back.h"


CBack::CBack(void)
{
	m_hBmpBackDown = NULL;
	m_hBmpBackUp = NULL;
	x = 0;
	y = 0;
}


CBack::~CBack(void)
{
	//É¾³ýÍ¼Æ¬
	::DeleteObject(m_hBmpBackDown);
	m_hBmpBackDown = NULL;
	::DeleteObject(m_hBmpBackUp);
	m_hBmpBackUp = NULL;
}

void CBack::BackInit(HINSTANCE hIns)
{
	m_hBmpBackUp = LoadBitmap(hIns,MAKEINTRESOURCE(IDB_BACK));
	m_hBmpBackDown = LoadBitmap(hIns,MAKEINTRESOURCE(IDB_BACK));
}

void CBack::BackMove()
{
	if(y > 550)
	{
		y = 0;
	}
	else
	{
		y++;
	}
}

void CBack::BackShow(HDC hdc)
{
	HDC hMenDc = CreateCompatibleDC(hdc);
	::SelectObject(hMenDc,m_hBmpBackUp);
	BitBlt(hdc,x,y-550,380,550,hMenDc,0,0,SRCCOPY);

	::SelectObject(hMenDc,m_hBmpBackDown);
	BitBlt(hdc,x,y,380,550,hMenDc,0,0,SRCCOPY);
	
	DeleteDC(hMenDc);
	hMenDc = NULL;
}