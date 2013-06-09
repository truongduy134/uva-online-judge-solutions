/*******************************************************
 * Author: Nguyen Truong Duy
 *******************************************************/

/* Methodology:
 *  + This can be modelled as an implicit graph problem.
 *      - Each cell is either SAFE or BLOCKED_OR_DANGEROUS
 *      - We construct an unweighted, undirected graph G = (V, E)
 *      - Each SAFE cell is a vertex in G.
 *        Two SAFE cells are connected if one is to the left, to the right, or above, or below the other.
 *  + Now the problem becomes finding shortest path from source (1, 1) (if (1, 1) is SAFE) on
 *      unweight graph (This can be solved using Breath First Search).
 *
 *  + If the cell (1, 1) or (R, C) is BLOCKED_OR_DANGEROUS, then it is impossible to escape.
 *  + Otherwise, we can run Breath First Search on G to find the shortest path from (1, 1) to (R, C)
 *     (if such path exists)
 *
 *  + Now come to the part of marking dangerous cell with respect to a pokemon (X, Y) with loudness L.
 *    We just need to check those cells in the rectangular whose
 *      - Upper-left corner is (max(1, X - L), max(1, Y - L) )
 *      - Lower-right corner is (min(X + L, R), min(Y + L, C) )
 *
 *  + Timpe complextity: O(R * C + n * L * L) where R x C is the size of the forest, n is the number of
 *              pokemons, and the maximum loudness amoung all pokemons.
 */

#include <cstdio>
#include <cstring>
#include <queue>
#include <utility>

using namespace std;

const int MAX_SIZE = 200;
const int BLOCKED_OR_DANGEROUS = 1;
const int SAFE = 0;
const int VISITED = 2;
#define NUM_DIRECTION 4
const int COORD_OFFSET[NUM_DIRECTION][2] = { {0, 1}, {1, 0}, {-1, 0}, {0, -1} };

int getMinLengthPath(int grid[][MAX_SIZE], int numRow, int numCol, int srcR, int srC,
                     int destR, int destC);
bool isValidCell(int row, int col, int numRow, int numCol);
void markDangerous(int grid[][MAX_SIZE], int numRow, int numCol, int centerR, int centerC,
                   int distance);
int computeSquareEuclidDist(int rowOne, int colOne, int rowTwo, int colTwo);

int main(void)
{
    int numRow, numCol, numBlocked, row, col, numPokemon, distance,
        grid[MAX_SIZE][MAX_SIZE];

    while(1)
    {
        scanf("%d %d", &numRow, &numCol);
        if(!(numRow || numCol))
            break;

        memset(grid, SAFE, MAX_SIZE * MAX_SIZE * sizeof(int));

        scanf("%d", &numBlocked);
        for(int i = 0; i < numBlocked; i++)
        {
            scanf("%d %d", &row, &col);
            grid[row - 1][col - 1] = BLOCKED_OR_DANGEROUS;
        }

        scanf("%d", &numPokemon);
        for(int i = 0; i < numPokemon; i++)
        {
            scanf("%d %d %d", &row, &col, &distance);
            markDangerous(grid, numRow, numCol, row - 1, col - 1, distance);
        }

        int minLength = getMinLengthPath(grid, numRow, numCol, 0, 0, numRow - 1, numCol - 1);
        if(minLength < 0)
            printf("Impossible.\n");
        else
            printf("%d\n", minLength);
    }
    return 0;
}

int getMinLengthPath(int grid[][MAX_SIZE], int numRow, int numCol, int srcR, int srcC,
                     int destR, int destC)
{
    if(grid[srcR][srcC] == BLOCKED_OR_DANGEROUS ||
       grid[destR][destC] == BLOCKED_OR_DANGEROUS)
        return -1;

    queue<pair<int, pair<int, int> > > vQueue;

    vQueue.push(pair<int, pair<int, int> > (0, pair<int, int>(srcR, srcC)));
    grid[srcR][srcC] = VISITED;

    while(!vQueue.empty())
    {
        int length = vQueue.front().first;
        int curR = vQueue.front().second.first;
        int curC = vQueue.front().second.second;
        vQueue.pop();

        if(curR == destR && curC == destC)
            return length;

        for(int direction = 0; direction < NUM_DIRECTION; direction++)
        {
            int nextR = curR + COORD_OFFSET[direction][0];
            int nextC = curC + COORD_OFFSET[direction][1];

            if(isValidCell(nextR, nextC, numRow, numCol) && grid[nextR][nextC] == SAFE)
            {
                grid[nextR][nextC] = VISITED;
                vQueue.push(pair<int, pair<int, int> > (length + 1, pair<int, int> (nextR, nextC)));
            }
        }
    }

    return -1;
}

bool isValidCell(int row, int col, int numRow, int numCol)
{
    if(row < 0 || col < 0 || row >= numRow || col >= numCol)
        return false;
    return true;
}
/* Mark those cells whose Euclidean distance with (centerR, centerC) is less than
 * or equal to 'distance'
 */
void markDangerous(int grid[][MAX_SIZE], int numRow, int numCol, int centerR, int centerC,
                   int distance)
{
    int rowFrom = centerR - distance;
    if(rowFrom < 0)
        rowFrom = 0;
    int rowTo = centerR + distance;
    if(rowTo >= numRow)
        rowTo = numRow - 1;
    int colFrom = centerC - distance;
    if(colFrom < 0)
        colFrom = 0;
    int colTo = centerC + distance;
    if(colTo >= numCol)
        colTo = numCol - 1;

    int squareDist = distance * distance;
    for(int row = rowFrom; row <= rowTo; row++)
        for(int col = colFrom; col <= colTo; col++)
            if(computeSquareEuclidDist(row, col, centerR, centerC) <= squareDist)
            {
                grid[row][col] = BLOCKED_OR_DANGEROUS;
            }
}

int computeSquareEuclidDist(int rowOne, int colOne, int rowTwo, int colTwo)
{
    int diffRow = rowOne - rowTwo, diffCol = colOne - colTwo;

    return diffRow * diffRow + diffCol * diffCol;
}
