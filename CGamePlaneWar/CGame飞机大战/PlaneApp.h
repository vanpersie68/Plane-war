#pragma once
#include "cgameapp.h"
#include"Back.h"
#include"Player.h"
#include"GunnerBox.h"
#include"Sys.h"
#include"FoePlaneBox.h"
#include"BlastFoePlaneBox.h"

class CPlaneApp :
	public CGameApp
{
public:
	CBack back;
	CPlayer player;
	CGunnerBox gunnerbox;
	CFoePlaneBox foeplanebox;
	CBlastFoePlaneBox blastplane;
public:
	CPlaneApp(void);
	~CPlaneApp(void);
public:
	virtual void OnCreateGame();	//需要 HINSTANCE实例的句柄
	virtual void OnGameDraw();		//需要 HWND窗口的句柄
	virtual void OnGameRun(WPARAM nTimerID);		//需要 WParam 这个定时器编号
	virtual void OnKeyDown(WPARAM nKey);		//需要 WParam 这个具体的按键
	void GunnerHitFoePlane();	//炮弹打敌人飞机
	bool IsGameOver();
};

