#pragma once
#include<Windows.h>

#define DECLARE(ThisClass)\
	CGameApp* CreateObject()\
	{\
		return new ThisClass;\
	}

class CGameApp
{
protected:
	HINSTANCE m_hIns;
	HWND m_hMainWnd;
public:
	CGameApp()
	{
		m_hIns = NULL;
		m_hMainWnd = NULL;
	}
	virtual ~CGameApp()
	{

	}
public:
	void SetHandle(HINSTANCE hIns,HWND hwnd)
	{
		m_hIns = hIns;
		m_hMainWnd = hwnd;
	}
public:
	virtual void OnCreateGame(){}	//��Ҫ HINSTANCEʵ���ľ��
	virtual void OnGameDraw(){}		//��Ҫ HWND���ڵľ��
	virtual void OnGameRun(WPARAM nTimerID){}		//��Ҫ WParam �����ʱ�����
	virtual void OnKeyDown(WPARAM nKey){}		//��Ҫ WParam �������İ���
	virtual void OnKeyUp(WPARAM nKey){}		//��Ҫ WParam �������İ���
	virtual void OnLButtonDown(POINT point){}	//��Ҫ һ������� ������ȡ��ͨ��LParam
	virtual void OnLButtonUp(POINT point){}	//��Ҫ һ������� ������ȡ��ͨ��LParam
	virtual void OnMouseMove(POINT point){}	//��Ҫ һ������� ������ȡ��ͨ��LParam
};