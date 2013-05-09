#include <cstdio>
#include <algorithm>
#include <vector>

using namespace std;

int myabs(int x)
{
    return x >= 0 ? x : -x;
}
int main(void)
{
     //   freopen("in.txt", "r", stdin);
     //   freopen("out.txt", "w", stdout);

        int n, m, q, closet, caseId, l, h, s;

        caseId = 1;
        while(1)
        {
            scanf("%d", &n);
            if(n == 0)
                break;

            vector<int> arr(n);

            for(int i = 0; i < n; i++)
                scanf("%d", &arr[i]);

            sort(arr.begin(), arr.end());

            scanf("%d", &m);

            printf("Case %d:\n", caseId);

            for(int i = 0; i < m; i++)
            {
                scanf("%d", &q);

                l = 0;
                h = n - 1;
                closet = arr[l] + arr[h];

                while(l < h)
                {
                    s = arr[l] + arr[h];
                    if((myabs(s - q)) < (myabs(closet - q)))
                        closet = s;

                    if(s > q)
                        h--;
                    else
                        if(s < q)
                            l++;
                        else
                            break;
                }

                printf("Closest sum to %d is %d.\n", q, closet);
            }

            caseId++;
        }

    return 0;
}
