/*******************************************************************************
 * Author: Nguyen Truong Duy
 ********************************************************************************/

/* Methodology:
 *	+ This can be modelled as a directed graph problem
 *		- Each box is a vertex
 *		- There is a directed edge from box u to box v if u can be nested in v.
 *	+ Note that our graph G has no cycle. So G is a DAG
 *	+ The problem now becomes finding the longest path on G (i.e. finding a longest path
 *		on a DAG).
 *	+ This can be done is O(V + E) using the following procedure:
 *		- Find a topological order of vertices in G.
 *		- Let f(v) be the length of the longest path in G ending at v
 *		  Then f(v) = max(f(u) + 1) where u is a vertex such that there is an edge from 
 *				u to v.
 *		  Compute all values f(v) by relaxing edges based on the topological order.
 *		- After computing all f(v), choose the maximum values among f(v)
 *		  Then construct the longest path.
 *
 *	+ It is not advisable to use DFS to find a topological order in this problem.
 *	  Instead use the following procedure:
 *		- Compute the in degree of all vertices v in G
 *		- Maintain a queue Q
 *		- Push all vertices whose in degrees are 0 to Q.
 *		- While Q is not empty
 *			* Pop the front element v from Q
 *			* Append v to the topological order
 *			* Decrement the in degrees of all neighbors u of v
 *			* If the in degree of u is 0, push u to Q.
 *
 *	+ Time complexity: O(V + E)
 */

#include <algorithm>
#include <cstdio>
#include <vector>
#include <queue>

using namespace std;

class Box
{
private:
	int _numDimension;
	vector<int> _dimension;

public:
	Box();
	Box(int numDimension, const vector<int> & dimension);
	Box(const Box & other) : _numDimension(other._numDimension),
				 _dimension(other._dimension) {}
	~Box() {}

	Box & operator= (const Box & rhs);
	bool canBeNestedIn(const Box & other) const;	
};

Box::Box()
{
	_numDimension = 0;
}

Box::Box(int numDimension, const vector<int> & dimension) :
	_numDimension(numDimension), _dimension(dimension)
{
	// Sort the dimensions in increasing order
	sort(_dimension.begin(), _dimension.end());
}

Box & Box::operator= (const Box & rhs)
{
	if(this == &rhs)
		return *this;
	
	_numDimension = rhs._numDimension;
	_dimension = rhs._dimension;
	return *this;
}

bool Box::canBeNestedIn(const Box & other) const
{
	if(_numDimension != other._numDimension)
		return false;

	for(int i = 0; i < _numDimension; i++)
		if(_dimension[i] >= other._dimension[i])
			return false;
	return true;
}

void buildAdjList(const vector<Box> & boxArr, vector<vector<int> > & adjList);
void getLongestPathDAG(const vector<vector<int> > & adjList, vector<int> & longestPath);
void getTopoOrder(const vector<vector<int> > & adjList, vector<int> & topoOrder);

int main(void)
{
	int numBox, numDimension;
	vector<Box> boxArr;
	vector<vector<int> > adjList;
	vector<int> longestNestedSeq;

	while(scanf("%d %d", &numBox, &numDimension) > 0)
	{
		boxArr.clear();
		for(int i = 0; i < numBox; i++)
		{
			vector<int> dimension(numDimension, 0);
			for(int j = 0; j < numDimension; j++)
				scanf("%d", &dimension[j]);
			boxArr.push_back(Box(numDimension, dimension));
		}

		buildAdjList(boxArr, adjList);

		getLongestPathDAG(adjList, longestNestedSeq);

		printf("%d\n", (int) longestNestedSeq.size());
		printf("%d", longestNestedSeq[0] + 1);
		for(int i = 1; i < (int) longestNestedSeq.size(); i++)
			printf(" %d", longestNestedSeq[i] + 1);
		printf("\n");		
	}

	return 0;	
}

void buildAdjList(const vector<Box> & boxArr, vector<vector<int> > & adjList)
{
	int numV = (int) boxArr.size();

	adjList.assign(numV, vector<int> ());

	for(int boxOne = 0; boxOne < numV; boxOne++)
		for(int boxTwo = 0; boxTwo < numV; boxTwo++)
			if(boxArr[boxOne].canBeNestedIn(boxArr[boxTwo]))
				adjList[boxOne].push_back(boxTwo);
}

void getLongestPathDAG(const vector<vector<int> > & adjList, vector<int> & longestPath)
{
	vector<int> topoOrder;

	getTopoOrder(adjList, topoOrder);

	int numV = (int) adjList.size();
	vector<int> predecessor(numV, 0);
	for(int i = 0; i < numV; i++)
		predecessor[i] = i;
	vector<int> pathLength(numV, 0);
	// Find the longest path based on the topological order
	for(int i = 0; i < numV; i++)
	{
		int u = topoOrder[i];
		for(int k = 0; k < (int) adjList[u].size(); k++)
		{
			int v = adjList[u][k];

			if(pathLength[u] + 1 > pathLength[v])
			{
				pathLength[v] = pathLength[u] + 1;
				predecessor[v] = u;
			}
		}
	}

	// Construct the longest path
	longestPath.clear();
	int maxInd = 0;
	for(int v = 1; v < numV; v++)
		if(pathLength[v] > pathLength[maxInd])
			maxInd = v;

	int pathV = maxInd;
	while(1)
	{
		longestPath.push_back(pathV);
		int parent = predecessor[pathV];
		if(parent == pathV)
			break;
		pathV = parent;
	}
	reverse(longestPath.begin(), longestPath.end());
}

void getTopoOrder(const vector<vector<int> > & adjList, vector<int> & topoOrder)
{
	int numV = (int) adjList.size();
	topoOrder.clear();
	
	vector<int> inDegree(numV, 0);
	for(int u = 0; u < numV; u++)
		for(int ind = 0; ind < (int) adjList[u].size(); ind++)
		{
			int v = adjList[u][ind];
			inDegree[v]++;
		}

	queue<int> zeroInDegree;
	for(int v = 0; v < numV; v++)
		if(inDegree[v] == 0)
			zeroInDegree.push(v);

	while(!zeroInDegree.empty())
	{
		int v = zeroInDegree.front();
		zeroInDegree.pop();

		topoOrder.push_back(v);

		for(int ind = 0; ind < (int) adjList[v].size(); ind++)
		{
			int nextV = adjList[v][ind];

			inDegree[nextV]--;
			if(inDegree[nextV] == 0)
				zeroInDegree.push(nextV);
		}
	}
}
