#pragma once
#include "foeplane.h"
class CMidFoePlane :
	public CFoePlane
{
public:
	CMidFoePlane(void);
	~CMidFoePlane(void);
public:
	virtual bool IsGunnerHitFoePlane(const CGunner* pGunner);	//是否被炮弹击中‎()
	virtual bool IsHitPlayer(const CPlayer& plane);				//是否撞玩家飞机‎()
	virtual void InitFoePlane(HINSTANCE hIns) ;					//初始化敌人飞机‎()
	virtual void MoveFoePlane();								//飞机移动‎()
	virtual void ShowFoePlane(HDC hdc);							//贴图()
};

