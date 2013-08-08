#include <cstdio>

using namespace std;

#define MAX_NUM 200000

int main()
{
  //  freopen("in.txt", "r", stdin);
  //  freopen("out.txt", "w", stdout);

    int N, S, arr[MAX_NUM];

    while(scanf("%d %d", &N, &S) > 0)
    {
        for(int i = 0; i < N; i++)
            scanf("%d", &arr[i]);

        int l = 0, u = 0, sum = 0, minLen = N + 1, len = 0;

        for(u = 0; u < N; u++)
        {
            sum += arr[u];
            len++;

            while(sum >= S)
            {
                if(len < minLen)
                    minLen = len;
                sum -= arr[l];
                l++;
                len--;
            }
        }

        if(minLen == N + 1)
            minLen = 0;
        printf("%d\n", minLen);
    }
    return 0;
}
