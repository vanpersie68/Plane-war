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
	virtual void OnCreateGame(){}	//需要 HINSTANCE实例的句柄
	virtual void OnGameDraw(){}		//需要 HWND窗口的句柄
	virtual void OnGameRun(WPARAM nTimerID){}		//需要 WParam 这个定时器编号
	virtual void OnKeyDown(WPARAM nKey){}		//需要 WParam 这个具体的按键
	virtual void OnKeyUp(WPARAM nKey){}		//需要 WParam 这个具体的按键
	virtual void OnLButtonDown(POINT point){}	//需要 一个坐标点 坐标点获取是通过LParam
	virtual void OnLButtonUp(POINT point){}	//需要 一个坐标点 坐标点获取是通过LParam
	virtual void OnMouseMove(POINT point){}	//需要 一个坐标点 坐标点获取是通过LParam
};