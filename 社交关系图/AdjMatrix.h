#pragma once
#include<string>
#include<cmath>
#include<stack>
#include<algorithm>
#include<iomanip>
using namespace std;
const int maxnum = 100;		//定义范围
const int infinity = 10000;	//用10000表示无穷值

class AdjMatrix
{
private:
	Person person[maxnum];	//Person类对象数组
	double adj[maxnum][maxnum];//邻接矩阵
	double dist[maxnum];		//路径长度
	int prePerson[maxnum];	//存放路径中该点的前一个人信息的数组
	int personNum;			//人数（点数）
	int edgeNum;			//边数
	bool visited[maxnum];	//判断是否访问某点的数组（访问过为true，反之为false）
public:
	AdjMatrix();			//构造函数
	bool CreateMatrix();	//创建邻接矩阵
	bool InitMatrix(int);	//初始化邻接矩阵
	int GetPersonNum();		//获取人数
	int GetEdgeNum();		//获取边数
	double GetAdj(int,int);	//获取邻接矩阵中的某个值
	string GetPersonName(int);	//获取Person对象的名字
	double Distance(int,int,int,int);	//计算两点间的距离
	void showAdj();			//输出邻接矩阵
	void shortestPath();	//计算并输出最短路径
	void updateXY();
};

AdjMatrix::AdjMatrix()
{	
	//初始化人数和边数
	personNum = 0;
	edgeNum = 0;
	//下面三行为初始化三个数组，数组元素由第三个参数填充
	fill(visited, visited + maxnum, false);
	fill(dist, dist + maxnum, infinity);
	fill(prePerson, prePerson + maxnum, infinity);
}

double AdjMatrix::Distance(int x1, int y1, int x2, int y2)	//计算两点间的距离
{
	double x = abs(x1 - x2);
	double y = abs(y1 - y2);
	double d = sqrt(x * x + y * y);
	return d;
}

int AdjMatrix::GetPersonNum()	//获取人数
{
	return personNum;
}

int AdjMatrix::GetEdgeNum()		//获取边数
{
	return edgeNum;
}

double AdjMatrix::GetAdj(int a,int b)	//获取邻接矩阵的某个值（通过参数确定位置）
{
	return adj[a][b];
}

string AdjMatrix::GetPersonName(int i)	//获取Person的对象的名字
{
	return person[i].getName();
}

bool AdjMatrix::InitMatrix(int n)	//初始化邻接矩阵
{
	for (int i = 0; i < n; i++)
	{
		prePerson[i] = i;
		for (int j = 0; j < n; j++)
		{
			adj[i][j] = infinity;	//初始用无穷值表示
		}
	}
	return true;
}

bool AdjMatrix::CreateMatrix()	//创建邻接矩阵
{
	
	cout << "请输入人数：" << endl;
	cin >> personNum;
	if (InitMatrix(personNum))	//初识化矩阵
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
		int i, j;
		double w;
		for (int k = 0; k < edgeNum; k++)
		{
			cout << "请输入有联系的两个人的序号(序号从1开始)：	";
			while (cin >> i >> j)
			{
				if (i > 0 && i < 101 && j>0 && j < 101)
					break;
				else
					cout << "非法输入，请重新输入！" << endl;
			}
			w = Distance(person[i - 1].getX(), person[i - 1].getY(), person[j - 1].getX(), person[j - 1].getY()); //根据两点坐标计算距离
			adj[i - 1][j - 1] = w;					//两点距离即边的权值
			adj[j - 1][i - 1] = adj[i - 1][j - 1];	//邻接矩阵为对称矩阵
		}
	}
	return true;
}

void AdjMatrix::showAdj()	//输出邻接矩阵
{
	//设置输出结果小数位精度为2
	cout << setprecision(2);
	cout << setiosflags(ios::fixed);
	cout << endl << "邻接矩阵：" << endl;
	for (int i = 0; i < personNum; i++)
		for (int j = 0; j < personNum; j++)
		{
			if (adj[i][j] == infinity)			
				cout << "∞      ";		//若为无穷值，则输出无穷符号
			else
				cout << adj[i][j] << "    ";
			if (j == (personNum - 1))	//设置换行
				cout << endl;
		}
	cout << endl;
}

