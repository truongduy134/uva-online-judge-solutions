#include <cstdio>
#include <vector>
using namespace std;

int main(void)
{
   // freopen("in.txt", "r", stdin);
   // freopen("out.txt", "w", stdout);

    int N, B, diff;

    while(1)
    {
        scanf("%d %d", &N, &B);
        if(N == 0 && B == 0)
            break;

        vector<int> ballArr(B);
        vector<bool> isPresent(N + 1, false);

        for(int index = 0; index < B; index++)
        {
            scanf("%d", &ballArr[index]);
        }

        for(int i = 0; i < B; i++)
            for(int j = i; j < B; j++)
            {
                diff = ballArr[j] - ballArr[i];
                if(diff < 0)
                    diff = -diff;
                isPresent[diff] = true;
            }

        bool allPresent = true;
        for(int index = 0; index <= N; index++)
            if(!isPresent[index])
            {
                allPresent = false;
                break;
            }

        if(allPresent)
            printf("Y\n");
        else
            printf("N\n");
    }

    return 0;
}
