#include<string>
#include<ctime>
#include<iostream>
#include<Windows.h>
using namespace std;
#pragma once
class Person
{
	friend class AdjMatrix;
private:
	string Name;//人名
	int X;		//人所在X轴坐标
	int Y;		//人所在Y轴坐标
public:
	Person()
	{
		Name = "";
		X = 0;
		Y = 0;
	}
	Person(string a) 
	{
		this->Name = a;
		InitX_Aixs();
		InitY_Aixs();
	}
	void InitX_Aixs();
	void InitY_Aixs();
	string getName();
	int getX();
	int getY();
};

void Person::InitX_Aixs()
{
	int tempX;
	srand((unsigned)time(NULL)+Y);
	tempX = (rand() % 100);
	X = tempX;
}

void Person::InitY_Aixs()
{
	int tempY;
	srand((unsigned)time(NULL)+X);
	tempY = (rand() % 100);
	Y = tempY;
}

string Person::getName()
{
	return Name;
}

int Person::getX()
{
	return X;
}

int Person::getY()
{
	return Y;
}
