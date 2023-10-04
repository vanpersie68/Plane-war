#pragma once
#include "Sys.h"
#include"GunnerBox.h"
class CPlayer
{
public:
	HBITMAP m_hBmpPlayer;
	int x;
	int y;
public:
	CPlayer(void);
	~CPlayer(void);
public:
	void InitPlayer(HINSTANCE hIns);
	void MovePlayer(int FX);
	void ShowPlayer(HDC hdc);
	void SendGunner(HINSTANCE hIns,CGunnerBox& gunnerBox);
};

