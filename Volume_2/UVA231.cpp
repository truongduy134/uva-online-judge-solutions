/*******************************************************
 * Author: Nguyen Truong Duy
 *******************************************************/

/* Methodology:
 *  + This problem asks to find the length of the longest NON-INCREASING subsequence.
 *
 *  + Solution: Use the well-known O(n log n) algorithm.
 *
 * Note on the usage of variables in the algorithm:
 *  + maxTailNISInd[i] = the index of the maximum tail among all tails of all non-increasing
 *       subsequences of length i.
 */

#include <cstdio>
#include <vector>

using namespace std;

int findInfimumIndex(const vector<int> & arrVal, const vector<int> & indArr, int key);
int computeLengthLNIS(const vector<int> & arr);

int main(void)
{
    vector<int> heightArr;
    int height, caseId;

    caseId = 1;
    while(1)
    {
        heightArr.clear();

        while(1)
        {
            scanf("%d", &height);
            if(height < 0)
                break;
            heightArr.push_back(height);
        }

        if(heightArr.size() == 0)
            break;

        if(caseId > 1)
            printf("\n");
        printf("Test #%d:\n", caseId);
        /* LNIS = Longest Non-Increasing Subsequence */
        printf("  maximum possible interceptions: %d\n", computeLengthLNIS(heightArr));

        caseId++;
    }
}

int computeLengthLNIS(const vector<int> & arr)
{
    vector<int> maxTailNISInd;
    int mSize = (int) arr.size();

    for(int ind = 0; ind < mSize; ind++)
    {
        // Actually the function returns the index of the infimum + 1.
        // Hence, the return result is also the index which we will do the insertion (or replacement)
        int infimumInd = findInfimumIndex(arr, maxTailNISInd, arr[ind]);

        if(infimumInd == (int) maxTailNISInd.size())
            maxTailNISInd.push_back(ind);
        else
            maxTailNISInd[infimumInd] = ind;
    }

    return (int) maxTailNISInd.size();
}

// Return an index k such that
//      arrVal[indArr[k - 1]] > key >= arrVal[indArr[k]]
// Let n be the size of indArr
// By our convention, arrVal[indArr[k]] = -INFINITY, arrVal[indArr[-1]] = INFINITY
int findInfimumIndex(const vector<int> & arrVal, const vector<int> & indArr, int key)
{
    int mSize = (int) indArr.size();

    if(mSize == 0)
        return mSize;
    if(arrVal[indArr[0]] < key)
        return 0;
    if(arrVal[indArr[mSize - 1]] >= key)
        return mSize;

    int left = 1, right = mSize - 1;
    while(left <= right)
    {
        int mid = left + ((right - left) >> 1);

        if(arrVal[indArr[mid - 1]] > key &&
           key >= arrVal[indArr[mid]])
            return mid;

        if(arrVal[indArr[mid]] < key)
            right = mid - 1;
        else
            left = mid + 1;
    }

    return -1;  // Dummy
}
