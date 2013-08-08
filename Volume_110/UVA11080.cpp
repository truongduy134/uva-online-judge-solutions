/*******************************************************
 * Author: Nguyen Truong Duy
 *******************************************************/

/* Methodology:
 *  + We can model the problem as a graph problem as follows:
 *      - Let G = (V, E) where
 *          * Each junction is a vertex.
 *          * An edge corresponds to a street connection two junctions.
 *      - Note that the graph is undirected and may be disconnected.
 *
 *  + The problem asks us to check if G is bipartite (or 2-colorable).
 *  + If so, return the smaller size among the two bipartite sets.
 *  + Let A, B be two bipartite sets of G.
 *    Then min(|A|, |B|) = sum(g(|A(i)|, |B(i)|)) where
 *          A(i), B(i) are bipartite sets of the i-th connected component of G.
 *    g(|A(i)|, |B(i)|) = 1 if A(i) or B(i) is empty (i.e. the connected componenet has a single vertex)
 *    g(|A(i)|, |B(i)|) = min(|A(i)|, |B(i)|) otherwise.
 *
 *  + We can simplify the above formula as:
 *          min(|A|, |B|) = sum(max(1, min(|A(i)|, |B(i)|)))
 *
 *  + Time complexity: O(|V| + |E|)
 */

#include <cstdio>
#include <vector>

using namespace std;

const int NO_COLOR = -1;
const int BLACK = 0;
const int WHITE = 1;

int computeMinBipartiteSet(vector<vector<int> > & adjList);
void colorGraphByDFS(const vector<vector<int> > & adjList, int v, int color,
                     vector<int> & vColor, int sizeColor[2], bool * isBipartite);
int getMin(int A, int B);
int getOppositeColor(int color);
int getMax(int A, int B);

int main(void)
{
    int T, numV, numE;
    vector<vector<int> > adjList;
    vector<int> emptyList;

    scanf("%d", &T);
    while(T)
    {
        scanf("%d %d", &numV, &numE);

        adjList.assign(numV, emptyList);
        int u, v;
        for(int e = 0; e < numE; e++)
        {
            scanf("%d %d", &u, &v);
            adjList[u].push_back(v);
            adjList[v].push_back(u);
        }

        int minBipartiteSet = computeMinBipartiteSet(adjList);
        printf("%d\n", minBipartiteSet);

        T--;
    }
    return 0;
}

int computeMinBipartiteSet(vector<vector<int> > & adjList)
{
    int numV = (int) adjList.size();

    vector<int> vColor(numV, NO_COLOR);

    int minBipartiteSet = 0;

    for(int v = 0; v < numV; v++)
    {
        if(vColor[v] == NO_COLOR)
        {
            int sizeColor[2] = {0};
            bool isBipartite = true;

            colorGraphByDFS(adjList, v, BLACK, vColor, sizeColor, &isBipartite);

            if(!isBipartite)
                return -1;
            minBipartiteSet += max(1, getMin(sizeColor[BLACK], sizeColor[WHITE]));
        }
    }

    return minBipartiteSet;
}

void colorGraphByDFS(const vector<vector<int> > & adjList, int v, int color,
                     vector<int> & vColor, int sizeColor[2], bool * isBipartite)
{
    vColor[v] = color;
    sizeColor[color]++;

    for(int ind = 0; ind < (int) adjList[v].size(); ind++)
    {
        int neighbor = adjList[v][ind];

        if(vColor[neighbor] == NO_COLOR)
        {
            colorGraphByDFS(adjList, neighbor, getOppositeColor(color), vColor, sizeColor, isBipartite);

            if(*isBipartite == false)
                return;
        }
        else
        {
            if(vColor[neighbor] == vColor[v])
            {
                *isBipartite = false;
                return;
            }
        }
    }
}
int getMin(int A, int B)
{
    if(A < B)
        return A;
    return B;
}

int getMax(int A, int B)
{
    if(A > B)
        return A;
    return B;
}

int getOppositeColor(int color)
{
    // Assumption: therea are only 2 colors, BLACK = 0, WHITE = 1
    return (color + 1) % 2;
}
