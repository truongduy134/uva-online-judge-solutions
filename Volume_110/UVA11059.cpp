#include <cstdio>
#include <vector>
#include <iostream>
using namespace std;

int main(void)
{
  //  freopen("in.txt", "r", stdin);
  //  freopen("out.txt", "w", stdout);
    int n, caseId;

    caseId = 1;
    while(scanf("%d", &n) > 0)
    {
        vector<int> arr(n);

        for(int i = 0; i < n; i++)
            scanf("%d", &arr[i]);

        long long maxProduct = 0, product;

        for(int len = 1; len <= n; len++)
        {
            int mEnd = len;
            product = 1;
            for(int i = 0; i < mEnd; i++)
                product *= (long long) arr[i];
            if(product > maxProduct)
                maxProduct = product;
            int start = 0;
            while(mEnd < n)
            {
                if(arr[start])
                    product /= arr[start];
                else
                {
                    product = 1;
                    for(int k = start + 1; k < mEnd; k++)
                        product *= arr[k];
                }
                product *= arr[mEnd];
                if(product > maxProduct)
                    maxProduct = product;
                start++;
                mEnd++;
            }
        }
        cout << "Case #" << caseId << ": The maximum product is " << maxProduct << "." << endl << endl;
        caseId++;
    }

    return 0;
}
