#include <iostream>
#include <queue>
#include <list>
#include <cstdlib>
#include "Person.h"
#include "AdjMatrix.h"
using namespace std;

int main()
{
	AdjMatrix* adjM = new AdjMatrix();
	queue<string> Q;
	if (adjM->CreateMatrix())
	{
		for (int i = 0; i < 2; i++)
		{
			adjM->showAdj();
			adjM->shortestPath();
			cout << endl << "请输入需要查找附近联系人的人的序号(所有序号从1开始)：" << endl;
			int find;
			cin >> find;
			find--;
			cout << endl;
			for (int j = 0; j < adjM->GetPersonNum(); j++)
			{
				if (adjM->GetAdj(find, j) < 100)
				{
					if(adjM->GetPersonName(j)!= adjM->GetPersonName(find))
						Q.push(adjM->GetPersonName(j));
				}
			}
			if (Q.empty())
				cout << "哦豁，这个人附近没有人。" << endl;
			while (!Q.empty())
			{
				cout << Q.front() << ' ';
				Q.pop();
			}
			adjM->updateXY();
		}
	}
	system("pause");
}

