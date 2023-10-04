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
	virtual void OnCreateGame();	//��Ҫ HINSTANCEʵ���ľ��
	virtual void OnGameDraw();		//��Ҫ HWND���ڵľ��
	virtual void OnGameRun(WPARAM nTimerID);		//��Ҫ WParam �����ʱ�����
	virtual void OnKeyDown(WPARAM nKey);		//��Ҫ WParam �������İ���
	void GunnerHitFoePlane();	//�ڵ�����˷ɻ�
	bool IsGameOver();
};

