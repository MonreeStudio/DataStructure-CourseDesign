#include<string>
#include<ctime>
#include<iostream>
#include<Windows.h>
using namespace std;
#pragma once
class Person
{
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
		this->X = InitX_Aixs();
		this->Y = InitY_Aixs();
	}
	int InitX_Aixs();
	int InitY_Aixs();
	string getName();
	int getX();
	int getY();
};

int Person::InitX_Aixs()
{
	int tempX;
	srand((unsigned)time(NULL)+Y);
	tempX = (rand() % 100);
	return tempX;
}

int Person::InitY_Aixs()
{
	int tempY;
	srand((unsigned)time(NULL)+X);
	tempY = (rand() % 100);
	return tempY;
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
