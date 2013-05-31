/*******************************************************
 * Author: Nguyen Truong Duy
 *******************************************************/

/* Methodology:
 *  + This problem can be modeled as a graph problem as follows:
 *      - Each stone is a vertex
 *      - Between any two stone, there is an edge connecting them with weight equal
 *          to the Euclidean distance between the two locations.
 *  + Consider P = v(i) ... v(j) be a path from v(i) to v(j)
 *    Define f(P) = the maximum weight among all edges in P.
 *  + We need to find min f(P) for all paths from the given stone U and V.
 *
 *  + Solution:
 *      - Method 1: Use a simple O(V^3) Floy-Warshall's algorithm
 *      - Method 2: (Time complexity: O((V + E) log V)
 *          * Compute the Minimum Spanning Tree T of the given graph using Kruskal's algorithm
 *          * Find a path P from U to V in T using DFS or BFS
 *          * Find the maximum weight of edges in P.
 */

#include <stdio.h>
#include <math.h>

const int MAX_NUM_STONE = 200;

typedef struct
{
    double x, y;
} Point;

double computeEuclidDist(Point * p1, Point * p2);
double computeSquare(double x);
void computeMinMaxFloyWarshall(double mat[][MAX_NUM_STONE], int numV);

int main(void)
{
    double miniMaxDist[MAX_NUM_STONE][MAX_NUM_STONE];
    Point pointArr[MAX_NUM_STONE];
    int numStone, i, j, caseId = 1;

    caseId = 1;
    while(1)
    {
        scanf("%d", &numStone);
        if(!numStone)
            break;

        for(i = 0; i < numStone; i++)
            scanf("%lf %lf", &pointArr[i].x, &pointArr[i].y);

        for(i = 0; i < numStone; i++)
            miniMaxDist[i][i] = 0.0;
        for(i = 0; i < numStone; i++)
            for(j = i + 1; j < numStone; j++)
            {
                miniMaxDist[i][j] = computeEuclidDist(&pointArr[i], &pointArr[j]);
                miniMaxDist[j][i] = miniMaxDist[i][j];
            }

        computeMinMaxFloyWarshall(miniMaxDist, numStone);

        printf("Scenario #%d\n", caseId);
        printf("Frog Distance = %.3lf\n\n", miniMaxDist[0][1]);

        caseId++;
    }
    return 0;
}

double computeEuclidDist(Point * p1, Point * p2)
{
    return sqrt(computeSquare(p1->x - p2->x) + computeSquare(p1->y - p2->y));
}

double computeSquare(double x)
{
    return x * x;
}

void computeMinMaxFloyWarshall(double mat[][MAX_NUM_STONE], int numV)
{
    int k, u, v;
    double maxW ;

    for(k = 0; k < numV; k++)
        for(u = 0; u < numV; u++)
            for(v = 0; v < numV; v++)
            {
                maxW = mat[u][k];
                if(maxW < mat[k][v])
                    maxW = mat[k][v];

                /* Minimize */
                if(maxW < mat[u][v])
                    mat[u][v] = maxW;
            }
}
