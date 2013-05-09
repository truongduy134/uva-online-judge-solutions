#include <cstdio>

using namespace std;

#define NUM_CHAR 26
#define MAX_COL 22
int main(void)
{
 //   freopen("in.txt", "r", stdin);
 //   freopen("out.txt", "w", stdout);

    int R, C, M, N, T, caseId;
    char row[MAX_COL + 1], trash[MAX_COL];
    scanf("%d", &T);
    caseId = 1;
    while(caseId <= T)
    {
        int frequency[NUM_CHAR] = {0};
        scanf("%d %d %d %d", &R, &C, &M, &N);
        gets(trash);

        for(int i = 0; i < R; i++)
        {
            gets(row);
            for(int j = 0; j < C; j++)
                frequency[row[j] - 'A']++;
        }

        int maxVal = 0;
        for(int i = 0; i < NUM_CHAR; i++)
            if(frequency[i] > maxVal)
                maxVal = frequency[i];

        int result = 0;
        for(int i = 0; i < NUM_CHAR; i++)
            if(frequency[i] == maxVal)
                result += frequency[i] * M;
            else
                result += frequency[i] * N;

        printf("Case %d: %d\n", caseId, result);
        caseId++;
    }

    return 0;
}
