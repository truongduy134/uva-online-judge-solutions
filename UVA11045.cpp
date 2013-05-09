#include <cstdio>
#include <vector>

using namespace std;

#define NUM_SIZE_SHIRT 6
#define MAX_LEN 10

bool findAndAugmentPath(const vector<vector<int> > & adjList, int leftV,
                        vector<int> & matchedLeftPartner, vector<bool> & visited);
void readAndBuildBipartiteGraph(vector<vector<int> > & adjList, int numPeople, int numShirt);
int getFirstShirtIndex(char sizeShirt[]);
int getSizeMaximumMatching(const vector<vector<int> > & adjList, int sizeLeftSet);

int main(void)
{
    int T, numShirt, numPeople;
    vector<vector<int> > adjList;

//    freopen("in.txt", "r", stdin);

    scanf("%d", &T);
    while(T)
    {
        scanf("%d %d", &numShirt, &numPeople);

        readAndBuildBipartiteGraph(adjList, numPeople, numShirt);

        // This is a perfect matching problem
        if(getSizeMaximumMatching(adjList, numPeople) != numPeople)
            printf("NO\n");
        else
            printf("YES\n");

        T--;
    }

    return 0;
}

void readAndBuildBipartiteGraph(vector<vector<int> > & adjList, int numPeople, int numShirt)
{
    int shirtId;
    vector<int> emptyList;
    char sizeShirt[MAX_LEN + 1];

    adjList.assign(numPeople + numShirt, emptyList);

    for(int personId = 0; personId < numPeople; personId++)
    {
        for(int shirt = 0; shirt < 2; shirt++)
        {
            scanf("%s", sizeShirt);
            shirtId = getFirstShirtIndex(sizeShirt);
            while(shirtId < numShirt)
            {
                adjList[personId].push_back(shirtId + numPeople);
                shirtId += NUM_SIZE_SHIRT;
            }
        }
    }
}

int getFirstShirtIndex(char sizeShirt[])
{
    if(sizeShirt[1] == '\0')
    {
        switch(sizeShirt[0])
        {
            case 'S':
                return 0;
            case 'M':
                return 1;
            case 'L':
                return 2;
        }
    }

    if(sizeShirt[2] == '\0')
    {
        switch(sizeShirt[1])
        {
            case 'S':
                return 3;
            case 'L':
                return 4;
        }
    }

    return 5;
}

int getSizeMaximumMatching(const vector<vector<int> > & adjList, int sizeLeftSet)
{
    int numV = (int) adjList.size();
    vector<int> matchedLeftPartner(numV, -1);
    vector<bool> visited;

    int maxNumMatching = 0;
    for(int leftV = 0; leftV < sizeLeftSet; leftV++)
    {
        visited.assign(sizeLeftSet, false);
        if(findAndAugmentPath(adjList, leftV, matchedLeftPartner, visited))
        {
            maxNumMatching++;
        }
    }

    return maxNumMatching;
}

bool findAndAugmentPath(const vector<vector<int> > & adjList, int leftV,
                        vector<int> & matchedLeftPartner, vector<bool> & visited)
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
            matchedLeftPartner[rightV] = leftV;
            return true;
        }
    }
    return false;
}
