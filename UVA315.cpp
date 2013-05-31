/*******************************************************************************
 * Author: Nguyen Truong Duy
 ********************************************************************************/

/* Methodology:
 *	+ This problem asks to find articulation points in a graph G.
 *	+ A graph G has no loop and is connected
 *
 * Algorithm: we can use DFS to find all articulation points in O(V + E) time.
 *
 * Alternative solution: Since the graph is small, we can have a straightforward
 *	O(V * (V + E)) solution by removing 1 vertex at a time, and running DFS to 
 *	check the new graph is still connected
 *
 * An explanation of the O(V + E) algorithm:
 *	+ dfsNum[v] = the order in which the node v is visied in a run of DFS.
 *	  So in the DFS tree, if x is an ancestor of y, dfsNum[x] < dfsNum[y].
 *
 *	+ lowLink[v] = the lowest dfsNum that can be visited from v using a backedge from one of its descendants in the DFS tree.
 *	  
 *	+ Clearly, removing a vertex v from the DFS tree disconnects the graph if and only if THERE EXISTS a child u of v such that there is no backedge from u (or its descendants) to one of ancestors of v. Hence, by removing v, we have no way to reach u and its descendants.
 *	  Hence, a non-root v is an articulation point if and only if v has a child u (in the DFS tree) such that lowLink[u] >= dfsNum[v] 
 *
 *	+ A root of the DFS tree is an articulation point if and only if it has more than 1 child.
 */

#include <cstdio>
#include <vector>
#include <cstdlib>
#include <cstring>

using namespace std;

const int MAX_LEN_LINE = 10000;

bool parseLineToBuildGraph(char line[], vector<vector<int> > & adjList);
int findNumArticulationPoints(const vector<vector<int> > & adjList);
int runDFSToFindArticulation(int v, const vector<vector<int> > & adjList, int *dfsId, vector<int> & dfsNum, vector<int> & lowLink, int directParent, vector<bool> & isArticulation);
int min(int a, int b);

int main(void)
{
	vector<vector<int> > adjList;
	vector<int> emptyList;
	int numV;
	char line[MAX_LEN_LINE + 1];

	while(1)
	{
		scanf("%d", &numV);
		gets(line);
		if(!numV)
			break;

		adjList.assign(numV, emptyList);

		do
		{
			gets(line);
		} while(parseLineToBuildGraph(line, adjList));

		printf("%d\n", findNumArticulationPoints(adjList));
	}

	return 0;
}

bool parseLineToBuildGraph(char line[], vector<vector<int> > & adjList)
{
	const char delim[] = " ";
	char * token;
	
	token = strtok(line, delim);
	int v;
	if(token != NULL)
	{
		v = atoi(token);
		if(v == 0)
			return false;
		v--;
	}

	int neighbor;
	token = strtok(NULL, delim);
	while(token != NULL)
	{
		neighbor = atoi(token);
		neighbor--;
		adjList[v].push_back(neighbor);
		adjList[neighbor].push_back(v);

		token = strtok(NULL, delim);
	}

	return true;
}

int findNumArticulationPoints(const vector<vector<int> > & adjList)
{
	int numV = (int) adjList.size();
	vector<bool> isArticulation(numV, false);
	vector<int> dfsNum(numV, -1);
	vector<int> lowLink(numV, -1);

	int dfsId = 0;
	for(int v = 0; v < numV; v++)
		if(dfsNum[v] < 0)
		{
			int numRootChild = runDFSToFindArticulation(v, adjList, &dfsId, dfsNum, lowLink, v, isArticulation);

			// Gotcha: isArticulation[v] (v is a root) has been turned on in the run of DFS. Hence, we must turn it off (set it to be false) if the root has less than 2 children)
			if(numRootChild >= 2) 
				isArticulation[v] = true;
			else
				isArticulation[v] = false;
		}

	int numArticulation = 0;
	for(int v = 0; v < numV; v++)
		if(isArticulation[v])
			numArticulation++;

	return numArticulation;
}

int runDFSToFindArticulation(int v, const vector<vector<int> > & adjList, int *dfsId, vector<int> & dfsNum, vector<int> & lowLink, int directParent, vector<bool> & isArticulation)
{
	dfsNum[v] = *dfsId;
	lowLink[v] = *dfsId;
	(*dfsId)++;

	int numChild = 0;
	for(int ind = 0; ind < (int) adjList[v].size(); ind++)
	{
		int neighbor = adjList[v][ind];

		if(dfsNum[neighbor] < 0)
		{
			// Not visited
			numChild++;

			runDFSToFindArticulation(neighbor, adjList, dfsId, dfsNum, lowLink, v, isArticulation);

			if(lowLink[neighbor] >= dfsNum[v])
			{
				// No backedge from the DFS subtree rooted at neighbor to one of the ancestors of v. So v is an articulation point
				isArticulation[v] = true;
			}

			lowLink[v] = min(lowLink[v], lowLink[neighbor]);
		}
		else
		{
			// Visited
			if(neighbor != directParent)
				// There is a backedge. Update lowLink
				lowLink[v] = min(lowLink[v], dfsNum[neighbor]);
		}
	}

	return numChild;
}

int min(int a, int b)
{
	if(a < b)
		return a;
	return b;
}
