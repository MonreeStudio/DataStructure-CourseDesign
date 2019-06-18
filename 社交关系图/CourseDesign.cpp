#include <iostream>
#include <queue>
#include <cstdlib>
#include "Person.h"
#include "AdjMatrix.h"
using namespace std;

int main()
{
	AdjMatrix adjM;
	if (adjM.CreateMatrix())
	{
		adjM.showAdj();
		adjM.shortestPath();
	}
	system("pause");
}

