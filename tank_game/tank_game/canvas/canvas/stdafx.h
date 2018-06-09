// stdafx.h : 标准系统包含文件的包含文件，
// 或是经常使用但不常更改的
// 特定于项目的包含文件
//

#pragma once

#include "targetver.h"

//方向定义
#define TOP 0
#define BOTTOM 1
#define LEFT 2
#define RIGHT 3

#define WIN32_LEAN_AND_MEAN             //  从 Windows 头文件中排除极少使用的信息
// Windows 头文件: 
#include <windows.h>

// C 运行时头文件
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>


// TODO:  在此处引用程序需要的其他头文件
//为节约时间，类暂时写在这里

//物体类
class Object
{
public:
	Object(){};
	virtual ~Object(){};
private:

};

//子弹类
class Bullet: public Object
{
public:	
	void Set(int xx,int yy){
		x = xx,y = yy;				//设置子弹坐标
	}
	void SetX(int xx){x = xx;}
	void SetY(int yy){y = yy;}
	int GetX(){return x;}
	int GetY(){return y;}	
private:
	int x,y;			//子弹坐标
};



//坦克类
class Tank: public Object
{
public:		
	Tank(int xx=20,int yy= 20,int d = 0){x = xx,y = yy,dir = d;}
	void Set(int xx,int yy){x = xx,y = yy;}
	void SetX(int xx){x = xx;}
	void SetY(int yy){y = yy;}
	void SetDirection(int dirr){dir = dirr;}			//方向
	Bullet* GetBullet(){return bullet;}
	int GetDirection(){return dir;}
	int GetX(){return x;}
	int GetY(){return y;}
private:
	int x,y;			//坐标
	int dir;			//方向
	Bullet bullet[20];			//子弹数组
};







