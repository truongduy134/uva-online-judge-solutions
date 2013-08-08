/*******************************************************************************
 * Author: Nguyen Truong Duy
 ********************************************************************************/

/* Methodology:
 *	+ We use backtracking algorithm to solve this problem.
 *
 *	+ At each vertex, we have 2 choices: coloring it BLACK or WHITE.
 *	  Every vertex can be colored WHITE.
 *	+ However, we must check if a vertex can be colored BLACK.
 *	  A vertex can be colored BLACK if and only if none of its neighbors is BLACK.
 *	+ So we go into each direction (if possible) and choose the one with the maximum number
 *		of black nodes.
 *
 *	+ Time complexity: O(2^|V|) in the worst case. However, this backtracking algorithm
 *		is fast enough to pass the time limit on the online judge.
 */

#include <cstdio>
#include <vector>

using namespace std;

const int BLACK = 0;
const int WHITE = 1;
const int NO_COLOR = 2;

void recurseOptimalColor(const vector<vector<int> > & adjList, int curV, int numBlack, vector<int> & colorArr, int * maxNumBlack, vector<int> & optimalColorArr);

int main(void)
{
	int T, numV, numE;
	vector<vector<int> > adjList;
	vector<int> emptyList;
	int maxNumBlack = 0;
	vector<int> optimalColorArr, colorArr;

	scanf("%d", &T);
	while(T)
	{
		scanf("%d %d", &numV, &numE);
		adjList.assign(numV, emptyList);

		int u, v;
		for(int i = 0; i < numE; i++)
		{
			scanf("%d %d", &u, &v);
			u--;
			v--;
			adjList[u].push_back(v);
			adjList[v].push_back(u);
		}

		colorArr.assign(numV, NO_COLOR);
		maxNumBlack = 0;
		recurseOptimalColor(adjList, 0, 0, colorArr, &maxNumBlack, optimalColorArr);

		printf("%d\n", maxNumBlack);
		bool isFirst = true;
		for(int v = 0; v < numV; v++)
			if(optimalColorArr[v] == BLACK)
			{
				if(isFirst)
					isFirst = false;
				else
					printf(" ");
				printf("%d", v + 1);
			}
		printf("\n");		
		T--;
	}
	return 0;
}

void recurseOptimalColor(const vector<vector<int> > & adjList, int curV, int numBlack, vector<int> & colorArr, int * maxNumBlack, vector<int> & optimalColorArr)
{
	int numV = (int) adjList.size();

	if(curV >= numV)
	{
		if(numBlack > *maxNumBlack)
		{
			*maxNumBlack = numBlack;
			optimalColorArr = colorArr;
		}
		return;
	}

	bool canBeBlack = true;
	for(int ind = 0; ind < (int) adjList[curV].size(); ind++)
	{
		int nextV = adjList[curV][ind];
		if(colorArr[nextV] == BLACK)
		{
			canBeBlack = false;
			break;
		}
	}

	if(canBeBlack)
	{
		colorArr[curV] = BLACK;
		recurseOptimalColor(adjList, curV + 1, numBlack + 1, colorArr, maxNumBlack, optimalColorArr);
	}

	// Backtrack and color this node white
	colorArr[curV] = WHITE;
	recurseOptimalColor(adjList, curV + 1, numBlack, colorArr, maxNumBlack, optimalColorArr);
}
