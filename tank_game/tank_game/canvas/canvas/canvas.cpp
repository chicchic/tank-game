
/*
 *	̹�˴�ս�����򣬱���ʱ���ܾ�����д�ɺ����ٵ��ã�������mypaint�������̫��
 */

#include "stdafx.h"
#include <stdio.h>

#include "mmsystem.h"//��������ͷ�ļ�
#pragma comment(lib,"winmm.lib")//��������ͷ�ļ���

HINSTANCE hInst;
HBITMAP  bg,start,tankImg[4],bullet;						//ͼƬ
HDC		hdc, mdc, bufdc;
HWND	hWnd;
DWORD	tPre, tNow;						//����ˢ��Ƶ��
bool isStart = false;				//��Ϸ��ʼ

ATOM				MyRegisterClass(HINSTANCE hInstance);
BOOL				InitInstance(HINSTANCE, int);
LRESULT CALLBACK	WndProc(HWND, UINT, WPARAM, LPARAM);
void				MyPaint(HDC hdc);		
void				StartPaint(HDC hdc);


//Ϊ������ʱ��Ϊȫ�ֱ���
//��ʼ����̹��
Tank myTank(100,100,LEFT);				//define left 2



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
			if (tNow - tPre >= 40){				//ˢ��Ƶ��
				if(isStart)				//��Ϸ�Ѿ���ʼ
					MyPaint(hdc);
				else
					StartPaint(hdc);			//��Ϸδ��ʼ
			}
		}
	}

	return msg.wParam;
}

//ע�ᴰ���࣬����Ҫ����ԭ��
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

//��ʼ��
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
		

	//����ͼƬ
	start = (HBITMAP)LoadImage(NULL, "start.bmp", IMAGE_BITMAP, 650, 450, LR_LOADFROMFILE);			//��ʼ����
	//bg = (HBITMAP)LoadImage(NULL, "bg.bmp", IMAGE_BITMAP, 650, 450, LR_LOADFROMFILE);				//����ͼ

	//�������Ҷ�Ӧ 0 1 2 3 
	tankImg[0] = (HBITMAP)LoadImage(NULL, "top.bmp", IMAGE_BITMAP, 30, 30, LR_LOADFROMFILE);				//̹��
	tankImg[2] = (HBITMAP)LoadImage(NULL, "left.bmp", IMAGE_BITMAP, 30, 30, LR_LOADFROMFILE);				
	tankImg[3] = (HBITMAP)LoadImage(NULL, "right.bmp", IMAGE_BITMAP, 30, 30, LR_LOADFROMFILE);				
	tankImg[1] = (HBITMAP)LoadImage(NULL, "bottom.bmp", IMAGE_BITMAP, 30, 30, LR_LOADFROMFILE);				
	bullet = (HBITMAP)LoadImage(NULL, "bullet.bmp", IMAGE_BITMAP, 10, 10, LR_LOADFROMFILE);				
	bg = (HBITMAP)LoadImage(NULL, "bg.bmp", IMAGE_BITMAP, 650, 450, LR_LOADFROMFILE);				//����		


	MyPaint(hdc);					//���û�ͼ����

	return TRUE;
}

void StartPaint(HDC hdc)
{	
	if(isStart == false){
		//����ʼ����
		SelectObject(bufdc, start);
		BitBlt(mdc, 0, 0, 650, 450, bufdc, 0, 0, SRCCOPY);		
		BitBlt(hdc, 0, 0, 650, 450, mdc, 0, 0, SRCCOPY);
		tPre = GetTickCount();
		printf("111\n");
	}	
}
void MyPaint(HDC hdc)
{				
	if(isStart == false)
		return;
	
	//��ͼ
	SelectObject(bufdc, bg);
	BitBlt(mdc, 0, 0, 650, 450, bufdc, 0, 0, SRCCOPY);					


	/*
	 * ����̹�ˣ��������޸ı���ͼ����Ҫ�޸�̹��ͼ��
	 */
	int myDirection = myTank.GetDirection();			//̹�˷���
	int myPositionX = myTank.GetX();			//̹��λ��
	int myPositionY = myTank.GetY();			//̹��λ��

	SelectObject(bufdc, tankImg[myDirection]);
	BitBlt(mdc, myPositionX, myPositionY, 30, 30, bufdc, 0, 0, SRCCOPY);					
	//������̹���ӵ�
	//int dir = myTank.GetDirection();
	Bullet *b = myTank.GetBullet();			//�ӵ�����	
	int x= myTank.GetX();
	int y = myTank.GetY();	
	int speed = 4;				//�ӵ��ٶ�
	for(int i = 0;i < 20;i++){				//�����ӵ�		
		Bullet temp = b[i];			
		if(temp.exist == false)
			continue;
		int bx = temp.GetX();				//�ӵ�������
		int by = temp.GetY();				//�ӵ�������
		int dir = temp.GetDir();			//�ӵ�����
		if(dir == 0){			//top
			by -= speed;
			if(by<=0||by>=450){				//�ӵ�Խ��
				b[i].exist = false;
				continue;
			}
			b[i].SetY(by);
		}
		if(dir == 1){			//��
			by += speed;
			if(by<=0||by>=450){				//�ӵ�Խ��
				b[i].exist = false;
				continue;
			}
			b[i].SetY(by);
		}
		if(dir == 2){			//��
			bx -= speed;
			if(bx<=0||bx>=650){				//�ӵ�Խ��
				b[i].exist = false;
				continue;
			}
			b[i].SetX(bx);
		}
		if(dir == 3){			//��
			bx += speed;
			if(bx<=0||bx>=650){				//�ӵ�Խ��
				b[i].exist = false;
				continue;
			}
			b[i].SetX(bx);
		}

		//���ӵ�
		SelectObject(bufdc, bullet);
		BitBlt(mdc, bx, by, 10, 10, bufdc, 0, 0, SRCCOPY);					
	}




	//
	BitBlt(hdc, 0, 0, 650, 450, mdc, 0, 0, SRCCOPY);
	tPre = GetTickCount();

}


