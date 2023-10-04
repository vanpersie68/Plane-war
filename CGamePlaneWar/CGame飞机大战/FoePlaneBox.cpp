#include "FoePlaneBox.h"
#include "BigFoePlane.h"
#include "MidFoePlane.h"
#include "SmallFoePlane.h"

CFoePlaneBox::CFoePlaneBox(void)
{
}


CFoePlaneBox::~CFoePlaneBox(void)
{
	list<CFoePlane*>::iterator ite = m_lstFoePlane.begin();
	while(ite != m_lstFoePlane.end())
	{
		delete(*ite);
		ite++;
	}
}

void CFoePlaneBox::AllFoePlaneMove()//所有飞机移动‎()
{
	list<CFoePlane*>::iterator ite = m_lstFoePlane.begin();
	while(ite != m_lstFoePlane.end())
	{
		if((*ite)->y > 550)
		{
			delete(*ite);
			ite = m_lstFoePlane.erase(ite);
		}
		else
		{
			(*ite)->MoveFoePlane();
			ite++;
		}
	}
}

void CFoePlaneBox::AllFoePlaneShow(HDC hdc) //显示所有敌人飞机‎()
{
	list<CFoePlane*>::iterator ite = m_lstFoePlane.begin();
	while(ite != m_lstFoePlane.end())
	{
		(*ite)->ShowFoePlane(hdc);
		ite++;
	}
}

void CFoePlaneBox::CreateFoePlane(HINSTANCE hIns) //创建敌人飞机‎()
{
	CFoePlane *pFoePlane = NULL;

	int index = rand()%12;
	if(index >= 0 && index <= 1) //出现大号飞机
	{
		pFoePlane = new CBigFoePlane;
	}
	if(index >= 2 && index <= 5) //出现中号飞机
	{
		pFoePlane = new CMidFoePlane;
	}
	if(index >= 6 && index <= 12) //出现小号飞机
	{
		pFoePlane = new CSmallFoePlane;
	}

	//初始化敌人飞机
	pFoePlane->InitFoePlane(hIns);

	//添加到链表中
	m_lstFoePlane.push_back(pFoePlane);
}