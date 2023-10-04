#pragma once
#include"FoePlane.h"
#include"Sys.h"

class CFoePlaneBox
{
public:
	list<CFoePlane*>m_lstFoePlane;
public:
	CFoePlaneBox(void);
	~CFoePlaneBox(void);
public:
	void AllFoePlaneMove(); //所有飞机移动‎()
	void AllFoePlaneShow(HDC hdc); //显示所有敌人飞机‎()
	void CreateFoePlane(HINSTANCE hIns); //创建敌人飞机‎()
};

