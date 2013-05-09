#include <cstdio>
#include <algorithm>
#include <vector>
using namespace std;

#define MAX_ROW 6
#define MAX_COL 5

void sortColumn(char grid[][MAX_COL + 1])
{
    char arr[MAX_ROW];

    for(int c = 0; c < MAX_COL; c++)
    {
        for(int r = 0; r < MAX_ROW; r++)
            arr[r] = grid[r][c];

        sort(arr, arr + MAX_ROW);

        for(int r = 0; r < MAX_ROW; r++)
            grid[r][c] = arr[r];
    }
}

void findColIntersect(char gridOne[][MAX_COL + 1], char gridTwo[][MAX_COL + 1], vector<vector<char> > &colIntersect)
{
    int r1, r2;
    for(int c = 0; c < MAX_COL; c++)
    {
        r1 = 0;
        r2 = 0;
        while(r1 < MAX_ROW && r2 < MAX_ROW)
        {
            if(gridOne[r1][c] == gridTwo[r2][c])
            {
                colIntersect[c].push_back(gridOne[r1][c]);
                do
                {
                    r1++;
                } while(r1 < MAX_ROW && gridOne[r1][c] == gridOne[r1 - 1][c]);
                do
                {
                    r2++;
                } while(r2 < MAX_ROW && gridTwo[r2][c] == gridTwo[r2 - 1][c]);
            }
            else
            {
                if(gridOne[r1][c] > gridTwo[r2][c])
                    r2++;
                else
                    r1++;
            }
        }
    }
}

bool findTargetStr(vector<vector<char> > & colIntersect, int K, char targetStr[])
{
    int count = 0, totalCommon = 1;

    for(unsigned i = 0; i < colIntersect.size(); i++)
        totalCommon *= (int) colIntersect[i].size();
    if(K > totalCommon)
        return false;

    for(unsigned int r0 = 0; r0 < colIntersect[0].size(); r0++)
        for(unsigned int r1 = 0; r1 < colIntersect[1].size(); r1++)
            for(unsigned int r2 = 0; r2 < colIntersect[2].size(); r2++)
                for(unsigned int r3 = 0; r3 < colIntersect[3].size(); r3++)
                    for(unsigned int r4 = 0; r4 < colIntersect[4].size(); r4++)
                    {
                        count++;
                        if(count == K)
                        {
                            targetStr[0] = colIntersect[0][r0];
                            targetStr[1] = colIntersect[1][r1];
                            targetStr[2] = colIntersect[2][r2];
                            targetStr[3] = colIntersect[3][r3];
                            targetStr[4] = colIntersect[4][r4];
                            targetStr[5] = '\0';
                            return true;
                        }
                    }

    return false;
}

int main(void)
{
    int T, K;
    char trash[10], gridOne[MAX_ROW][MAX_COL + 1], gridTwo[MAX_ROW][MAX_COL + 1];
    char target[MAX_COL + 1];
    vector<vector<char> > colIntersect;
    bool existFlg;

   // freopen("in.txt", "r", stdin);
   // freopen("out.txt", "w", stdout);

    for(int i = 0; i < MAX_COL; i++)
    {
        vector<char> col;
        colIntersect.push_back(col);
    }

    scanf("%d", &T);
    while(T)
    {
        scanf("%d", &K);
        gets(trash);

        for(int i = 0; i < MAX_ROW; i++)
            gets(gridOne[i]);
        for(int i = 0; i < MAX_ROW; i++)
            gets(gridTwo[i]);

        sortColumn(gridOne);
        sortColumn(gridTwo);

        for(int i = 0; i < MAX_COL; i++)
            colIntersect[i].clear();

        findColIntersect(gridOne, gridTwo, colIntersect);

        existFlg = findTargetStr(colIntersect, K, target);

        if(existFlg)
            printf("%s\n", target);
        else
            printf("NO\n");
        T--;
    }
}
