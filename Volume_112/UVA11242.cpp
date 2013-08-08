#include <cstdio>
#include <vector>
#include <algorithm>
using namespace std;

int main(void)
{
    int f, r;

 //   freopen("in.txt", "r", stdin);
 //   freopen("out.txt", "w", stdout);
    while(1)
    {
        scanf("%d", &f);
        if(f == 0)
            break;

        scanf("%d", &r);
        int fArr[f], rArr[r];

        for(int i = 0; i < f; i++)
            scanf("%d", &fArr[i]);
        for(int i = 0; i < r; i++)
            scanf("%d", &rArr[i]);

        vector<double> arr(f * r);
        int id = 0;
        for(int i = 0; i < r; i++)
            for(int j = 0; j < f; j++)
            {
                arr[id] = rArr[i] / ((double) fArr[j]);
                id++;
            }

        sort(arr.begin(), arr.end());

        double mMax = 0;
        for(unsigned int id = 1; id < arr.size(); id++)
            if(arr[id] != arr[id - 1])
            {
                double mRatio = arr[id] / arr[id - 1];
                if(mRatio > mMax)
                    mMax = mRatio;
            }

        printf("%.2f\n", mMax);
    }
    return 0;
}
