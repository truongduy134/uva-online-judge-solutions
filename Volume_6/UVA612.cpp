#include <algorithm>
#include <cstdio>
#include <utility>
#include <string>
#include <vector>

using namespace std;

#define MAX_LEN 60

bool compare(const pair<int, string> & one, const pair<int, string> & two)
{
    return one.first < two.first;
}

int countNumInversion(char str[], int len)
{
    int numInverse = 0;
    for(int i = 0; i < len; i++)
        for(int j = i + 1; j < len; j++)
            if(str[i] > str[j])
                numInverse++;

    return numInverse;
}

int main(void)
{
    int numStr, len, T, numInverse;
    char DNA[MAX_LEN + 1];
    vector<pair<int, string> > arr;

  //  freopen("in.txt", "r", stdin);
  //  freopen("out.txt", "w", stdout);

    scanf("%d", &T);
    while(T)
    {
        arr.clear();

        scanf("%d %d", &len, &numStr);

        for(int i = 0; i < numStr; i++)
        {
            scanf("%s", DNA);
            numInverse = countNumInversion(DNA, len);
            arr.push_back(make_pair(numInverse, DNA));
        }

        stable_sort(arr.begin(), arr.end(), compare);

        for(int i = 0; i < numStr; i++)
            printf("%s\n", arr[i].second.c_str());

        if(T != 1)
            printf("\n");
        T--;
    }
}
