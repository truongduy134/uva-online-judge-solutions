/*******************************************************
 * Author: Nguyen Truong Duy
 *******************************************************/

/* Methodology:
 *  + Consider a matrix N x M.
 *  + Pass 1:
 *      - If each column does not have exactly 2 one-entry, then it is not
 *        an incidence matrix of a simple graph.
 *  + Pass 2: Check if there are parallel edges by using another matrix that
 *              presents the adjacent matrix.
 *  + Special case: If M = 0, then clearly it is an incidence matrix of a simple graph without edges.
 *                  If N = 1 and M != 0, then clearly it is NOT an incidence matrix of a simple graph.
 */

#include <stdio.h>
#include <string.h>

const int MAX_NUM_V = 8;
const int MAX_NUM_E = 64;

int isValidIncidenceMatOfSimpleGraph(int incidenceMat[MAX_NUM_V][MAX_NUM_E], int numV, int numE);

int main(void)
{
    int incidenceMat[MAX_NUM_V][MAX_NUM_E], T, numE, numV, v, e;

    scanf("%d", &T);
    while(T)
    {
        scanf("%d %d", &numV, &numE);

        for(v = 0; v < numV; v++)
            for(e = 0; e < numE; e++)
                scanf("%d", &incidenceMat[v][e]);

        printf("%s\n", isValidIncidenceMatOfSimpleGraph(incidenceMat, numV, numE) ? "Yes" : "No");

        T--;
    }
    return 0;
}

int isValidIncidenceMatOfSimpleGraph(int incidenceMat[MAX_NUM_V][MAX_NUM_E], int numV, int numE)
{
    int numOneCol, e, v, adjMat[MAX_NUM_V][MAX_NUM_V], vArr[2];

    if(numV < 2 && numE != 0)
        return 0;
    if(numE == 0)
        return 1;

    memset(adjMat, 0, MAX_NUM_V * MAX_NUM_V * sizeof(int));
    /* Pass 1 and Pass 2 combined*/
    for(e = 0; e < numE; e++)
    {
        numOneCol = 0;
        for(v = 0; v < numV; v++)
        {
            if(incidenceMat[v][e] != 0 && incidenceMat[v][e] != 1)
                return 0;
            else
            {
                if(incidenceMat[v][e])
                {
                    if(numOneCol < 2)
                    {
                        vArr[numOneCol] = v;
                        numOneCol++;
                    }
                    else
                        return 0;
                }
            }
        }

        /* If there are less than 2 one-entries, also return false */
        if(numOneCol < 2)
            return 0;

        /* Check for parallel edges */
        if(adjMat[vArr[0]][vArr[1]])
            return 0;
        else
        {
            adjMat[vArr[0]][vArr[1]] = 1;
            adjMat[vArr[1]][vArr[0]] = 1;
        }
    }

    return 1;
}
