#include <iostream>
#include <queue>
#include <cstdlib>
#include "Person.h"
#include "AdjMatrix.h"
using namespace std;

void nearFind(AdjMatrix *a)	//寻找附近能够联系的人
{
	queue<string> Q; //定义一个队列来储存路径上的人
	cout << endl << "请输入需要查找附近联系人的人的序号(所有序号从1开始)：" << endl;
	int find;
	//检查输入的序号是否在范围之内
	while (cin >> find)
	{
		if (find > 0 && find < a->GetPersonNum() + 1)
			break;
		else
			cout << "非法输入，请重新输入！" << endl;
	}
	find--;
	cout << endl;
	//利用循环寻找附近范围能够联系到的人
	for (int j = 0; j < a->GetPersonNum(); j++)
		if (a->GetAdj(find, j) < 50 && a->GetPersonName(j) != a->GetPersonName(find))
			Q.push(a->GetPersonName(j));
	if (Q.empty())
		cout << "哦豁，这个人附近没有人。" << endl;
	else
	{
		cout << "在附近能够找到的人有：";
		while (!Q.empty())
		{
			cout << Q.front() << ' ';
			Q.pop();
		}
	}
}

void FindByOne(AdjMatrix *a)	//寻找通过一次中间人能够联系的人
{
	queue<string> Q;
	cout << endl << "请输入需要一次中间人查找联系人的人的序号(所有序号从1开始)：" << endl;
	int find;
	//检查输入的序号是否在范围之内
	while (cin >> find)
	{
		if (find > 0 && find < a->GetPersonNum() + 1)
			break;
		else
			cout << "非法输入，请重新输入！" << endl;
	}
	find--;
	for (int k = 0; k < a->GetPersonNum(); k++)
		if (a->GetAdj(find, k) != infinity)
			for (int m = 0; m < a->GetPersonNum(); m++)
				if (a->GetAdj(k, m) != infinity && a->GetPersonName(m) != a->GetPersonName(find))
					Q.push(a->GetPersonName(m));
	if (Q.empty())
		cout << "真是尴尬，通过一次中间人此人无法联系到其他人。" << endl;
	else
	{
		cout << endl << "通过一次中间人能够联系到的人有：";
		while (!Q.empty())
		{
			cout << Q.front() << ' ';
			Q.pop();
		}
	}
}

int main()
{
	AdjMatrix* adjM = new AdjMatrix();	//创建一个对象
	if (adjM->CreateMatrix())	//创建邻接矩阵
	{
		bool go_on = true;
		while(go_on)		//重复操作
		{
			adjM->showAdj();	//输出邻接矩阵
			adjM->shortestPath();	//输出最短路径
			nearFind(adjM);		//寻找附近能够联系的人
			FindByOne(adjM);	//寻找通过一次中间人能够联系的人
			cout << endl << endl << "继续吗？若要退出请输0，其他数则继续。" << endl;
			int i;
			cin >> i;
			if (i == 0)
				go_on = false;
			else
			{
				cout << endl;
				adjM->updateXY();	//更新地理位置信息
			}
		}
	}
}

