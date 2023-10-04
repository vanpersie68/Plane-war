#include "GunnerBox.h"


CGunnerBox::CGunnerBox(void)
{
}


CGunnerBox::~CGunnerBox(void)
{
	list<CGunner*>::iterator ite = m_lstGunner.begin();
	while(ite != m_lstGunner.end())
	{
		delete(*ite);
		ite++;
	}
}

void CGunnerBox::AllGunnerMove()
{
	list<CGunner*>::iterator ite = m_lstGunner.begin();
	while(ite != m_lstGunner.end())
	{
		if((*ite)->y < 0)
		{
			//炮弹出界，删除这个炮弹
			delete(*ite);
			ite = m_lstGunner.erase(ite); //在链表中删除这个节点，记录下一个炮弹(因为删除后迭代器自动跳转到下一个，所以不用ite++,否则会跳过一个节点)
		}
		else
		{
			(*ite)->GunnerMove();
			ite++;
		}
	}
}

void CGunnerBox::AllGunnerShow(HDC hdc)
{
	list<CGunner*>::iterator ite = m_lstGunner.begin();
	while(ite != m_lstGunner.end())
	{
		(*ite)->GunnerShow(hdc);
		ite++;
	}
}