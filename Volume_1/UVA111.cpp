#include <cstdio>
#include <vector>
#include <cstring>

using namespace std;

// Find the largest arr[i] such that arr[i] <= key < arr[i + 1]
// Assumption:
//      arr[-1] = -INFINITY
//      arr[n] = INFINITY
int supremumBinarySearch(vector<int> & arr, int key)
{
    int mSize = (int) arr.size();
    if(mSize == 0 || key < arr[0])
        return -1;
    if(key >= arr[mSize - 1])
        return mSize - 1;

    int left = 0, right = mSize - 1, middle;
    while(left <= right)
    {
        middle = (left + right) >> 1;
        if(arr[middle] <= key && key < arr[middle + 1])
            return middle;
        else
        {
            if(arr[middle + 1] <= key)
                left = middle + 1;
            else
                right = middle - 1;
        }
    }

    return -1;      // Dummy
}

int LIS(vector<int> & arr)
{
    vector<int> minTailSeq;

    for(int i = 0; i < (int) arr.size(); i++)
    {
        int k = supremumBinarySearch(minTailSeq, arr[i]);
        if(k == (int) minTailSeq.size() - 1)
            minTailSeq.push_back(arr[i]);

        if(arr[i] < minTailSeq[k + 1])
            minTailSeq[k + 1] = arr[i];
    }

    return (int) minTailSeq.size();
}

int main(void)
{
    int numEvent, eventRank;

 //   freopen("in.txt", "r", stdin);
 //   freopen("out.txt", "w", stdout);

    scanf("%d", &numEvent);

    vector<int> mapOrderToIncreasing(numEvent);
    vector<int> eventOrder(numEvent);
    vector<int> eventCorrectOrder(numEvent);

    for(int i = 0; i < numEvent; i++)
    {
        scanf("%d", &eventRank);
        mapOrderToIncreasing[i] = eventRank - 1;
    }

    while(scanf("%d", &eventRank) > 0)
    {
        eventOrder[eventRank - 1] = mapOrderToIncreasing[0];
        for(int i = 1; i < numEvent; i++)
        {
            scanf("%d", &eventRank);
            eventOrder[eventRank - 1] = mapOrderToIncreasing[i];

        }

        printf("%d\n", LIS(eventOrder));
    }

    return 0;
}
