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
			//�ڵ����磬ɾ������ڵ�
			delete(*ite);
			ite = m_lstGunner.erase(ite); //��������ɾ������ڵ㣬��¼��һ���ڵ�(��Ϊɾ����������Զ���ת����һ�������Բ���ite++,���������һ���ڵ�)
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