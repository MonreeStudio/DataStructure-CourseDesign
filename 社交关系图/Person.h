#include<string>
#include<ctime>
#include<iostream>
using namespace std;
#pragma once
class Person
{
	friend class AdjMatrix;	//邻接矩阵AdjMatrix类定义为其友元类
private:
	string Name;//人名
	int X;		//人所在X轴坐标
	int Y;		//人所在Y轴坐标
public:
	Person()	//构造函数初始化成员变量
	{
		Name = "";
		X = 0;
		Y = 0;
	}
	Person(string a) //重载构造函数为成员变量赋值
	{
		this->Name = a;
		InitX_Aixs();
		InitY_Aixs();
	}
	void InitX_Aixs();	//初始化X轴坐标
	void InitY_Aixs();	//初始化Y轴坐标
	string getName();	//获取名字
	int getX();	//获取X轴坐标
	int getY();	//获取Y轴坐标
};

void Person::InitX_Aixs()	//利用随机数为X轴坐标赋值
{
	int tempX;
	srand((unsigned)time(NULL)+Y);
	tempX = (rand() % 100);
	X = tempX;
}

void Person::InitY_Aixs()	//利用随机数为Y轴坐标赋值
{
	int tempY;
	srand((unsigned)time(NULL)+X);
	tempY = (rand() % 100);
	Y = tempY;
}

string Person::getName()	//获取名字
{
	return Name;
}

int Person::getX()	//获取X轴坐标
{
	return X;
}

int Person::getY()	//获取Y轴坐标
{
	return Y;
}
