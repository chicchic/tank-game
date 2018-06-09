
/*
 *	坦克大战主程序，编码时功能尽量编写成函数再调用，以免在mypaint里面代码太多
 */

#include "stdafx.h"
#include <stdio.h>

#include "mmsystem.h"//导入声音头文件
#pragma comment(lib,"winmm.lib")//导入声音头文件库

HINSTANCE hInst;
HBITMAP  bg,start,tankTopImg,tankLeftImg,tankRightImg,tankBottomImg;						//图片
HDC		hdc, mdc, bufdc;
HWND	hWnd;
DWORD	tPre, tNow;						//控制刷新频率
bool isStart = false;				//游戏开始

ATOM				MyRegisterClass(HINSTANCE hInstance);
BOOL				InitInstance(HINSTANCE, int);
LRESULT CALLBACK	WndProc(HWND, UINT, WPARAM, LPARAM);
void				MyPaint(HDC hdc);		
void				StartPaint(HDC hdc);






int APIENTRY WinMain(HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	LPSTR     lpCmdLine,
	int       nCmdShow)
{
	MSG msg;

	MyRegisterClass(hInstance);

	if (!InitInstance(hInstance, nCmdShow))
	{
		return FALSE;
	}
	GetMessage(&msg, NULL, 0, 0);
	while (msg.message != WM_QUIT)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else
		{
			tNow = GetTickCount();
			if (tNow - tPre >= 40)				//刷新频率
				if(isStart)				//游戏已经开始
					MyPaint(hdc);
				else
					StartPaint(hdc);			//游戏未开始
		}
	}

	return msg.wParam;
}

//注册窗口类，不需要明白原理
ATOM MyRegisterClass(HINSTANCE hInstance)
{
	WNDCLASSEX wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);
	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = (WNDPROC)WndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hInstance;
	wcex.hIcon = NULL;
	wcex.hCursor = NULL;
	wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wcex.lpszMenuName = NULL;
	wcex.lpszClassName = "canvas";
	wcex.hIconSm = NULL;

	return RegisterClassEx(&wcex);
}

//初始化
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
	HBITMAP bmp;
	hInst = hInstance;

	hWnd = CreateWindow("canvas", "Window", WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, NULL, NULL, hInstance, NULL);

	if (!hWnd)
	{
		return FALSE;
	}

	MoveWindow(hWnd, 10, 10, 640, 480, true);
	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	hdc = GetDC(hWnd);
	mdc = CreateCompatibleDC(hdc);
	bufdc = CreateCompatibleDC(hdc);

	bmp = CreateCompatibleBitmap(hdc, 640, 480);
	SelectObject(mdc, bmp);
		

	//加载图片
	start = (HBITMAP)LoadImage(NULL, "start.bmp", IMAGE_BITMAP, 650, 450, LR_LOADFROMFILE);			//开始界面
	//bg = (HBITMAP)LoadImage(NULL, "bg.bmp", IMAGE_BITMAP, 650, 450, LR_LOADFROMFILE);				//背景图
	tankTopImg = (HBITMAP)LoadImage(NULL, "top.bmp", IMAGE_BITMAP, 30, 30, LR_LOADFROMFILE);				//坦克
	tankLeftImg = (HBITMAP)LoadImage(NULL, "left.bmp", IMAGE_BITMAP, 30, 30, LR_LOADFROMFILE);				
	tankRightImg = (HBITMAP)LoadImage(NULL, "right.bmp", IMAGE_BITMAP, 30, 30, LR_LOADFROMFILE);				
	tankBottomImg = (HBITMAP)LoadImage(NULL, "bottom.bmp", IMAGE_BITMAP, 30, 30, LR_LOADFROMFILE);				

	//初始化的坦克
	Tank myTank(100,100,RIGHT);


	MyPaint(hdc);					//调用绘图函数

	return TRUE;
}

void StartPaint(HDC hdc)
{	
	if(isStart == false){
		//贴开始界面
		SelectObject(bufdc, start);
		BitBlt(mdc, 0, 0, 650, 450, bufdc, 0, 0, SRCCOPY);		
		BitBlt(hdc, 0, 0, 650, 450, mdc, 0, 0, SRCCOPY);
		tPre = GetTickCount();
	}	
}
void MyPaint(HDC hdc)
{				
	if(isStart == false)
		return;
	//绘图
	//SelectObject(bufdc, bg);
	//BitBlt(mdc, 0, 0, 650, 450, bufdc, 0, 0, SRCCOPY);					

	//画己方坦克
	SelectObject(bufdc, tankLeftImg);
	BitBlt(mdc, 0, 0, 30, 30, bufdc, 0, 0, SRCCOPY);					


	
	BitBlt(hdc, 0, 0, 650, 450, mdc, 0, 0, SRCCOPY);
	tPre = GetTickCount();

}


//事件处理函数
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
		//按下键盘开始游戏
	case WM_LBUTTONDOWN:  		
		if(isStart == true)
			break;								
		isStart = true;	
		PlaySound("music.wav", NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);	    //播放背景音乐				
		break;

	case WM_KEYDOWN:
		switch (wParam)
		{
		case VK_ESCAPE:
			PostQuitMessage(0);
			break;

		case VK_UP:			
			break;
		case VK_DOWN:
			
			break;
		case VK_LEFT:
			
			break;
		case VK_RIGHT:
			

			break;
		}
		break;
	case WM_DESTROY:
		int i;

		DeleteDC(mdc);
		DeleteDC(bufdc);
		DeleteObject(bg);
		ReleaseDC(hWnd, hdc);

		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}
