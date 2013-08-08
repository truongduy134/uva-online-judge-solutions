#include <cstdio>
#include <cctype>
#include <cstdlib>
#include <map>
#include <cstring>
#include <vector>
#include <utility>

using namespace std;

#define MINUS_INFINITY -1000000000
#define MAX_LEN 7
#define MAX_LEN_FORMULA 5001
#define NUM_ALPHA 26

void getRowAndCol(char stringPosition[], int *row, int *col)
{
    int i = 0;

    *col = 0;
    while(isalpha(stringPosition[i]))
    {
        *col = (*col) * NUM_ALPHA + (stringPosition[i] - 'A' + 1);
        i++;
    }

    *row = atoi(&stringPosition[i]);
}

int computeCellValue(int spreadSheet[], int numCol, map< pair<int, int>, vector< pair <int, int> > > & mapCellToFormula, int row, int col)
{
    if(spreadSheet[row * numCol + col] != MINUS_INFINITY)
        return spreadSheet[row * numCol + col];

    int val = 0;
    vector< pair<int, int > > cellsInFormula = mapCellToFormula[make_pair(row, col)];
    for(int i = 0; i < (int) cellsInFormula.size(); i++)
    {
        pair<int, int> curCell = cellsInFormula[i];
        val += computeCellValue(spreadSheet, numCol, mapCellToFormula, curCell.first, curCell.second);
    }

    spreadSheet[row * numCol + col] = val;

    return val;
}

int main(void)
{
    int T, numRow, numCol, row, col;
    char cellElement[MAX_LEN_FORMULA], *token, delim[] = " +";
    map< pair<int, int>, vector< pair<int, int> > > mapCellToFormula;

   // freopen("in.txt", "r", stdin);
   // freopen("out.txt", "w", stdout);

    scanf("%d", &T);

    while(T)
    {
        scanf("%d %d", &numCol, &numRow);

        int spreadSheet[numRow][numCol];

        for(int i = 0; i < numRow; i++)
            for(int j = 0; j < numCol; j++)
                spreadSheet[i][j] = MINUS_INFINITY;

        mapCellToFormula.clear();

        for(int i = 0; i < numRow; i++)
            for(int j = 0; j < numCol; j++)
            {
                scanf("%s", cellElement);
                if(cellElement[0] != '=')
                    spreadSheet[i][j] = atoi(cellElement);
                else
                {
                    token = strtok(cellElement + 1, delim);
                    vector< pair<int, int> > cellsInFormula;
                    do
                    {
                        getRowAndCol(token, &row, &col);
                        pair<int, int> cellCoord = make_pair(row - 1, col - 1);
                        cellsInFormula.push_back(cellCoord);
                        token = strtok(NULL, delim);
                    } while(token != NULL);
                    mapCellToFormula[make_pair(i, j)] = cellsInFormula;
                }
            }

        for(int i = 0; i < numRow; i++)
            for(int j = 0; j < numCol; j++)
                if(spreadSheet[i][j] == MINUS_INFINITY)
                    spreadSheet[i][j] = computeCellValue((int *) spreadSheet, numCol, mapCellToFormula, i, j);

        for(int i = 0; i < numRow; i++)
        {
            printf("%d", spreadSheet[i][0]);
            for(int j = 1; j < numCol; j++)
                printf(" %d", spreadSheet[i][j]);
            printf("\n");
        }
        T--;
    }
    return 0;
}
