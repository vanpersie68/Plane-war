#include "PlaneApp.h"

DECLARE(CPlaneApp)
CPlaneApp::CPlaneApp(void)
{

}

CPlaneApp::~CPlaneApp(void)
{

}

void CPlaneApp::OnCreateGame() //������Ϸ
{
	//1. ������ʼ��
	back.BackInit(m_hIns);

	//2.��ҷɻ���ʼ��
	player.InitPlayer(m_hIns);

	//3.�������еĶ�ʱ��
	::SetTimer(m_hMainWnd,BACK_MOVE_TIMER_ID,100,0); //���Ʊ����ƶ�
	::SetTimer(m_hMainWnd,PLAYER_MOVE_TIMER_ID,1,0); //������ҷɻ��ƶ�
	::SetTimer(m_hMainWnd,ALLGUNNER_MOVE_TIMER_ID,10,0); //���������ڵ��ƶ�
	::SetTimer(m_hMainWnd,PLAYER_SENDGUNNER_TIMER_ID,350,0); //���Ʒɻ������ڵ�
	::SetTimer(m_hMainWnd,CREATEFOEPLANE_TIMER_ID,1000,0); //�������˷ɻ�
	::SetTimer(m_hMainWnd,ALLFOEPLANE_MOVE_TIMER_ID,30,0); //���Ƶ��˷ɻ��ƶ�
	::SetTimer(m_hMainWnd,CHANGE_BLASTSHOWID_TIMER_ID,150,0); //�ı䱬ըЧ��
}

void CPlaneApp::OnGameDraw() //��ʾ��Ϸ���ػ�
{
	HDC hdc = GetDC(m_hMainWnd);
	HDC hMen = CreateCompatibleDC(hdc); //ͨ���ٴ���һ���հ׵ļ�����DC��������ɻ���˸�����⣨��������hMenDC�ķŵ�������hMen�ϣ�
	HBITMAP hBitmap = ::CreateCompatibleBitmap(hdc,380,550);	//����һ���հ׵�bitmap

	::SelectObject(hMen,hBitmap);
	//1. ��ʾ����
	back.BackShow(hMen);

	//2.��ʾ��ҷɻ�
	player.ShowPlayer(hMen);

	//3.��ʾ���е��ڵ�
	gunnerbox.AllGunnerShow(hMen);

	//4.��ʾ���е��˵ķɻ�
	foeplanebox.AllFoePlaneShow(hMen);

	//5.��ʾ���еı�ը�ķɻ�
	blastplane.AllBlastFoePlaneShow(hMen);

	::BitBlt(hdc,0,0,380,550,hMen,0,0,SRCCOPY);	//����������hMen�ķŵ������ϣ�
	::DeleteObject(hBitmap);
	hBitmap = NULL;
	::DeleteDC(hMen);
	hMen = NULL;
	::ReleaseDC(m_hMainWnd,hdc);
}

void CPlaneApp::OnGameRun(WPARAM nTimerID) //������Ϸ
{
	//1.�����ƶ�
	if(nTimerID == BACK_MOVE_TIMER_ID)
	{
		back.BackMove();
	}

	//��ҷɻ��ƶ�
	if(nTimerID == PLAYER_MOVE_TIMER_ID)
	{
		if(GetAsyncKeyState(VK_LEFT)) //GetAsyncKeyState ��ȡ���̰��µ�״̬
			player.MovePlayer(VK_LEFT);
		if(GetAsyncKeyState(VK_RIGHT))
			player.MovePlayer(VK_RIGHT);
		if(GetAsyncKeyState(VK_UP))
			player.MovePlayer(VK_UP);
		if(GetAsyncKeyState(VK_DOWN))
			player.MovePlayer(VK_DOWN);
	}

	//2.��ҷɻ������ڵ�
	if(nTimerID == PLAYER_SENDGUNNER_TIMER_ID)
	{
		player.SendGunner(m_hIns,gunnerbox);
	}

	//3.�����ڵ��ƶ�
	if(nTimerID == ALLGUNNER_MOVE_TIMER_ID)
	{
		gunnerbox.AllGunnerMove();
		this->GunnerHitFoePlane(); //3.1�ڵ�����˷ɻ�
	}

	//4.�������˷ɻ�
	if(nTimerID == CREATEFOEPLANE_TIMER_ID)
	{
		foeplanebox.CreateFoePlane(m_hIns);
	}

	//5.���е��˷ɻ��ƶ�
	if(nTimerID == ALLFOEPLANE_MOVE_TIMER_ID)
	{
		foeplanebox.AllFoePlaneMove();
		if(this->IsGameOver() == true) //5.1��Ϸ�Ƿ����
		{
			::KillTimer(m_hMainWnd,BACK_MOVE_TIMER_ID); 
			::KillTimer(m_hMainWnd,PLAYER_MOVE_TIMER_ID); 
			::KillTimer(m_hMainWnd,ALLGUNNER_MOVE_TIMER_ID); 
			::KillTimer(m_hMainWnd,PLAYER_SENDGUNNER_TIMER_ID); 
			::KillTimer(m_hMainWnd,CREATEFOEPLANE_TIMER_ID); 
			::KillTimer(m_hMainWnd,ALLFOEPLANE_MOVE_TIMER_ID); 
			::KillTimer(m_hMainWnd,CHANGE_BLASTSHOWID_TIMER_ID); 
			MessageBox(0,"GameOver","��ʾ",MB_OK);
		}
	}

	//6.�л���ը��Ч��ͼ
	if(nTimerID = CHANGE_BLASTSHOWID_TIMER_ID)
	{
		blastplane.ChangeShowID();
	}

	//�ػ�
	OnGameDraw();
}
	
void CPlaneApp::OnKeyDown(WPARAM nKey) //���Ƽ���
{
	
}

void CPlaneApp::GunnerHitFoePlane()
{
	bool bflag = false; //����ڵ��Ƿ�򵽵��˷ɻ�

	//�������е��ڵ�
	list<CGunner*>::iterator iteGun = gunnerbox.m_lstGunner.begin();

	while(iteGun != gunnerbox.m_lstGunner.end())
	{
		//�������еĵ��˷ɻ�
		list<CFoePlane*>::iterator itePlane = foeplanebox.m_lstFoePlane.begin();
		while(itePlane != foeplanebox.m_lstFoePlane.end())
		{
			//�ж��ڵ��Ƿ���е��˷ɻ�
			if((*itePlane)->IsGunnerHitFoePlane(*iteGun) == true)
			{
				bflag = true;
				//ɾ���ڵ�
				delete(*iteGun);
				iteGun = gunnerbox.m_lstGunner.erase(iteGun);

				//���˷ɻ���Ѫ
				(*itePlane)->DownBlood();

				//�ж��Ƿ�ը
				if((*itePlane)->IsBoom() == true)
				{
					//�ѵ��˷ɻ��ŵ���ը���������������ʾЧ��
					blastplane.m_lstBlastFoePlane.push_back(*itePlane);

					//ɾ����ը�ķɻ�
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
