#include <cstdio>
#include <vector>

using namespace std;

// Return the largest index k such that
//      arr[indexArr[k]] <= key < arr[indexArr[k + 1]]
// Convention: arr[-1] = INFINITY
//      and arr[n] = INFINITY (n is the size of the array)
int supremumBinarySearch(vector<int> & arr, vector<int> & indexArr, int key)
{
    if(indexArr.size() == 0 || key < arr[indexArr[0]])
        return -1;
    if(key >= arr[indexArr[indexArr.size() - 1]])
        return indexArr.size() - 1;

    int left = 0, right = (int) indexArr.size() - 1, middle;
    while(left <= right)
    {
        middle = (left + right) >> 1;

        if(arr[indexArr[middle]] <= key && key < arr[indexArr[middle + 1]])
            return middle;
        else
        {
            if(key > arr[indexArr[middle]])
                left = middle + 1;
            else
                right = middle - 1;
        }
    }

    return -1;      // Dummy
}

int main(void)
{
    int num, index, curIndex;
    vector<int> arr, smallestTailIndexArr, predecessorIndexArr;

 //   freopen("in.txt", "r", stdin);
 //   freopen("out.txt", "w", stdout);

    curIndex = 0;
    while(scanf("%d", &num) > 0)
    {
        arr.push_back(num);

        index = supremumBinarySearch(arr, smallestTailIndexArr, num);

        if(index >= 0 && arr[smallestTailIndexArr[index]] == num)
        {
            predecessorIndexArr.push_back(predecessorIndexArr[smallestTailIndexArr[index]]);
            curIndex++;
            continue;       // The sequence is strictly increasing
        }

        if(index < 0)
            predecessorIndexArr.push_back(-1);
        else
            predecessorIndexArr.push_back(smallestTailIndexArr[index]);

        if(index == (int) smallestTailIndexArr.size() - 1)
        {
            smallestTailIndexArr.push_back(curIndex);
        }
        else
            if(arr[smallestTailIndexArr[index + 1]] > num)
            {
                smallestTailIndexArr[index + 1] = curIndex;
            }

        curIndex++;
    }

    int lenLIS = (int) smallestTailIndexArr.size(), resultIndex = lenLIS - 1;
    vector<int> LIS(lenLIS);

    index = smallestTailIndexArr[lenLIS - 1];

    while(index >= 0)
    {
        LIS[resultIndex] = arr[index];
        index = predecessorIndexArr[index];
        resultIndex--;
    }
    printf("%d\n-\n", (int) smallestTailIndexArr.size());
    for(int i = 0; i < lenLIS; i++)
        printf("%d\n", LIS[i]);

    return 0;
}
