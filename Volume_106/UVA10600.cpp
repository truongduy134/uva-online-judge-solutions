/*******************************************************************************
 * Author: Nguyen Truong Duy
 ********************************************************************************/

/* Methodology:
 *	+ The problem asks us to compute the total edge weight of the minimum spanning tree T
 *		and of the second-best minimum spanning tree T'
 *
 *	+ To compute the edge weight of minimum spanning tree T, use Kruskal's algorithm
 *	  (we will have to implement the class UnionFind).
 *	  Time complexity: O(E log V) (roughly)
 *
 *	+ To compute the edge weight of the second-best minimum spanning tree T', we use
 *		the following theorem:
 *	Let T be a minimum spanning tree. Then there exists a second-best minimum spanning
 *	tree T' such that T' = T - {u, v} + {w, x} (where {u, v} is an edge in T, and
 *	{w, x} in an edge not in T).
 *
 *	+ Following the above theorem, we compute all the values maxPathWeight[u][v] which is
 *		the maximum edge weight among all edges in the path from u to v in the minimum
 *		spanning tree T.
 *	  Then for each edge {u, v} not in T, we compute the cost
 *			f(u, v) = |T| - maxPathWeight[u][v] + |{u, v}| (|T| is the total cost
 *		of the MST T, and |{u, v}| is the weight of the edge {u, v})
 *	  We choose the minimum among f(u, v) to be the cost of the second-best MST.
 *	+ Time complexity: O(V^2) to compute the second-best MST.
 */

#include <cstdio>
#include <vector>
#include <algorithm>
#include <utility>
#include <queue>

using namespace std;

class UnionFind {
private:
	vector<int> _rank, _parent;

	int getLeader(int ele);
public:
	UnionFind(int mSize);

	bool areInSameSet(int eleOne, int eleTwo);
	void unionSet(int eleOne, int eleTwo);
};

UnionFind::UnionFind(int mSize)
{
	_rank.assign(mSize, 0);
	_parent.assign(mSize, 0);
	for(int i = 0; i < mSize; i++)
		_parent[i] = i;
}

int UnionFind::getLeader(int ele)
{
	if(_parent[ele] == ele)
		return ele;
	_parent[ele] = getLeader(_parent[ele]);
	return _parent[ele];
}

bool UnionFind::areInSameSet(int eleOne, int eleTwo)
{
	return getLeader(eleOne) == getLeader(eleTwo);
}

void UnionFind::unionSet(int eleOne, int eleTwo)
{
	int leaderOne = getLeader(eleOne);
	int leaderTwo = getLeader(eleTwo);

	if(leaderOne == leaderTwo)
		return;

	if(_rank[leaderOne] < _rank[leaderTwo])
	{
		_parent[leaderOne] = leaderTwo;
	}
	else
	{
		_parent[leaderTwo] = leaderOne;
		if(_rank[leaderOne] == _rank[leaderTwo])
			_rank[leaderOne]++;
	}
}

const int MAX_NUM_V = 100;

int computeMST(vector<pair<int, pair<int, int> > > & edgeList, int numV,
	       vector<vector<pair<int, int> > > & mstAdjList,
	       vector<pair<int, pair<int, int> > > & notInMstEdgeList);
int computeSecondBestMST(const vector<vector<pair<int, int> > > & mstAdjList, 
			 const vector<pair<int, pair<int, int> > > & notInMstEdgeList,
			 int mstCost);
int findMaxPathWeightBFS(const vector<vector<pair<int, int> > > & mstAdjList, int src, int dest);

int main(void)
{
	int T, numV, numE, u, v, weight, minMST, secondMinMST;
	vector<pair<int, pair<int, int> > > edgeList;
	vector<pair<int, pair<int, int> > > notInMstEdgeList;
	vector<vector<pair<int, int> > > mstAdjList;
	
	scanf("%d", &T);
	while(T)
	{
		scanf("%d %d", &numV, &numE);
		
		edgeList.clear();
		for(int e = 0; e < numE; e++)
		{
			scanf("%d %d %d", &u, &v, &weight);
			u--;
			v--;
			edgeList.push_back(pair<int, pair<int, int> > (weight,
				pair<int, int> (u, v)));
		}

		minMST = computeMST(edgeList, numV, mstAdjList, notInMstEdgeList);
		secondMinMST = computeSecondBestMST(mstAdjList, notInMstEdgeList, minMST);

		printf("%d %d\n", minMST, secondMinMST);
		T--;
	}
	return 0;
}

