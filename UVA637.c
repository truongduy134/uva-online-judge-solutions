#include <stdio.h>

#define MAX_PAGE 101

void initTableOrder(int arr[][2], int size, int val);
void determineOrder(int printOrder[][2], int numSheet, int numPage);
void printResult(int printOrder[][2], int numSheet, int numPage);

int main()
{
    int numPage, numSheet, printOrder[2 * MAX_PAGE][2];

    while(1)
    {
        scanf("%d", &numPage);

        if(numPage == 0)
            break;

        numSheet = numPage / 4;
        if(numPage % 4)
            numSheet++;

        initTableOrder(printOrder, numSheet << 1, -1);
        determineOrder(printOrder, numSheet, numPage);
        printResult(printOrder, numSheet, numPage);
    }

    return 0;
}

void initTableOrder(int arr[][2], int size, int val)
{
    int index;

    for(index = 0; index < size; index++)
        arr[index][0] = arr[index][1] = val;
}

void determineOrder(int printOrder[][2], int numSheet, int numPage)
{
    int page = 1, line = 0, goDown = 1, totalLine = numSheet << 1;

    while(page <= numPage)
    {
        if(line & 1)
        {
            /* Line is odd. This is the back face */
            if(goDown)
                printOrder[line][0] = page;
            else
                printOrder[line][1] = page;
        }
        else
        {
            /* Front face */
            if(goDown)
                printOrder[line][1] = page;
            else
                printOrder[line][0] = page;
        }

        page++;
        if(goDown)
        {
            line++;
            if(line >= totalLine)
            {
                line = totalLine - 1;
                goDown = 0;
            }
        }
        else
            line--;
    }
}

void printResult(int printOrder[][2], int numSheet, int numPage)
{
    int line, numLine = numSheet << 1, sheet = 1, col;

    printf("Printing order for %d pages:\n", numPage);
    for(line = 0; line < numLine; line++)
    {
        if(printOrder[line][0] < 0 && printOrder[line][1] < 0)
            continue;

        if(line & 1)
        {
            /* Back face */
            printf("Sheet %d, back : ", sheet);
            sheet++;
        }
        else
            /* Front face */
            printf("Sheet %d, front: ", sheet);

        for(col = 0; col <= 1; col++)
        {
            if(printOrder[line][col] < 0)
                printf("Blank");
            else
                printf("%d", printOrder[line][col]);

            if(col)
                printf("\n");
            else
                printf(", ");
        }
    }
}