void AdjMatrix::shortestPath()	//最短路径计算和输出
{
	fill(dist, dist + personNum, infinity);	//初始化路径长度数组，用无穷值填充
	int FirstPerson;	//定义出发点
	cout << endl << "请输入第一个人的序号(所有序号从1开始)：" << endl;
	while (cin >> FirstPerson)	//判断是否为非法输入
	{
		if (FirstPerson > 0 && FirstPerson < personNum + 1)
			break;
		else
			cout << "非法输入，请重新输入！" << endl;
	}
	FirstPerson--;

	dist[FirstPerson] = 0;	//点到自身的距离为0
	for (int i = 0; i < personNum; i++)	//开始遍历
	{
		int u = -1;		//设置跟踪点，初始为-1
		double min = infinity;	//每一段路径长度最小值初始化为无穷值
		for (int j = 0; j < personNum; j++)	//查找下一个点
		{
			if (visited[j] == false && dist[j] <= min)	//若下一个点未被访问过，且到达该点路径长度为最小值
			{
				u = j;	//跟踪点更新为下一个未访问过的点
				min = dist[j];	//到达下一点的路径最小值
			}
		}
		if (u == -1)	//若u仍为-1，未找到下一个点，退出循环
			break;
		visited[u] = true;	//访问过的点记为true
		for (int v = 0; v < personNum; v++)	//再次遍历
		{
			if (visited[v] == false && adj[u][v] != infinity)	//若该点未被访问过且与跟踪点所在位置相连
			{
				if (dist[u] + adj[u][v] < dist[v])	//计算路径长度是否为最小值
				{
					dist[v] = dist[u] + adj[u][v];	//更新最短路径长度
					prePerson[v] = u;	//记录该点的前一个点
				}
			}
		}
	}
	for (int i = 0; i < personNum; i++)
	{
		if (dist[i] == infinity)
			cout << person[FirstPerson].getName() << "到" << person[i].getName() << "的最短距离为: ∞" << endl;
		else
			cout << person[FirstPerson].getName() << "到" << person[i].getName() << "的最短距离为: " << dist[i] << endl;
	}
	int SecondPerson;	//定义终点
	cout << "请输入第二个人的序号(所有序号从1开始):" << endl;
	while (cin >> SecondPerson)	//判断是否为非法输入
	{
		if (SecondPerson > 0 && SecondPerson < personNum + 1)
			break;
		else
			cout << "非法输入，请重新输入！" << endl;
	}
	SecondPerson--;

	stack<int> myStack;//定义一个堆栈，用来记录最短路径所经过的点
	int temp = SecondPerson;
	myStack.push(SecondPerson);	//先将终点压入栈中
	
	bool isConnected = true;  // 假设是连通的
	while (FirstPerson != temp) 
	{
		temp = prePerson[temp];
		//若不连通则退出循环
		if (temp == infinity) 
		{
			isConnected = false;
			break;
		}
		//连通则将该点的前一个点压入栈中
		myStack.push(temp);
	}
	if (isConnected) //如果是连通图
	{
		//输出起始点到终点的最短路径
		cout << person[FirstPerson].getName() << "到" << person[SecondPerson].getName() << "的最短路线为: ";
		while (!myStack.empty())
		{
			cout << person[myStack.top()].getName() << " ";
			myStack.pop();
		}
		cout << endl << endl;
	}
	else	//如果不是连通图且该点为孤立点
	{
		cout << "哦豁，这个人被孤立了。" << endl;
	}
	
}

void AdjMatrix::updateXY()	//更新Person的对象的X、Y坐标
{
	//再次初始化三个数组
	fill(visited, visited + maxnum, false);
	fill(dist, dist + maxnum, infinity);
	fill(prePerson, prePerson + maxnum, infinity);
	//重新为X、Y坐标赋值
	for (int i = 0; i < personNum; i++)
	{
		person[i].InitX_Aixs();
		person[i].InitY_Aixs();
	}
	//根据新的X、Y坐标计算两点间距离
	for (int i = 0; i < personNum; i++)
		for (int j = 0; j < personNum; j++)
		{
			if (adj[i][j] != infinity)
				adj[i][j] = Distance(person[i].getX(), person[i].getY(), person[j].getX(), person[j].getY());
		}
	cout << endl << endl << endl << "所有人的位置已更新！" << endl;
}
