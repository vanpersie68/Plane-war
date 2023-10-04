#pragma once
#include"Sys.h"

class CGunner
{
public:
	HBITMAP m_hBmpGunner;
	int x;
	int y;
public:
	CGunner(void);
	~CGunner(void);
public:
	void GunnerInit(HINSTANCE hIns, int x1, int y1); //初始化炮弹‎()
	void GunnerMove();
	void GunnerShow(HDC hdc);
};

