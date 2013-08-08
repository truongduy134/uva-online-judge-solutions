#include <cstdio>
#include <set>

using namespace std;

long long computePolyMod(int c[], long long k, long long x, long long mod)
{
    long long val = 0, powerX = 1;

    for(int i = 0; i <= k; i++)
    {
        val = (val + ((long long) c[i]) * powerX) % mod;
        powerX = (powerX * x) % mod;
    }

    return val;
}

int main(void)
{
    int N, M, k, c[12];
    long long val;
    set<long long> mSet;

  //  freopen("in.txt", "r", stdin);
  //  freopen("out.txt", "w", stdout);

    while(1)
    {
        scanf("%d %d", &N, &M);
        if(N == 0 && M == 0)
            break;

        scanf("%d", &k);

        for(int i = 0; i <= k; i++)
            scanf("%d", &c[i]);

        mSet.clear();

        for(int i = 0; i <= M; i++)
        {
            val = computePolyMod(c, k, i, N + 1);
     //       printf("Val = %d\n", val);
            mSet.insert(val);
        }

        printf("%d\n", mSet.size());
    }
}
