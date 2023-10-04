#include "Player.h"


CPlayer::CPlayer(void)
{
	m_hBmpPlayer = NULL;
	x = 160;
	y = 490;
}


CPlayer::~CPlayer(void)
{
	::DeleteObject(m_hBmpPlayer);
	m_hBmpPlayer = NULL;
}

void CPlayer::InitPlayer(HINSTANCE hIns)
{
	m_hBmpPlayer = LoadBitmap(hIns,MAKEINTRESOURCE(IDB_PLAYER));
}

void CPlayer::MovePlayer(int FX)
{
	if(FX == VK_LEFT)
	{
		if(x > 0)
		x = x - 2;
	}
	if(FX == VK_RIGHT)
	{
		if(x < 320)
		x = x + 2;
	}
	if(FX == VK_UP)
	{
		if(y > 0)
		y = y - 2;
	}
	if(FX == VK_DOWN)
	{
		if(y < 490)
		y = y + 2;
	}
}


void CPlayer::ShowPlayer(HDC hdc)
{
	HDC hMenDC = CreateCompatibleDC(hdc);
	::SelectObject(hMenDC,m_hBmpPlayer);

	::BitBlt(hdc,x,y,60,60,hMenDC,0,0,SRCAND);
	::DeleteDC(hMenDC);
	hMenDC = NULL;
}

void CPlayer::SendGunner(HINSTANCE hIns,CGunnerBox& gunnerBox)
{
	//1.创建炮弹对象
	CGunner *pGunner = new CGunner;
	//2.初始化炮弹
	pGunner->GunnerInit(hIns,x+27,y-9);
	//3.添加到链表中
	gunnerBox.m_lstGunner.push_back(pGunner);
}