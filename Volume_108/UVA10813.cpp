#include <cstdio>
#include <map>
#include <utility>

using namespace std;

const int BINGO_SHEET_SIZE = 5;
const int NUM_NUM = 75;
const int FREE_SPACE_ROW = 2;
const int FREE_SPACE_COL = 2;

int determineWhenToBingo(const map<int, pair<int, int> > & mapNumToCellBingo, int numSeq[]);

int main(void)
{
    map<int, pair<int, int> > mapNumToCellBingo;
    int numSeq[NUM_NUM], T, num;

    scanf("%d", &T);

    while(T)
    {
        mapNumToCellBingo.clear();

        for(int row = 0; row < BINGO_SHEET_SIZE; row++)
            for(int col = 0; col < BINGO_SHEET_SIZE; col++)
                if(row != FREE_SPACE_ROW || col != FREE_SPACE_COL)
                {
                    scanf("%d", &num);
                    mapNumToCellBingo[num] = pair<int, int> (row, col);
                }

        for(int i = 0; i < NUM_NUM; i++)
            scanf("%d", &numSeq[i]);

        printf("BINGO after %d numbers announced\n", determineWhenToBingo(mapNumToCellBingo, numSeq));
        T--;
    }
    return 0;
}

int determineWhenToBingo(const map<int, pair<int, int> > & mapNumToCellBingo, int numSeq[])
{
    int numHitRow[BINGO_SHEET_SIZE] = {0}, numHitCol[BINGO_SHEET_SIZE] = {0},
        numHitLeftDiag = 0, numHitRightDiag = 0;

    numHitRow[FREE_SPACE_COL]++;
    numHitCol[FREE_SPACE_ROW]++;
    numHitLeftDiag++;
    numHitRightDiag++;

    map<int, pair<int, int> >::const_iterator it;
    int row, col;

    for(int i = 0; i < NUM_NUM; i++)
    {
        it = mapNumToCellBingo.find(numSeq[i]);
        if(it != mapNumToCellBingo.end())
        {
            row = it->second.first;
            col = it->second.second;

            numHitRow[row]++;
            if(numHitRow[row] == BINGO_SHEET_SIZE)
                return i + 1;

            numHitCol[col]++;
            if(numHitCol[col] == BINGO_SHEET_SIZE)
                return i + 1;

            if(row == col)
            {
                numHitLeftDiag++;
                if(numHitLeftDiag == BINGO_SHEET_SIZE)
                    return i + 1;
            }

            if(row + col == BINGO_SHEET_SIZE - 1)
            {
                numHitRightDiag++;
                if(numHitRightDiag == BINGO_SHEET_SIZE)
                    return i + 1;
            }
        }
    }

    return -1;      // Dummy
}
