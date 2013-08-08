#include <cstdio>
#include <vector>
#include <utility>
#include <algorithm>

using namespace std;

int main(void)
{
    int k, x, y, numer, denom;
    vector<pair<int, int> > resultVect;

    while(scanf("%d", &k) > 0)
    {
        resultVect.clear();

        for(y = k + 1; y <= (k << 1); y++)
        {
            numer = k * y;
            denom = y - k;
            if(numer % denom == 0)
            {
                x = numer / denom;
                if(x >= y)
                    resultVect.push_back(make_pair(-x, y));
            }
        }

        sort(resultVect.begin(), resultVect.end());

        printf("%d\n", (int) resultVect.size());
        for(int i = 0; i < (int) resultVect.size(); i++)
            printf("1/%d = 1/%d + 1/%d\n", k, -resultVect[i].first, resultVect[i].second);
    }
    return 0;
}
