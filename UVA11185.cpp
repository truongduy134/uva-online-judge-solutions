#include <cstdio>
#include <algorithm>

using namespace std;

#define MAX_LEN 4000

void getTernaryStr(int N, char ternary[])
{
    if(N == 0)
    {
        ternary[0] = '0';
        ternary[1] = '\0';
        return;
    }

    int r, len = 0;
    while(N)
    {
        r = N % 3;
        ternary[len++] = r + '0';
        N /= 3;
    }
    reverse(ternary, ternary + len);
    ternary[len] = '\0';
}

int main(void)
{
    int N;
    char ternary[MAX_LEN];

  //  freopen("in.txt", "r", stdin);
    while(1)
    {
        scanf("%d", &N);
        if(N < 0)
            break;

        getTernaryStr(N, ternary);
        printf("%s\n", ternary);
    }

    return 0;
}