//�¼�������
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
		//���¼��̿�ʼ��Ϸ
		case WM_LBUTTONDOWN:  		
			if(isStart == true)
				break;								
			isStart = true;	
			PlaySound("music.wav", NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);	    //���ű�������				
			break;

		case WM_KEYDOWN:
			switch (wParam)
			{
				case VK_ESCAPE:{
					PostQuitMessage(0);
				}
				break;
			
				//̹���ƶ�
				case VK_UP:		{	
					myTank.SetDirection(TOP);
					int y = myTank.GetY();
					y -= 5;				//�ƶ��ٶ�
					if(y <= 0)	y = 0;
					if(y >= 450) y = 450;
					myTank.SetY(y);
					}
					break;
				case VK_DOWN:
					{	
					myTank.SetDirection(BOTTOM);
					int y = myTank.GetY();
					y += 5;				//�ƶ��ٶ�
					if(y <= 0)	y = 0;
					if(y >= 420) y = 420;
					myTank.SetY(y);
					}
					break;
				case VK_LEFT:
					{	
					myTank.SetDirection(LEFT);
					int x = myTank.GetX();
					x -= 5;				//�ƶ��ٶ�
					if(x <= 0)	x = 0;
					if(x >= 590) x = 590;
					myTank.SetX(x);
					}
					break;
				case VK_RIGHT:
					{	
					myTank.SetDirection(RIGHT);
					int x = myTank.GetX();
					x += 5;				//�ƶ��ٶ�
					if(x <= 0)	x = 0;
					if(x >= 590) x = 590;
					myTank.SetX(x);
			
			
				}
				break;

				case VK_SPACE:{
					int dir = myTank.GetDirection();
					Bullet *b = myTank.GetBullet();			//�ӵ�����		
					int x= myTank.GetX();
					int y = myTank.GetY();		
					int index = -1;			//�����ӵ��±�
					for(int i = 0;i < 20;i++){
						if(b[i].exist == false){
							index = i;
							b[i].exist = true;
							break;
						}
					}
					if(index == -1)
						return 0;			//ͬʱ��෢��20���ӵ�
					if(dir == 0){				//����Ϊ��
						//�����ӵ�λ��
						b[index].SetX(x+10);
						b[index].SetY(y+2);
						//�����ӵ�����
						b[index].SetDir(dir);
					}
					if(dir == 1){				//����Ϊ��
						//�����ӵ�λ��
						b[index].SetX(x+10);
						b[index].SetY(y+33);
						//�����ӵ�����
						b[index].SetDir(dir);
					}
					if(dir == 2){				//����Ϊ��
						//�����ӵ�λ��
						b[index].SetX(x - 13);
						b[index].SetY(y+10);
						//�����ӵ�����
						b[index].SetDir(dir);
					}
					if(dir == 3){				//����Ϊ��
						//�����ӵ�λ��
						b[index].SetX(x+33);
						b[index].SetY(y+10);
						//�����ӵ�����
						b[index].SetDir(dir);
					}
					break;
				 }
				break;
			}
			break;
	case WM_DESTROY:{
		int i;

		DeleteDC(mdc);
		DeleteDC(bufdc);
		DeleteObject(bg);
		ReleaseDC(hWnd, hdc);

		PostQuitMessage(0);
		}
		break;
		
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}
