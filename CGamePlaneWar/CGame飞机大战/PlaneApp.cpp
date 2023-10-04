#include "PlaneApp.h"

DECLARE(CPlaneApp)
CPlaneApp::CPlaneApp(void)
{

}

CPlaneApp::~CPlaneApp(void)
{

}

void CPlaneApp::OnCreateGame() //创建游戏
{
	//1. 背景初始化
	back.BackInit(m_hIns);

	//2.玩家飞机初始化
	player.InitPlayer(m_hIns);

	//3.启动所有的定时器
	::SetTimer(m_hMainWnd,BACK_MOVE_TIMER_ID,100,0); //控制背景移动
	::SetTimer(m_hMainWnd,PLAYER_MOVE_TIMER_ID,1,0); //控制玩家飞机移动
	::SetTimer(m_hMainWnd,ALLGUNNER_MOVE_TIMER_ID,10,0); //控制所有炮弹移动
	::SetTimer(m_hMainWnd,PLAYER_SENDGUNNER_TIMER_ID,350,0); //控制飞机发射炮弹
	::SetTimer(m_hMainWnd,CREATEFOEPLANE_TIMER_ID,1000,0); //创建敌人飞机
	::SetTimer(m_hMainWnd,ALLFOEPLANE_MOVE_TIMER_ID,30,0); //控制敌人飞机移动
	::SetTimer(m_hMainWnd,CHANGE_BLASTSHOWID_TIMER_ID,150,0); //改变爆炸效果
}

void CPlaneApp::OnGameDraw() //显示游戏、重绘
{
	HDC hdc = GetDC(m_hMainWnd);
	HDC hMen = CreateCompatibleDC(hdc); //通过再创建一个空白的兼容性DC，来解决飞机闪烁的问题（将兼容性hMenDC的放到兼容性hMen上）
	HBITMAP hBitmap = ::CreateCompatibleBitmap(hdc,380,550);	//制作一个空白的bitmap

	::SelectObject(hMen,hBitmap);
	//1. 显示背景
	back.BackShow(hMen);

	//2.显示玩家飞机
	player.ShowPlayer(hMen);

	//3.显示所有的炮弹
	gunnerbox.AllGunnerShow(hMen);

	//4.显示所有敌人的飞机
	foeplanebox.AllFoePlaneShow(hMen);

	//5.显示所有的爆炸的飞机
	blastplane.AllBlastFoePlaneShow(hMen);

	::BitBlt(hdc,0,0,380,550,hMen,0,0,SRCCOPY);	//（将兼容性hMen的放到窗口上）
	::DeleteObject(hBitmap);
	hBitmap = NULL;
	::DeleteDC(hMen);
	hMen = NULL;
	::ReleaseDC(m_hMainWnd,hdc);
}

void CPlaneApp::OnGameRun(WPARAM nTimerID) //运行游戏
{
	//1.背景移动
	if(nTimerID == BACK_MOVE_TIMER_ID)
	{
		back.BackMove();
	}

	//玩家飞机移动
	if(nTimerID == PLAYER_MOVE_TIMER_ID)
	{
		if(GetAsyncKeyState(VK_LEFT)) //GetAsyncKeyState 获取键盘按下的状态
			player.MovePlayer(VK_LEFT);
		if(GetAsyncKeyState(VK_RIGHT))
			player.MovePlayer(VK_RIGHT);
		if(GetAsyncKeyState(VK_UP))
			player.MovePlayer(VK_UP);
		if(GetAsyncKeyState(VK_DOWN))
			player.MovePlayer(VK_DOWN);
	}

	//2.玩家飞机发射炮弹
	if(nTimerID == PLAYER_SENDGUNNER_TIMER_ID)
	{
		player.SendGunner(m_hIns,gunnerbox);
	}

	//3.所有炮弹移动
	if(nTimerID == ALLGUNNER_MOVE_TIMER_ID)
	{
		gunnerbox.AllGunnerMove();
		this->GunnerHitFoePlane(); //3.1炮弹打敌人飞机
	}

	//4.创建敌人飞机
	if(nTimerID == CREATEFOEPLANE_TIMER_ID)
	{
		foeplanebox.CreateFoePlane(m_hIns);
	}

	//5.所有敌人飞机移动
	if(nTimerID == ALLFOEPLANE_MOVE_TIMER_ID)
	{
		foeplanebox.AllFoePlaneMove();
		if(this->IsGameOver() == true) //5.1游戏是否结束
		{
			::KillTimer(m_hMainWnd,BACK_MOVE_TIMER_ID); 
			::KillTimer(m_hMainWnd,PLAYER_MOVE_TIMER_ID); 
			::KillTimer(m_hMainWnd,ALLGUNNER_MOVE_TIMER_ID); 
			::KillTimer(m_hMainWnd,PLAYER_SENDGUNNER_TIMER_ID); 
			::KillTimer(m_hMainWnd,CREATEFOEPLANE_TIMER_ID); 
			::KillTimer(m_hMainWnd,ALLFOEPLANE_MOVE_TIMER_ID); 
			::KillTimer(m_hMainWnd,CHANGE_BLASTSHOWID_TIMER_ID); 
			MessageBox(0,"GameOver","提示",MB_OK);
		}
	}

	//6.切换爆炸的效果图
	if(nTimerID = CHANGE_BLASTSHOWID_TIMER_ID)
	{
		blastplane.ChangeShowID();
	}

	//重绘
	OnGameDraw();
}
	
void CPlaneApp::OnKeyDown(WPARAM nKey) //控制键盘
{
	
}

void CPlaneApp::GunnerHitFoePlane()
{
	bool bflag = false; //标记炮弹是否打到敌人飞机

	//遍历所有的炮弹
	list<CGunner*>::iterator iteGun = gunnerbox.m_lstGunner.begin();

	while(iteGun != gunnerbox.m_lstGunner.end())
	{
		//遍历所有的敌人飞机
		list<CFoePlane*>::iterator itePlane = foeplanebox.m_lstFoePlane.begin();
		while(itePlane != foeplanebox.m_lstFoePlane.end())
		{
			//判断炮弹是否击中敌人飞机
			if((*itePlane)->IsGunnerHitFoePlane(*iteGun) == true)
			{
				bflag = true;
				//删除炮弹
				delete(*iteGun);
				iteGun = gunnerbox.m_lstGunner.erase(iteGun);

				//敌人飞机掉血
				(*itePlane)->DownBlood();

				//判断是否爆炸
				if((*itePlane)->IsBoom() == true)
				{
					//把敌人飞机放到爆炸盒子这个链表中显示效果
					blastplane.m_lstBlastFoePlane.push_back(*itePlane);

					//删除爆炸的飞机
					foeplanebox.m_lstFoePlane.erase(itePlane);
				}
				break;
			}
			itePlane++;
		}
		if(bflag == false)
			iteGun++;
		else
			bflag = false;
	}
}

bool CPlaneApp::IsGameOver()
{
	list<CFoePlane*>::iterator ite = foeplanebox.m_lstFoePlane.begin();
	while(ite != foeplanebox.m_lstFoePlane.end())
	{
		if((*ite)->IsHitPlayer(player) == false)
			return true;
		++ite;
	}
	return false;
}
