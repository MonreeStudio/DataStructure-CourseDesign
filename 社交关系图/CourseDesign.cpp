#include <iostream>
#include <queue>
#include <cstdlib>
#include "Person.h"
#include "AdjMatrix.h"
using namespace std;

int main()
{
	AdjMatrix* adjM = new AdjMatrix();	//创建一个对象
	queue<string> Q1, Q2;	//定义两个队列用来存放数据
	if (adjM->CreateMatrix())	//创建邻接矩阵
	{
		while(true)		//重复操作
		{
			adjM->showAdj();	//输出邻接矩阵
			adjM->shortestPath();	//输出最短路径
			cout << endl << "请输入需要查找附近联系人的人的序号(所有序号从1开始)：" << endl;
			int find;	
			cin >> find;
			find--;
			cout << endl;
			//利用循环寻找附近范围能够联系到的人
			for (int j = 0; j < adjM->GetPersonNum(); j++)
				if (adjM->GetAdj(find, j) < 100 && adjM->GetPersonName(j) != adjM->GetPersonName(find))
						Q1.push(adjM->GetPersonName(j));			
			if (Q1.empty())
				cout << "哦豁，这个人附近没有人。" << endl;
			else
			{
				cout << "在附近能够找到的人有：";
				while (!Q1.empty())
				{
					cout << Q1.front() << ' ';
					Q1.pop();
				}
			}
			//利用循环寻找通过一次中间人可以联系到的人
			for (int k = 0; k < adjM->GetPersonNum(); k++)
				if(adjM->GetAdj(find,k)!=infinity)
					for (int m = 0; m < adjM->GetPersonNum(); m++)
						if (adjM->GetAdj(k, m) != infinity && adjM->GetPersonName(m) != adjM->GetPersonName(find))
							Q2.push(adjM->GetPersonName(m));
			if (Q2.empty())
				cout << "真是尴尬，通过一次中间人此人无法联系到其他人。" << endl;
			else
			{
				cout << endl << "通过一次中间人能够联系到的人有：";
				while (!Q2.empty())
				{
					cout << Q2.front() << ' ';
					Q2.pop();
				}
			}
			cout << endl;
			adjM->updateXY();
		}
	}
	system("pause");
}

