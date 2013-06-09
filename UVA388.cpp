/*******************************************************************************
 * Author: Nguyen Truong Duy
 ********************************************************************************/

/* Methodology:
 *	+ Key observation: When finding the trading value between Earth and
 *		a planet X, we only care about the shortest shipping line (in terms
 *		of the number of nodes). It is because the longer the shipping line,
 *		the more fee we have to pay.
 *
 *	+ Hence, first, we find the shortest path from Earth to other planets 
 *	  (if such path exists).
 *	+ For each intermediate stops, we have to pay 5% fee.
 *	+ Hence, for a shipping line of length L, and the value of the exporter is V,
 *		the value of the goods in Earth is f = V * (0.95)^(L - 1)
 *	  We choose the maximum value of f among all shortest paths from Earth to 
 *		other planets.
 *	+ To find the shortest path, we can use Breadth First Search (because our
 *		graph is unweighted) with Adjacency List.
 * 
 *	+ Time complexity: O(V + E)
 */

#include <cstdio>
#include <vector>
#include <cstring>
#include <queue>
#include <cmath>

using namespace std;

const int MAX_NUM_PLANET = 27;
const char EARTH = '*';
const int EARTH_V_IND = 26;
const int MAX_LEN_STR = 26;
const int INFINITY_LENGTH = 1000000000;
const double GAIN_AFTER_FEE = 0.95;

int findBestExporter(const vector<vector<int> > & adjList, const vector<double> & valueArr);
void findShortestPathBFS(const vector<vector<int> > & adjList, int src, vector<int> & distFromSrc);

int main(void)
{
	int numPlanet;
	vector<double> valueArr;
	vector<vector<int> > adjList;
	vector<int> emptyList;
	int adjMat[MAX_NUM_PLANET][MAX_NUM_PLANET];
	char planet[MAX_LEN_STR + 1], neighbor[MA388X_LEN_STR + 1];
	double val;

	while(scanf("%d", &numPlanet) > 0)
	{
		memset(adjMat, 0, MAX_NUM_PLANET * MAX_NUM_PLANET * sizeof(int));
		valueArr.assign(MAX_NUM_PLANET, 0.0);
		adjList.assign(MAX_NUM_PLANET, emptyList);

		for(int i = 0; i < numPlanet; i++)
		{
			scanf("%s %lf %s", planet, &val, neighbor);

			int idOne = (int) planet[0] - 'A';
			valueArr[idOne] = val;
			for(int k = 0; neighbor[k] != '\0'; k++)
			{
				int idTwo = EARTH_V_IND;
				if(neighbor[k] != EARTH)
					idTwo = (int) neighbor[k] - 'A';
				if(adjMat[idOne][idTwo] == 0)
				{
					adjMat[idOne][idTwo] = 1;
					adjMat[idTwo][idOne] = 1;
					adjList[idOne].push_back(idTwo);
					adjList[idTwo].push_back(idOne);
				}
			}
		}

		int bestExport = findBestExporter(adjList, valueArr);
		printf("Import from %c\n", bestExport + 'A');	
	}
	return 0;
}

int findBestExporter(const vector<vector<int> > & adjList, const vector<double> & valueArr)
{
	vector<double> importVal(MAX_NUM_PLANET, 0.0);

	vector<int> distFromEarth;
	findShortestPathBFS(adjList, EARTH_V_IND, distFromEarth);

	for(int planet = 0; planet < MAX_NUM_PLANET - 1; planet++)
		if(distFromEarth[planet] != INFINITY_LENGTH)
		{
			importVal[planet] = valueArr[planet] * pow(GAIN_AFTER_FEE, distFromEarth[planet] - 1);
		}

	int maxInd = 0;
	for(int v = 1; v < MAX_NUM_PLANET - 1; v++)
		if(importVal[v] > importVal[maxInd])
			maxInd = v;
	return maxInd;
}

void findShortestPathBFS(const vector<vector<int> > & adjList, int src, vector<int> & distFromSrc)
{
	distFromSrc.assign(MAX_NUM_PLANET, INFINITY_LENGTH);
	distFromSrc[src] = 0;
	queue<int> bfsQueue;
	bfsQueue.push(src);

	while(!bfsQueue.empty())
	{
		int v = bfsQueue.front();
		bfsQueue.pop();

		for(int i = 0; i < (int) adjList[v].size(); i++)
		{
			int nextV = adjList[v][i];
			if(distFromSrc[nextV] == INFINITY_LENGTH)
			{
				distFromSrc[nextV] = distFromSrc[v] + 1;
				bfsQueue.push(nextV);
			}
		}
	}
}
