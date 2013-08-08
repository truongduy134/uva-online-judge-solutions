#include <cstdio>
#include <vector>
#include <utility>
#include <queue>
#include <cstring>

using namespace std;

#define MAX_NUM_V 101

int runEdmondsKarp(vector<vector<pair<int, int> > > & residualGraph, int indexInAdjList[][MAX_NUM_V],
                   int source, int sink);
bool runBreadthFirstSearch(vector<vector<pair<int, int> > > & residualGraph, int source, int sink,
                           vector<int> & parentArr);
int getAugmentFlow(vector<vector<pair<int, int> > > & residualGraph, int indexInAdjList[][MAX_NUM_V],
                   vector<int> & parentArr, int source, int sink);
void updateResidualGraph(vector<vector<pair<int, int> > > & residualGraph, int indexInAdjList[][MAX_NUM_V],
                         vector<int> & parentArr, int augmentFlow, int source, int sink);

int main(void)
{
    int numV, caseId, source, sink, numE, vOne, vTwo, capacity, ind;
    vector<vector<pair<int, int> > > residualGraph;
    vector<pair<int, int> > emptyList;
    int indexInAdjList[MAX_NUM_V][MAX_NUM_V];

 //   freopen("in.txt", "r", stdin);

    caseId = 1;
    while(1)
    {
        scanf("%d", &numV);
        if(numV== 0)
            break;

        residualGraph.assign(numV, emptyList);
        memset(indexInAdjList, -1, MAX_NUM_V * MAX_NUM_V * sizeof(int));

        scanf("%d %d %d", &source, &sink, &numE);
        source--;
        sink--;

        // Build residual graph
        for(int i = 0; i < numE; i++)
        {
            scanf("%d %d %d", &vOne, &vTwo, &capacity);
            vOne--;
            vTwo--;

            ind = residualGraph[vOne].size();
            if(indexInAdjList[vOne][vTwo] < 0)
            {
                residualGraph[vOne].push_back(make_pair(vTwo, capacity));
                indexInAdjList[vOne][vTwo] = ind;
            }
            else
            {
                ind = indexInAdjList[vOne][vTwo];
                residualGraph[vOne][ind].second += capacity;
            }

            ind = residualGraph[vTwo].size();
            if(indexInAdjList[vTwo][vOne] < 0)
            {
                residualGraph[vTwo].push_back(make_pair(vOne, capacity));
                indexInAdjList[vTwo][vOne] = ind;
            }
            else
            {
                ind = indexInAdjList[vTwo][vOne];
                residualGraph[vTwo][ind].second += capacity;
            }
        }

        // Run Emonds-Karp algorithm
        printf("Network %d\nThe bandwidth is %d.\n\n", caseId, runEdmondsKarp(residualGraph, indexInAdjList,
                                                                              source, sink));

        caseId++;
    }
    return 0;
}

// If indexInAdjList[u][v] = i
// Then residualGrpah[u][i].first = v
int runEdmondsKarp(vector<vector<pair<int, int> > > & residualGraph, int indexInAdjList[][MAX_NUM_V],
                   int source, int sink)
{
    int totalFlow = 0, augmentFlow;
    vector<int> parentArr;
    bool existPath;
    while(1)
    {
        existPath = runBreadthFirstSearch(residualGraph, source, sink, parentArr);
        if(!existPath)
            break;

        augmentFlow = getAugmentFlow(residualGraph, indexInAdjList, parentArr, source, sink);

        if(augmentFlow == 0)
            break;

        totalFlow += augmentFlow;

        updateResidualGraph(residualGraph, indexInAdjList, parentArr, augmentFlow, source, sink);
    }

    return totalFlow;
}

bool runBreadthFirstSearch(vector<vector<pair<int, int> > > & residualGraph, int source, int sink,
                           vector<int> & parentArr)
{
    int numV = (int) residualGraph.size();

    parentArr.assign(numV, -1);
    queue<int> mQueue;
    parentArr[source] = source;
    mQueue.push(source);

    int curV, nextV, residualCapacity;
    while(!mQueue.empty())
    {
        curV = mQueue.front();
        mQueue.pop();

        numExe++;

        if(curV == sink)
        {
            return true;
        }

        for(int ind = 0; ind < (int) residualGraph[curV].size(); ind++)
        {
            nextV = residualGraph[curV][ind].first;
            residualCapacity = residualGraph[curV][ind].second;

            if(residualCapacity > 0 && parentArr[nextV] < 0)
            {
                parentArr[nextV] = curV;
                mQueue.push(nextV);
            }
        }
    }

    return false;
}

// If indexInAdjList[u][v] = i
// Then residualGrpah[u][i].first = v
int getAugmentFlow(vector<vector<pair<int, int> > > & residualGraph, int indexInAdjList[][MAX_NUM_V],
                   vector<int> & parentArr, int source, int sink)
{
    int augmentFlow = 0, curV = sink, residualCapacity, ind, parentV;

    while(curV != source)
    {
        parentV = parentArr[curV];

        ind = indexInAdjList[parentV][curV];
        residualCapacity = residualGraph[parentV][ind].second;

        if(augmentFlow == 0 || augmentFlow > residualCapacity)
            augmentFlow = residualCapacity;

        curV = parentV;
    }

    return augmentFlow;
}

void updateResidualGraph(vector<vector<pair<int, int> > > & residualGraph, int indexInAdjList[][MAX_NUM_V],
                         vector<int> & parentArr, int augmentFlow, int source, int sink)
{
    int curV = sink, indOne, indTwo, parentV;

    while(curV != source)
    {
        parentV = parentArr[curV];

        indOne = indexInAdjList[parentV][curV];
        residualGraph[parentV][indOne].second -= augmentFlow;

        indTwo = indexInAdjList[curV][parentV];
        residualGraph[curV][indTwo].second += augmentFlow;

        curV = parentV;
    }
}