int computeMST(vector<pair<int, pair<int, int> > > & edgeList, int numV,
	       vector<vector<pair<int, int> > > & mstAdjList,
	       vector<pair<int, pair<int, int> > > & notInMstEdgeList)
{
	mstAdjList.assign(numV, vector<pair<int, int> > ());
	notInMstEdgeList.clear();

	UnionFind disjointForest(numV);

	sort(edgeList.begin(), edgeList.end());

	int mstCost = 0;
	for(int e = 0; e < (int) edgeList.size(); e++)
	{
		int weight = edgeList[e].first;
		int u = edgeList[e].second.first;
		int v = edgeList[e].second.second;

		if(disjointForest.areInSameSet(u, v) == false)
		{
			disjointForest.unionSet(u, v);
			mstCost += weight;
			mstAdjList[u].push_back(pair<int, int> (v, weight));
			mstAdjList[v].push_back(pair<int, int> (u, weight));
		}
		else
			notInMstEdgeList.push_back(pair<int, pair<int, int> >(weight, pair<int, int> (u, v)));
	}

	return mstCost;
}

int computeSecondBestMST(const vector<vector<pair<int, int> > > & mstAdjList, 
			 const vector<pair<int, pair<int, int> > > & notInMstEdgeList,
			 int mstCost)
{
	int numV = (int) mstAdjList.size();

	// maxPathWeight[u][v] = maximum edge weight among all edges in the path from u to v in 
	// the minimum spanning tree T.
	int maxPathWeight[MAX_NUM_V][MAX_NUM_V];

	// Initialization
	for(int u = 0; u < numV; u++)
		for(int v = 0; v < numV; v++)
			maxPathWeight[u][v] = -1;
	for(int u = 0; u < numV; u++)
		maxPathWeight[u][u] = 0;

	// Compute all values of maxPathWeight[u][v]
	for(int u = 0; u < numV; u++)
		for(int v = u + 1; v < numV; v++)
		{
			maxPathWeight[u][v] = findMaxPathWeightBFS(mstAdjList, u, v);
			maxPathWeight[v][u] = maxPathWeight[u][v];
		}

	int secondMinMst = -1;
	for(int e = 0; e < (int) notInMstEdgeList.size(); e++)
	{
		int weight = notInMstEdgeList[e].first;
		int u = notInMstEdgeList[e].second.first;
		int v = notInMstEdgeList[e].second.second;

		int cost = mstCost + weight - maxPathWeight[u][v];
		if(secondMinMst < 0 || cost < secondMinMst)
			secondMinMst = cost;
	}

	return secondMinMst;
}

// Return the maximum edge weight among all edges in the shortest path (in terms of the number of
// edges) from u to v in the given graph
// Underlying algorithm: BFS (breadth-first search)
int findMaxPathWeightBFS(const vector<vector<pair<int, int> > > & adjList, int src, int dest)
{
	int numV = (int) adjList.size();
	vector<bool> visited(numV, false);

	queue<pair<int, int> > vQueue;
	vQueue.push(pair<int, int> (src, 0));
	visited[src] = true;

	while(!vQueue.empty())
	{
		int v = vQueue.front().first;
		int maxPWeight = vQueue.front().second;
		vQueue.pop();

		if(v == dest)
			return maxPWeight;

		for(int ind = 0; ind < (int) adjList[v].size(); ind++)
		{
			int nextV = adjList[v][ind].first;

			if(visited[nextV] == false)
			{
				visited[nextV] = true;
				int weight = adjList[v][ind].second;
				if(weight > maxPWeight)
					maxPWeight = weight;

				vQueue.push(pair<int, int> (nextV, maxPWeight));
			}
		}
	}
	return -1;
}
