#pragma once
#include"Sys.h"
#include"FoePlane.h"

class CBlastFoePlaneBox
{
public:
	list<CFoePlane*>m_lstBlastFoePlane;
public:
	CBlastFoePlaneBox(void);
	~CBlastFoePlaneBox(void);
public:
	void AllBlastFoePlaneShow(HDC hdc);
	void ChangeShowID();
};

