/*******************************************************
 * Author: Nguyen Truong Duy
 *******************************************************/
 
/* Methodology:
 *  + Use the brute-force approach. Search in 8 directions
 *
 *  + Time complexity: O(N^3 * K) where N is the length of a word (as well as the size of the grid),
 *          and K is the number of queries.
 */
#include <stdio.h>
#include <ctype.h>
#include <string.h>

const int MAX_SIZE = 50;
#define NUM_DIRECTION 8
const int COORD_OFFSET[NUM_DIRECTION][2] = { {0, 1}, {1, 0}, {0, -1}, {-1, 0},
                                          {1, -1}, {-1, 1}, {-1, -1}, {1, 1} };

int existWordInGrid(char wordGrid[][MAX_SIZE + 1], int numRow, int numCol,
                    char word[], int wordLen, int startR, int startC);
void findWordInGrid(char wordGrid[][MAX_SIZE + 1], int numRow, int numCol,
                    char word[MAX_SIZE + 1], int * foundR, int * foundC);
void tolowerStr(char str[]);

int main(void)
{
    char wordGrid[MAX_SIZE][MAX_SIZE + 1], word[MAX_SIZE + 1], trash[MAX_SIZE + 1];
    int T, numRow, numCol, row, numQuery, query, foundR,  foundC;

    scanf("%d", &T);
    while(T)
    {
        scanf("%d %d", &numRow, &numCol);
        gets(trash);

        for(row = 0; row < numRow; row++)
        {
            gets(wordGrid[row]);
            tolowerStr(wordGrid[row]);
        }

        scanf("%d", &numQuery);
        for(query = 0; query < numQuery; query++)
        {
            scanf("%s", word);
            tolowerStr(word);

            findWordInGrid(wordGrid, numRow, numCol, word, &foundR, &foundC);
            printf("%d %d\n", foundR + 1, foundC + 1);
        }
        if(T > 1)
            printf("\n");
        T--;
    }

    return 0;
}

void tolowerStr(char str[])
{
    int i;

    for(i = 0; str[i] != '\0'; i++)
        str[i] = tolower(str[i]);
}

void findWordInGrid(char wordGrid[][MAX_SIZE + 1], int numRow, int numCol,
                    char word[MAX_SIZE + 1], int * foundR, int * foundC)
{
    int row, col;

    int wordLen = (int) strlen(word);

    for(row = 0; row < numRow; row++)
        for(col = 0; col < numCol; col++)
            if(existWordInGrid(wordGrid, numRow, numCol, word, wordLen, row, col))
            {
                *foundR = row;
                *foundC = col;
                return;
            }

    /* If not found */
    *foundR = -1;
    *foundC = -1;
}

int existWordInGrid(char wordGrid[][MAX_SIZE + 1], int numRow, int numCol,
                    char word[], int wordLen, int startR, int startC)
{
    int ind, direct, rowOffset, colOffset, endR, endC;

    if(wordGrid[startR][startC] != word[0])
        return 0;

    int found = 0;

    for(direct = 0; direct < NUM_DIRECTION; direct++)
    {
        found = 1;

        rowOffset = COORD_OFFSET[direct][0];
        colOffset = COORD_OFFSET[direct][1];

        endR = startR + rowOffset * (wordLen - 1);
        endC = startC + colOffset * (wordLen - 1);
        if(endR < 0 || endC < 0 || endR >= numRow || endC >= numCol)
            continue;

        for(ind = 0; ind < wordLen; ind++)
            if(word[ind] != wordGrid[startR + rowOffset * ind][startC + colOffset * ind])
            {
                found = 0;
                break;
            }
        if(found)
            return 1;
    }

    return 0;
}
