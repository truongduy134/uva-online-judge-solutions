#include <cstdio>
#include <vector>
#include <cstdlib>

using namespace std;

typedef struct {
	int loveId, hateId;
} Voter;

#define MAX_LEN 10

int buildBipartiteGraph(vector<vector<int> > & adjList, vector<Voter> & catLovers, vector<Voter> & dogLovers);
int getNumMaximumMatching(const vector<vector<int> > & adjList, int sizeLeftSet);
bool findAndAugmentPath(const vector<vector<int> > & adjList, int leftV, vector<int> & matchedLeftPartner, vector<bool> &visited);

int main(void)
{
	vector<Voter> catLovers, dogLovers;
	vector<vector<int> > adjList;
	int T, numCat, numDog, numVoter;
	char love[MAX_LEN], hate[MAX_LEN];

	scanf("%d", &T);
	while(T)
	{
		catLovers.clear();
		dogLovers.clear();

		scanf("%d %d %d", &numCat, &numDog, &numVoter);
		for(int i = 0; i < numVoter; i++)
		{
			scanf("%s %s", love, hate);
			Voter newVoter;
			newVoter.loveId = atoi(&love[1]);
			newVoter.hateId = atoi(&hate[1]);
			if(love[0] == 'C')
				catLovers.push_back(newVoter);
			else
				dogLovers.push_back(newVoter);
		}
		
		buildBipartiteGraph(adjList, catLovers, dogLovers);

		/* This is an maximum independent set problem on a bipartite graph */
		printf("%d\n", numVoter - getNumMaximumMatching(adjList, (int) catLovers.size()));

		T--;
	}

	return 0;
}

/* Description of the bipartite graph:
 *	+ Bipartite set 1: set of cat lovers.
 *	+ Bipartite set 2: set of dog lovers.
 * There is an edge between a cat lover A and a dog lover B iff
 *		The candidate A wants to keep is the one B wants to throw out,
 *			or vice versa.
 * So they cannot be satisfied both at the same time.
 *
 * Hence, our problem is reduced to finding the size of maximum independent set on this graph 
 */  
int buildBipartiteGraph(vector<vector<int> > & adjList, vector<Voter> & catLovers, vector<Voter> & dogLovers)
{
	int numCatLover = (int) catLovers.size(), numDogLover = (int) dogLovers.size();
	vector<int> emptyList;
	adjList.assign(numCatLover + numDogLover, emptyList);

	for(int catId = 0; catId < numCatLover; catId++)
		for(int dogId = 0; dogId < numDogLover; dogId++)
		{
			if(catLovers[catId].loveId == dogLovers[dogId].hateId ||
			   catLovers[catId].hateId == dogLovers[dogId].loveId)
			{
				adjList[catId].push_back(dogId + numCatLover);
			}
		}
}

int getNumMaximumMatching(const vector<vector<int> > & adjList, int sizeLeftSet)
{
	int numV = (int) adjList.size();
	vector<int> matchedLeftPartner(numV, -1);
	vector<bool> visited;

	int maxNumMatching = 0;
	for(int leftV = 0; leftV < sizeLeftSet; leftV++)
	{
		visited.assign(sizeLeftSet, false);
		if(findAndAugmentPath(adjList, leftV, matchedLeftPartner, visited))
			maxNumMatching++;
	}

	return maxNumMatching;
}

bool findAndAugmentPath(const vector<vector<int> > & adjList, int leftV, vector<int> & matchedLeftPartner, vector<bool> &visited)
{
	if(visited[leftV])
		return false;
	
	visited[leftV] = true;
	int rightV;
	for(int ind = 0; ind < (int) adjList[leftV].size(); ind++)
	{
		rightV = adjList[leftV][ind];

		if(matchedLeftPartner[rightV] == -1 ||
		   findAndAugmentPath(adjList, matchedLeftPartner[rightV], matchedLeftPartner, visited))
		{
			matchedLeftPartner[rightV] = leftV;
			return true;
		}
	}

	return false;
}
