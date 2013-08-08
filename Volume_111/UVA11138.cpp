#include <cstdio>
#include <vector>

using namespace std;

void readAndBuildBipartiteGraph(vector<vector<int> > & adjList, int sizeLeftSet, int sizeRightSet);
int getMaximumNumberOfMatching(const vector<vector<int> > & adjList, int sizeLeftSet);
bool findAndAugmentPath(const vector<vector<int> > & adjList, int leftV, vector<int> & matchedLeftPartner,
                        vector<bool> & visited);

int main(void)
{
    int T, numBolts, numNuts, caseId;
    vector<vector<int> > adjList;

//    freopen("in.txt", "r", stdin);

    scanf("%d", &T);
    caseId = 1;
    while(caseId <= T)
    {
        scanf("%d %d", &numBolts, &numNuts);

        readAndBuildBipartiteGraph(adjList, numBolts, numNuts);

        printf("Case %d: a maximum of %d nuts and bolts can be fitted together\n",
               caseId, getMaximumNumberOfMatching(adjList, numBolts));
        caseId++;
    }

    return 0;
}

void readAndBuildBipartiteGraph(vector<vector<int> > & adjList, int sizeLeftSet, int sizeRightSet)
{
    vector<int> emptyList;
    adjList.assign(sizeLeftSet + sizeRightSet, emptyList);

    int isAdjacent, leftV, rightV;
    for(leftV = 0; leftV < sizeLeftSet; leftV++)
        for(rightV = 0; rightV < sizeRightSet; rightV++)
        {
            scanf("%d", &isAdjacent);
            if(isAdjacent)
                adjList[leftV].push_back(rightV + sizeLeftSet);
        }
}

int getMaximumNumberOfMatching(const vector<vector<int> > & adjList, int sizeLeftSet)
{
    int numV = (int) adjList.size();

    vector<int> matchedLeftPartner(numV, -1);
    vector<bool> visited;

    int numMatching = 0;
    for(int leftV = 0; leftV < sizeLeftSet; leftV++)
    {
        visited.assign(sizeLeftSet, false);
        if(findAndAugmentPath(adjList, leftV, matchedLeftPartner, visited))
            numMatching++;
    }

    return numMatching;
}

bool findAndAugmentPath(const vector<vector<int> > & adjList, int leftV, vector<int> & matchedLeftPartner,
                        vector<bool> & visited)
{
    if(visited[leftV])
        return false;

    visited[leftV] = true;

    int rightV;
    for(int ind = 0; ind < (int) adjList[leftV].size(); ind++)
    {
        rightV = adjList[leftV][ind];
        if(matchedLeftPartner[rightV] == -1 || findAndAugmentPath(adjList, matchedLeftPartner[rightV],
                                                                  matchedLeftPartner, visited))
        {
            // augment
            matchedLeftPartner[rightV] = leftV;
            return true;
        }
    }

    return false;
}
