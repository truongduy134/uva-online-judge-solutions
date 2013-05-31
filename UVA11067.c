/*******************************************************
 * Author: Nguyen Truong Duy
 *******************************************************/

/* Methodology:
 *  + Use dynamic programming.
 *
 *  + Let W[i][j] = 1 if the wolf may be at the intersection at row i, column j.
 *    Otherwise, W[i][j] = 0
 *
 *  + Let the grid be of size h x w.
 *    Then there are h + 1 horizontal lines and w + 1 vertical lines
 *
 *  + Define f(i, j) = the number of shortest paths (i.e. north-east paths) from (i, j) to (h, w)
 *         without meeting the wolf.
 *
 *  + Then f(i, j) = 0 if W[i][j] = 1 or (i, j) is not valid
 *    Otherwise, f(i, j) = f(i + 1, j) + f(i, j + 1) (since we only consider
 *          north-east paths)
 *    Note that f(h, w) = 1 (since (h, w) is the destination)
 *
 *  + Time complexity: O(h * w)
 */

#include <stdio.h>
#include <string.h>

const int MAX_SIZE = 101;

long long int countNumPath(int row, int col, int numRow, int numCol, long long int numPath[][MAX_SIZE], int wolfPos[][MAX_SIZE]);

int main(void)
{
    long long int numPath[MAX_SIZE][MAX_SIZE];
    int wolfPos[MAX_SIZE][MAX_SIZE], numR, numC, col, row, numPos, path, i;

    while(1)
    {
        scanf("%d %d", &numC, &numR);
        if(numR == 0 && numC == 0)
            break;

        numC++;
        numR++;
        memset(numPath, -1, MAX_SIZE * MAX_SIZE * sizeof(long long int));
        memset(wolfPos, 0, MAX_SIZE * MAX_SIZE * sizeof(int));

        scanf("%d", &numPos);
        for(i = 0; i < numPos; i++)
        {
            scanf("%d %d", &col, &row);
            wolfPos[row][col] = 1;
        }

        path = countNumPath(0, 0, numR, numC, numPath, wolfPos);

        if(path == 0)
            printf("There is no path.\n");
        else
        {
            if(path == 1)
                printf("There is one path from Little Red Riding Hood's house to her grandmother's house.\n");
            else
                printf("There are %lld paths from Little Red Riding Hood's house to her grandmother's house.\n", path);
        }
    }
    return 0;
}

long long int countNumPath(int row, int col, int numRow, int numCol, long long int numPath[][MAX_SIZE], int wolfPos[][MAX_SIZE])
{
    if(row < 0 || col < 0 || row >= numRow || col >= numCol)
        return 0;
    if(row == numRow - 1 && col == numCol - 1)
        return 1;
    if(wolfPos[row][col] == 1)
        return 0;

    if(numPath[row][col] >= 0)
        return numPath[row][col];

    numPath[row][col] = countNumPath(row + 1, col, numRow, numCol, numPath, wolfPos) +
                        countNumPath(row, col + 1, numRow, numCol, numPath, wolfPos);

    return numPath[row][col];
}