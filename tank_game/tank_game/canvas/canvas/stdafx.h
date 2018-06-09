// stdafx.h : ��׼ϵͳ�����ļ��İ����ļ���
// ���Ǿ���ʹ�õ��������ĵ�
// �ض�����Ŀ�İ����ļ�
//

#pragma once

#include "targetver.h"

//������
#define TOP 0
#define BOTTOM 1
#define LEFT 2
#define RIGHT 3

#define WIN32_LEAN_AND_MEAN             //  �� Windows ͷ�ļ����ų�����ʹ�õ���Ϣ
// Windows ͷ�ļ�: 
#include <windows.h>

// C ����ʱͷ�ļ�
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>


// TODO:  �ڴ˴����ó�����Ҫ������ͷ�ļ�
//Ϊ��Լʱ�䣬����ʱд������

//������
class Object
{
public:
	Object(){};
	virtual ~Object(){};
private:

};

//�ӵ���
class Bullet: public Object
{
public:	
	void Set(int xx,int yy){
		x = xx,y = yy;				//�����ӵ�����
	}
	void SetX(int xx){x = xx;}
	void SetY(int yy){y = yy;}
	int GetX(){return x;}
	int GetY(){return y;}	
private:
	int x,y;			//�ӵ�����
};



//̹����
class Tank: public Object
{
public:		
	Tank(int xx=20,int yy= 20,int d = 0){x = xx,y = yy,dir = d;}
	void Set(int xx,int yy){x = xx,y = yy;}
	void SetX(int xx){x = xx;}
	void SetY(int yy){y = yy;}
	void SetDirection(int dirr){dir = dirr;}			//����
	Bullet* GetBullet(){return bullet;}
	int GetDirection(){return dir;}
	int GetX(){return x;}
	int GetY(){return y;}
private:
	int x,y;			//����
	int dir;			//����
	Bullet bullet[20];			//�ӵ�����
};







