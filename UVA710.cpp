/*******************************************************
 * Author: Nguyen Truong Duy
 *******************************************************/

/* Methodology:
 *  + Let the original grid be of size n x n
 *    We add a boundary which consists of empty cells only around the original grid.
 *    So we obtain a new grid L of size (n + 2) x (n + 2)
 *
 *  + This can be modelled as a shortest path on an unweight graph problem.
 *  + Let us construct a graph G as follows:
 *      + The starting and ending piece locations (S and T) are vertices.
 *      + All empty cells in the grid L are vertices as well.
 *      + Two vertices are connected if and only if
 *          - They are in the SAME ROW or COLUMN.
 *          - There is no piece betwen the two vertices (The two vertices can be pieces)
 *  + Now we want to find a path of shortest length from S to T. The length of such a path
 *    equals the number of segments to join S and T.
 *
 *  + Time complexity: O(n^2) where n is the size of the orignal grid.
 */

#include <queue>
#include <cstdio>
#include <utility>

using namespace std;

const int MAX_SIZE = 75;
const char HAS_PIECE = 'X';
const int INFINITY = 10000;
const char EMPTY = ' ';

int findShortestPathBFS(const char board[][MAX_SIZE + 2], int numR, int numC,
                        int fromR, int fromC, int toR, int toC);

int main(void)
{
    int numR, numC, fromR, fromC, toR, toC, caseId, pairId, minDist;
    char board[MAX_SIZE + 2][MAX_SIZE + 2], trash[MAX_SIZE + 1];

    caseId = 1;
    while(1)
    {
        scanf("%d %d", &numC, &numR);
        if(numR == 0 && numC == 0)
            break;

        /* Add outer boundary */
        numR += 2;
        numC += 2;

        gets(trash);
        for(int i = 1; i < numR - 1; i++)
            gets(&board[i][1]);

        for(int row = 0; row < numR; row++)
        {
            board[row][0] = EMPTY;
            board[row][numC - 1] = EMPTY;
        }
        for(int col = 0; col < numC; col++)
        {
            board[0][col] = EMPTY;
            board[numR - 1][col] = EMPTY;
        }

        printf("Board #%d:\n", caseId);
        pairId = 1;
        while(1)
        {
            scanf("%d %d %d %d", &fromC, &fromR, &toC, &toR);
            if(!(fromR || fromC || toR || toC))
                break;

            minDist = findShortestPathBFS(board, numR, numC, fromR, fromC, toR, toC);
            printf("Pair %d:", pairId);
            if(minDist < 0)
                printf(" impossible.\n");
            else
                printf(" %d segments.\n", minDist);

            pairId++;
        }
        printf("\n");

        caseId++;
    }
    return 0;
}

int findShortestPathBFS(const char board[][MAX_SIZE + 2], int numR, int numC,
                        int fromR, int fromC, int toR, int toC)
{
    queue<pair<int, int> > vQueue;
    vQueue.push(pair<int, int>(fromR, fromC));

    int minDist[MAX_SIZE + 2][MAX_SIZE + 2], row, col, nextR, nextC;
    for(row = 0; row < numR; row++)
        for(col = 0; col < numC; col++)
            minDist[row][col] = INFINITY;
    minDist[fromR][fromC] = 0;

    while(!vQueue.empty())
    {
        row = vQueue.front().first;
        col = vQueue.front().second;
        vQueue.pop();

        if(row == toR && col == toC)
            return minDist[toR][toC];

        // Go vertically
        for(int offset = -1; offset <= 1; offset += 2)
        {
            nextR = row + offset;
            while(nextR >= 0 && nextR < numR)
            {
                if(!(nextR == toR && col == toC) && board[nextR][col] == HAS_PIECE)
                    break;

                if(minDist[nextR][col] == INFINITY)
                {
                    minDist[nextR][col] = minDist[row][col] + 1;
                    vQueue.push(pair<int, int>(nextR, col));
                }
                nextR += offset;
            }
        }

        // Go horizontally
        for(int offset = -1; offset <= 1; offset += 2)
        {
            nextC = col + offset;
            while(nextC >= 0 && nextC < numC)
            {
                if(!(row == toR && nextC == toC) && board[row][nextC] == HAS_PIECE)
                    break;

                if(minDist[row][nextC] == INFINITY)
                {
                    minDist[row][nextC] = minDist[row][col] + 1;
                    vQueue.push(pair<int, int>(row, nextC));
                }
                nextC += offset;
            }
        }
    }

    return -1;
}
