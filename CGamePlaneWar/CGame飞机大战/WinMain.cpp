#include<Windows.h> //windows API����
#include<time.h>
#include"CGameApp.h"

//��Ϣ�Ĵ�����
LRESULT CALLBACK WindowProc(HWND hwnd,UINT uMsg,WPARAM wParam,LPARAM lParam);
HINSTANCE hIns = 0;

	//����Լ�� CALLBACK
int CALLBACK WinMain(HINSTANCE hInstance,	 //��ǰӦ�ó���ʵ���ľ��
					 HINSTANCE hPreInstance, //ǰһ��Ӧ�ó���ʵ���ľ��
					 LPSTR lpCmdLine,		 //�����в���
					 int nShowCmd)			 //Ĭ�ϵĴ�����ʾ��ʽ
{
	srand((unsigned int)time(0));
	MSG msg; //װ��Ϣ��
	hIns = hInstance;
	//----------------------�������ڹ���-----------------------------------
	//  1. ���
	WNDCLASSEX wndclass;							//һ��������Ľṹ��
	wndclass.cbClsExtra = 0;						//�Ƿ�������Ŀռ�
	wndclass.cbWndExtra = 0;						//�Ƿ�������Ŀռ�
	wndclass.cbSize = sizeof(wndclass);				//�ṹ���С
	wndclass.hbrBackground = (HBRUSH)COLOR_WINDOW;	//���ڵı�����ɫ��HBrush�ǽ�COLOR_WINDOWǿת��
	wndclass.hCursor = 0;							//���ľ��
	wndclass.hIcon = 0;								//Ӧ�ó���ͼ��ľ��
	wndclass.hIconSm = 0;							//�޸Ĵ������Ͻ� Ӧ�ó���Сͼ��ľ��
	wndclass.hInstance = hInstance;					//ʵ���ľ��
	wndclass.lpfnWndProc = &WindowProc;				//������Ϣ�Ĵ�����
	wndclass.lpszClassName = "lele";				//ע�ᴰ���������
	wndclass.lpszMenuName = 0;						//�˵�������
	wndclass.style = CS_HREDRAW|CS_VREDRAW;			//���������ʽ = ˮƽˢ��|��ֱˢ��

	// 2.  ע��(����ռ�)
	if(RegisterClassEx(&wndclass) == FALSE)	//ʧ��
	{
		MessageBox(0,"ע��ʧ��","��ʾ",MB_OK); //����һ����ʾ��
		return 0;
	}
	//  3.  ����
	HWND hwnd = CreateWindow("lele","�ҵĴ���O(��_��)O����~",WS_OVERLAPPEDWINDOW,0,0,380+16,550+38,0,0,hInstance,0);										
	if(hwnd == 0)
	{
		MessageBox(0,"����ʧ��","��ʾ",MB_OK);
		return 0;	
	}
	//  4.  ��ʾ����
	ShowWindow(hwnd,SW_SHOW);
	//---------------------------�������ڹ���------------------------------------------------



	//  5. ��Ϣѭ��-------------------------------------------
	while(GetMessage(&msg,0,0,0))  //GetMessage ����Ϣ����ȡ��Ϣ����0��0��0������ʾ���д��ڵ�������Ϣ
	{
		TranslateMessage(&msg);	   //����
		DispatchMessage(&msg);	   //�ַ���������Ϣ�Ĵ�������
	}

	return 0;
}


//=================================������Ϣ========================================================
// hwnd ��Ϣ��Ӧ�Ĵ���		uMsg ��Ϣ����		wParam lParam �����Ϣ�������ĸ�����Ϣ

CGameApp * pApp = 0;
CGameApp* CreateObject();  // ��������ĺ���

LRESULT CALLBACK WindowProc(HWND hwnd,UINT uMsg,WPARAM wParam,LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_CREATE:
		{
			pApp = CreateObject();		//����һ����Ϸ����
			if(pApp != NULL)
			{
				pApp->SetHandle(hIns,hwnd); //���þ��
				pApp->OnCreateGame();		//��ʼ����Ϸ��������Դ
			}
		}
		break;
	case WM_PAINT:
		{
			if(pApp != NULL)
			{
				pApp->OnGameDraw();
			}
		}
		break;
	case WM_TIMER:
		{
			if(pApp != NULL)
			{
				pApp->OnGameRun(wParam);
			}
		}
		break;
	case WM_KEYDOWN:
		{
			if(pApp != NULL)
			{
				pApp->OnKeyDown(wParam);
			}
		}
		break;
	case WM_KEYUP:
		{
			if(pApp != NULL)
			{
				pApp->OnKeyUp(wParam);
			}
		}
		break;
	case WM_LBUTTONDOWN:
		{
			if(pApp != NULL)
			{
				POINT point;
				point.x = LOWORD(lParam);
				point.y = HIWORD(lParam);

				pApp->OnLButtonDown(point);
			}
		}
		break;
	case WM_LBUTTONUP:
		{
			if(pApp != NULL)
			{
				POINT point;
				point.x = LOWORD(lParam);
				point.y = HIWORD(lParam);

				pApp->OnLButtonUp(point);
			}
		}
		break;
	case WM_MOUSEMOVE:
		{
			if(pApp != NULL)
			{
				POINT point;
				point.x = LOWORD(lParam);
				point.y = HIWORD(lParam);

				pApp->OnMouseMove(point);
			}
		}
		break;
	case WM_CLOSE:				//�رյ���Ϣ
		delete pApp;
		pApp = NULL;
		PostQuitMessage(0);		//����һ���˳�����Ϣ
		break;
	}

	return DefWindowProc( hwnd, uMsg, wParam, lParam); //Ĭ�ϵ���Ϣ�Ĵ���
}