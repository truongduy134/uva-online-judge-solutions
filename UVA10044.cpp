/*******************************************************
 * Author: Nguyen Truong Duy
 *******************************************************/

/* Methodology:
 *  1) Parse inputs to get the authors' names.
 *  2) Construct a graph with the set of authors as the vertice set.
 *    Two authors are connected in this graph is they co-author a common paper.
 *  3) Run BFS from the vertex representing Erdos.
 *
 * Note: the first two steps are quite tedius.
 *
 * Important!!!
 *      + The number of authors is quite large. Therefore, any attemp to use adjacency matrix
 *      (to be used for BFS, or for checking parallel edges) will result in Runtime-error.
 */

#include <map>
#include <vector>
#include <string>
#include <cstdio>
#include <utility>
#include <cstring>
#include <queue>

using namespace std;

const int MAX_LEN_LINE = 1000000;
const int MAX_LEN_TRASH = 2;
const char ERDOS_NAME[] = "Erdos, P.";

void readAndInitEdgeList(int numPaper, map<string, int> & mapNameToId, vector<pair<int, int> > & edgeList);
void getAuthorListFromTitle(char paperTitle[], vector<string> & authorList);
void buildAdjList(vector<vector<int> > & adjList, int numV, const vector<pair<int, int> > & edgeList);
void computeErdosNum(const vector<vector<int> > & adjList, vector<int> & erdosNumVect);

int main(void)
{
    int numPaper, numQuery, T, numV, caseId;
    char name[MAX_LEN_LINE + 1], trash[MAX_LEN_TRASH + 1];
    map<string, int> mapNameToId;
    map<string, int>::iterator it;
    vector<vector<int> > adjList;
    vector<pair<int, int> > edgeList;
    vector<int> erdosNumVect;

    scanf("%d", &T);
    caseId = 1;
    while(caseId <= T)
    {
        scanf("%d %d", &numPaper, &numQuery);
        gets(trash);

        readAndInitEdgeList(numPaper, mapNameToId, edgeList);
        numV = mapNameToId.size();

        buildAdjList(adjList, numV, edgeList);

        computeErdosNum(adjList, erdosNumVect);

        // Query
        printf("Scenario %d\n", caseId);
        for(int i = 0; i < numQuery; i++)
        {
            gets(name);
            it = mapNameToId.find(name);

            printf("%s ", name);
            if(it == mapNameToId.end() || erdosNumVect[it->second] < 0)
                printf("infinity\n");
            else
                printf("%d\n", erdosNumVect[it->second]);
        }

        caseId++;
    }
    return 0;
}

void readAndInitEdgeList(int numPaper, map<string, int> & mapNameToId, vector<pair<int, int> > & edgeList)
{
    char line[MAX_LEN_LINE + 1];

    mapNameToId.clear();
    edgeList.clear();

    mapNameToId[ERDOS_NAME] = 0;
    int idToAssign = 1, id;

    vector<string> authorList;
    vector<int> idList;
    map<string, int>::iterator it;

    for(int i = 0; i < numPaper; i++)
    {
        gets(line);

        getAuthorListFromTitle(line, authorList);
        idList.clear();

        for(int k = 0; k < (int) authorList.size(); k++)
        {
            it = mapNameToId.find(authorList[k]);
            if(it == mapNameToId.end())
            {
                mapNameToId[authorList[k]] = idToAssign;
                id = idToAssign;
                idToAssign++;
            }
            else
                id = it->second;

            idList.push_back(id);
        }

        for(int i = 0; i < (int) idList.size(); i++)
            for(int j = i + 1; j < (int) idList.size(); j++)
                edgeList.push_back(pair<int, int> (idList[i], idList[j]));
    }
}

void getAuthorListFromTitle(char paperTitle[], vector<string> & authorList)
{
    int i, commaInd, startName;

    authorList.clear();

    for(i = 0, commaInd = 0, startName = 0; paperTitle[i] != '\0'; i++)
    {
        if(paperTitle[i] == ',')
        {
            commaInd++;
        }

        if(commaInd == 2 || paperTitle[i] == ':')
        {
            // Found end of a name
            authorList.push_back(string(paperTitle + startName, paperTitle + i));
            startName = i + 2;
            commaInd = 0;
        }

        if(paperTitle[i] == ':')
            break;
    }
}

void buildAdjList(vector<vector<int> > & adjList, int numV, const vector<pair<int, int> > & edgeList)
{
    adjList.assign(numV, vector<int> ());
    for(int i = 0; i < (int) edgeList.size(); i++)
        if(edgeList[i].first != edgeList[i].second)
        {
            adjList[edgeList[i].first].push_back(edgeList[i].second);
            adjList[edgeList[i].second].push_back(edgeList[i].first);
        }
}

void computeErdosNum(const vector<vector<int> > & adjList, vector<int> & erdosNumVect)
{
    int numV = (int) adjList.size();

    erdosNumVect.assign(numV, -1);

    // Asumption: 0 is the vertex id representing Erdos
    queue<int> vQueue;
    vQueue.push(0);
    erdosNumVect[0] = 0;

    while(!vQueue.empty())
    {
        int curId = vQueue.front();
        vQueue.pop();

        for(int ind = 0; ind < (int) adjList[curId].size(); ind++)
        {
            int nextId = adjList[curId][ind];

            if(erdosNumVect[nextId] < 0)
            {
                // Not visited yet
                erdosNumVect[nextId] = erdosNumVect[curId] + 1;
                vQueue.push(nextId);
            }
        }
    }
}
