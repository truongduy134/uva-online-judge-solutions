/*******************************************************
 * Author: Nguyen Truong Duy
 *******************************************************/

/* Methodology:
 *  + Define f(r, c) = the minimum number of steps to reach a cell of color 3 from the current cell (r, c)
 *  + We are asked to compute the minimum number of steps to reach a cell of color 3 from a cell of color 1
 *      independent of the choice of the inital cell of color 1.
 *    That means we are to compute:
 *          max f(r, c) where the color of cell (r, c) is 1.
 *
 *  + High level procedure:
 *         - Step 1: Compute the value f(r, c) for all cells in the grid.
 *         - Step 2: Find the maximum f(r, c) among the cells (r, c) of color 1.
 *  + To do step 1 efficiently, we model this problem as a graph problem. Construct the graph G = (V, E)
 *      as follows
 *         - V consists of a special vertex S and all the cells in the grid.
 *         - S is connected to all cells of color 3 in the grid.
 *         - Two cells in the grid are connected in G if one is to the north / south / east / west of
 *              the other.
 *         - G is unweighted
 *    It is easy to see that
 *      f(r, c) = the length of the shortest path from S to (r, c) - 1.
 *    So computing all values f(r, c) is equivalent to finding shorest paths from the single source S.
 *  + Since G is unweighed, we can use Breath First Search to finding shortest paths.
 *
 *  + Time complexity: O(N^2) where N is the size of the grid.
 */

#include <queue>
#include <cstdio>
#include <utility>

using namespace std;

const char DEST_COLOR = '3';
const char START_COLOR = '1';
const int MAX_SIZE = 600;
#define NUM_DIRECTION 4
const int COORD_OFFSET[NUM_DIRECTION][2] = { {0, 1}, {1, 0}, {0, -1}, {-1, 0} };
const short UNVISITED = -1;

short getMaxMinDistFromStartToDestColor(char colorGrid[][MAX_SIZE + 1], int mSize);
bool isValidCell(int r, int c, int numR, int numC);

int main(void)
{
    char colorGrid[MAX_SIZE][MAX_SIZE + 1];
    int mSize;

    while(scanf("%d", &mSize) > 0)
    {
        for(int r = 0; r < mSize; r++)
            scanf("%s", colorGrid[r]);

        printf("%d\n", getMaxMinDistFromStartToDestColor(colorGrid, mSize));
    }
    return 0;
}

short getMaxMinDistFromStartToDestColor(char colorGrid[][MAX_SIZE + 1], int mSize)
{
    short distFromDest[mSize][mSize];

    for(int r = 0; r < mSize; r++)
        for(int c = 0; c < mSize; c++)
            distFromDest[r][c] = UNVISITED;

    queue<pair<int, int> > vQueue;
    // Add those cells with DEST_COLOR to the queue. We go backwards from destination to source
    for(int r = 0; r < mSize; r++)
        for(int c = 0; c < mSize; c++)
            if(colorGrid[r][c] == DEST_COLOR)
            {
                vQueue.push(pair<int, int> (r, c));
                distFromDest[r][c] = 0;
            }

    while(!vQueue.empty())
    {
        int curR = vQueue.front().first;
        int curC = vQueue.front().second;
        vQueue.pop();

        for(int direction = 0; direction < NUM_DIRECTION; direction++)
        {
            int nextR = curR + COORD_OFFSET[direction][0];
            int nextC = curC + COORD_OFFSET[direction][1];

            if(isValidCell(nextR, nextC, mSize, mSize) && distFromDest[nextR][nextC] == UNVISITED)
            {
                distFromDest[nextR][nextC] = distFromDest[curR][curC] + 1;
                vQueue.push(pair<int, int> (nextR, nextC));
            }
        }
    }

    short maxMinDist = 0;
    for(int r = 0; r < mSize; r++)
        for(int c = 0; c < mSize; c++)
            if(colorGrid[r][c] == START_COLOR && maxMinDist < distFromDest[r][c])
                maxMinDist = distFromDest[r][c];

    return maxMinDist;
}

bool isValidCell(int r, int c, int numR, int numC)
{
    if(r < 0 || c < 0 || r >= numR || c >= numC)
        return false;
    return true;
}
