#pragma once
#include"Sys.h"
#include"GunnerBox.h"
#include"Player.h"
class CFoePlane
{
public:
	HBITMAP m_hBmpFoePlane;
	int m_nBlood;
	int m_nShowID;
	int x;
	int y;
public:
	CFoePlane(void);
	~CFoePlane(void);
public:
	void DownBlood();
	bool IsBoom();
public:
	virtual bool IsGunnerHitFoePlane(const CGunner* pGunner) = 0; //是否被炮弹击中‎()
	virtual bool IsHitPlayer(const CPlayer& plane) = 0; //是否撞玩家飞机‎()
	virtual void InitFoePlane(HINSTANCE hIns) = 0; //初始化敌人飞机‎()
	virtual void MoveFoePlane() = 0; //飞机移动‎()
	virtual void ShowFoePlane(HDC hdc)=0;   //贴图()
};

