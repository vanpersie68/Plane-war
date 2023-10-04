#pragma once
#include"Sys.h"
#include"Gunner.h"
class CGunnerBox
{
public:
	list<CGunner*>m_lstGunner;
public:
	CGunnerBox(void);
	~CGunnerBox(void);
public:
	void AllGunnerMove();
	void AllGunnerShow(HDC hdc);
};

