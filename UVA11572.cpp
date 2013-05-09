#include <cstdio>
#include <map>
#include <vector>
using namespace std;

int main(void)
{
 //   freopen("in.txt", "r", stdin);
 //   freopen("out.txt", "w", stdout);

    int numCase, numSnow;
    scanf("%d", &numCase);
    while(numCase)
    {
        map<int, int> snowTree;


        scanf("%d", &numSnow);
        vector<int> snowVector(numSnow);
        for(int i = 0; i < numSnow; i++)
            scanf("%d", &snowVector[i]);

        int maxLen = 0, low = 0, high, curLen = 0;

        for(high = 0; high < numSnow; high++)
        {
            map<int, int>::iterator it = snowTree.find(snowVector[high]);
            if(it != snowTree.end())
            {
                if(curLen > maxLen)
                    maxLen = curLen;

                int oldPos = it->second;

                for(int j = low; j <= oldPos; j++)
                {
                    snowTree.erase(snowVector[j]);
                    curLen--;
                }
                low = oldPos + 1;
            }

            curLen++;
            snowTree[snowVector[high]] = high;
        }

        if(curLen > maxLen)
            maxLen = curLen;
        printf("%d\n", maxLen);
        numCase--;
    }
    return 0;
}
