#include <cstdio>

using namespace std;

#define MAX_SIZE 100
int main(void)
{
    int N, h[MAX_SIZE], T, caseId = 1, highJump, lowJump;

   // freopen("in.txt", "r", stdin);
    scanf("%d", &T);

    while(caseId <= T)
    {
        scanf("%d", &N);

        for(int i = 0; i < N; i++)
            scanf("%d", &h[i]);

        highJump = lowJump = 0;
        for(int i = 1; i < N; i++)
            if(h[i] > h[i - 1])
                highJump++;
            else
                if(h[i] < h[i - 1])
                    lowJump++;

        printf("Case %d: %d %d\n", caseId, highJump, lowJump);
        caseId++;
    }
    return 0;
}
