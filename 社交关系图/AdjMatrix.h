#pragma once
#include<string>
#include<cmath>
#include<stack>
#include<algorithm>
using namespace std;
const int maxnum = 100;
const int infinity = 10000;//用10000表示无穷值

class AdjMatrix
{
private:
	Person person[maxnum];
	int adj[maxnum][maxnum];
	int path[maxnum];
	int prePerson[maxnum];
	int personNum;
	int edgeNum;
	bool visited[maxnum];
public:
	AdjMatrix();
	bool CreateMatrix();
	bool InitMatrix(int);
	int GetPersonNum();
	int GetEdgeNum();
	double Distance(int,int,int,int);
	void showAdj();
	void shortestPath();
	Person GetPerson(int);
};

AdjMatrix::AdjMatrix()
{
	personNum = 0;
	edgeNum = 0;
	fill(visited, visited + maxnum, false);
	fill(path, path + maxnum, infinity);
	fill(prePerson, prePerson + maxnum, infinity);
}

double AdjMatrix::Distance(int x1, int y1, int x2, int y2)
{
	double x = abs(x1 - x2);
	double y = abs(y1 - y2);
	double d = sqrt(x * x + y * y);
	return d;
}

int AdjMatrix::GetPersonNum()
{
	return personNum;
}

int AdjMatrix::GetEdgeNum()
{
	return edgeNum;
}

Person AdjMatrix::GetPerson(int n)
{
	return person[n];
}

bool AdjMatrix::InitMatrix(int n)
{
	for (int i = 0; i < n; i++)
	{
		prePerson[i] = i;
		for (int j = 0; j < n; j++)
		{
			adj[i][j] = infinity;
		}
	}
	return true;
}

bool AdjMatrix::CreateMatrix()
{
	
	cout << "请输入人数：" << endl;
	cin >> personNum;
	if (InitMatrix(personNum))
	{
		cout << "请输入社交网络图的边数(两人有联系即两人有一条边)：" << endl;
		cin >> edgeNum;
		cout << endl;
		for (int i = 0; i < personNum; i++)
		{
			string tempName;
			cout << "请输入第" << i + 1 << "个人的名字" << endl;
			cin >> tempName;
			person[i] = Person(tempName);
			cout << "坐标为：(" << person[i].getX() << ',' << person[i].getY() << ')' << endl << endl;
		}
		int i, j, w;
		for (int k = 0; k < edgeNum; k++)
		{
			cout << "请输入有联系的两个人的序号(序号从1开始)：	";
			cin >> i >> j;
			w = Distance(person[i].getX(), person[i].getY(), person[j].getX(), person[j].getY());
			adj[i - 1][j - 1] = w;
			adj[j - 1][i - 1] = adj[i - 1][j - 1];
		}
	}
	return true;
}

void AdjMatrix::showAdj()
{
	cout << endl;
	for (int i = 0; i < personNum; i++)
		for (int j = 0; j < personNum; j++)
		{
			if (adj[i][j] == infinity)
			{
				cout << adj[i][j] << ' ';
			}
			else
				cout << adj[i][j] << "    ";
			if (j == (personNum - 1))
				cout << endl;
		}
	cout << endl;
}

void AdjMatrix::shortestPath()
{
	fill(path, path + personNum, infinity);
	int FirstPerson;
	cout << endl << "请输入第一个人的序号(所有序号从1开始)：" << endl;
	cin >> FirstPerson;
	FirstPerson--;

	path[FirstPerson] = 0;
	for (int i = 0; i < personNum; i++)
	{
		int u = -1;
		int min = infinity;
		for (int j = 0; j < personNum; j++)
		{
			if (visited[j] == false && path[j] <= min)
			{
				u = j;	
				min = path[j];
			}
		}
		if (u == -1)
			break;
		visited[u] = true;
		for (int v = 0; v < personNum; v++)
		{
			if (visited[v] == false && adj[u][v] != infinity)
			{
				if (path[u] + adj[u][v] < path[v])
				{
					path[v] = path[u] + adj[u][v];
					prePerson[v] = u;	
				}
			}
		}
	}
	for (int i = 0; i < personNum; i++)
	{
		cout  << person[FirstPerson].getName() << "到" << person[i].getName() << "的最短距离为: " << path[i] << endl;
	}
	int SecondPerson;
	cout << "请输入第二个人的序号(所有序号从1开始):" << endl;
	cin >> SecondPerson;
	SecondPerson--;
	stack<int> myStack;
	int temp = SecondPerson;
	myStack.push(SecondPerson);
	while (FirstPerson != temp) 
	{
		temp = prePerson[temp];
		myStack.push(temp);
	}
	cout<< person[FirstPerson].getName() << "到" << person[SecondPerson].getName() << "的最短路线为: ";
	while (!myStack.empty()) 
	{
		cout << person[myStack.top()].getName() << " ";
		myStack.pop();
	}
	cout << endl << endl;
}
