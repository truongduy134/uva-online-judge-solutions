/*******************************************************
 * Author: Nguyen Truong Duy
 *******************************************************/

/* Methodology:
 *  + This is an implicit graph problem.
 *      - Water cells in the grid are the vertices
 *      - Two water cells are connected if one is to the left /right / north / east of the other.
 *  + The problem now becomes counting the size of the connected component containing the input
 *      cell (determined by the given row and column)
 *  + So we run DFS at the given cell.
 *
 *  + Time complexity: O(m * n) where m x n is the dimemsion of the grid.
 */

#include <stdio.h>
#include <string.h>

const int MAX_NUM_ROW = 99;
const int MAX_NUM_COL = 99;
const char LAND = '1';
const char WATER = '0';
const char VISITED = '2';
#define NUM_DIRECTION 4
const int COORD_OFFSET[NUM_DIRECTION][2] = { {0, 1}, {1, 0}, {0, -1}, {-1, 0} };

int computeConnectedWaterRegionSize(char grid[][MAX_NUM_COL + 1], int numRow, int numCol, int curRow, int curCol);
int isValidCell(int row, int col, int numRow, int numCol);

int main(void)
{
    char grid[MAX_NUM_ROW + 1][MAX_NUM_COL + 1], trash[MAX_NUM_COL + 1];
    int numRow, numCol, T, startR, startC;

    scanf("%d", &T);
    while(T)
    {
        scanf("%d %d", &startR, &startC);
        gets(trash);
        startR--;
        startC--;

        numRow = 0;
        while(gets(grid[numRow]) != NULL)
        {
            if(grid[numRow][0] == '\0')
                break;
            numRow++;
        }
        numCol = (int) strlen(grid[0]);

        printf("%d\n", computeConnectedWaterRegionSize(grid, numRow, numCol, startR, startC));
        if(T > 1)
            printf("\n");
        T--;
    }
    return 0;
}

int computeConnectedWaterRegionSize(char grid[][MAX_NUM_COL + 1], int numRow, int numCol, int curRow, int curCol)
{
    int area = 1, direction, nextR, nextC;

    grid[curRow][curCol] = VISITED;
    for(direction = 0; direction < NUM_DIRECTION; direction++)
    {
        nextR = curRow + COORD_OFFSET[direction][0];
        nextC = curCol + COORD_OFFSET[direction][1];
        if(isValidCell(nextR, nextC, numRow, numCol) && grid[nextR][nextC] == WATER)
        {
            area += computeConnectedWaterRegionSize(grid, numRow, numCol, nextR, nextC);
        }
    }

    return area;
}

int isValidCell(int row, int col, int numRow, int numCol)
{
    if(row < 0 || col < 0 || row >= numRow || col >= numCol)
        return 0;
    return 1;
}
