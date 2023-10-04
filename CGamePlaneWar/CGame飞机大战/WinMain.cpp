#include<Windows.h> //windows API函数
#include<time.h>
#include"CGameApp.h"

//消息的处理函数
LRESULT CALLBACK WindowProc(HWND hwnd,UINT uMsg,WPARAM wParam,LPARAM lParam);
HINSTANCE hIns = 0;

	//调用约定 CALLBACK
int CALLBACK WinMain(HINSTANCE hInstance,	 //当前应用程序实例的句柄
					 HINSTANCE hPreInstance, //前一个应用程序实例的句柄
					 LPSTR lpCmdLine,		 //命令行参数
					 int nShowCmd)			 //默认的窗口显示方式
{
	srand((unsigned int)time(0));
	MSG msg; //装消息的
	hIns = hInstance;
	//----------------------创建窗口过程-----------------------------------
	//  1. 设计
	WNDCLASSEX wndclass;							//一个窗口类的结构体
	wndclass.cbClsExtra = 0;						//是否分配额外的空间
	wndclass.cbWndExtra = 0;						//是否分配额外的空间
	wndclass.cbSize = sizeof(wndclass);				//结构体大小
	wndclass.hbrBackground = (HBRUSH)COLOR_WINDOW;	//窗口的背景颜色（HBrush是将COLOR_WINDOW强转）
	wndclass.hCursor = 0;							//光标的句柄
	wndclass.hIcon = 0;								//应用程序图标的句柄
	wndclass.hIconSm = 0;							//修改窗口左上角 应用程序小图标的句柄
	wndclass.hInstance = hInstance;					//实例的句柄
	wndclass.lpfnWndProc = &WindowProc;				//窗口消息的处理函数
	wndclass.lpszClassName = "lele";				//注册窗口类的名字
	wndclass.lpszMenuName = 0;						//菜单的名字
	wndclass.style = CS_HREDRAW|CS_VREDRAW;			//窗口类的样式 = 水平刷新|垂直刷新

	// 2.  注册(分配空间)
	if(RegisterClassEx(&wndclass) == FALSE)	//失败
	{
		MessageBox(0,"注册失败","提示",MB_OK); //弹出一个提示框
		return 0;
	}
	//  3.  创建
	HWND hwnd = CreateWindow("lele","我的窗口O(∩_∩)O哈哈~",WS_OVERLAPPEDWINDOW,0,0,380+16,550+38,0,0,hInstance,0);										
	if(hwnd == 0)
	{
		MessageBox(0,"创建失败","提示",MB_OK);
		return 0;	
	}
	//  4.  显示窗口
	ShowWindow(hwnd,SW_SHOW);
	//---------------------------创建窗口过程------------------------------------------------



	//  5. 消息循环-------------------------------------------
	while(GetMessage(&msg,0,0,0))  //GetMessage 在消息队列取消息，（0，0，0，）表示所有窗口的所有消息
	{
		TranslateMessage(&msg);	   //翻译
		DispatchMessage(&msg);	   //分发（调用消息的处理函数）
	}

	return 0;
}


//=================================处理消息========================================================
// hwnd 消息对应的窗口		uMsg 消息种类		wParam lParam 这个消息带过来的附加信息

CGameApp * pApp = 0;
CGameApp* CreateObject();  // 创建对象的函数

LRESULT CALLBACK WindowProc(HWND hwnd,UINT uMsg,WPARAM wParam,LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_CREATE:
		{
			pApp = CreateObject();		//创建一个游戏的子
			if(pApp != NULL)
			{
				pApp->SetHandle(hIns,hwnd); //设置句柄
				pApp->OnCreateGame();		//初始化游戏，加载资源
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
	case WM_CLOSE:				//关闭的消息
		delete pApp;
		pApp = NULL;
		PostQuitMessage(0);		//发送一个退出的消息
		break;
	}

	return DefWindowProc( hwnd, uMsg, wParam, lParam); //默认的消息的处理
}