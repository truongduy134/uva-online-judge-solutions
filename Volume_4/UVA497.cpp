/*******************************************************
 * Author: Nguyen Truong Duy
 *******************************************************/

/* Methodology:
 *  + This is the longest increasing subsequence problem.
 *  + Use the well-known greedy O(n log n) solution
 *
 * Note on the usage of variables in the algorithm:
 *  + minEndInd[i] stores the index of the smallest tail among
 *          all strictly increasing subsequence of length i.
 *  + predecessor[i] stores the index of the element standing right in front of
 *          arr[i] in the longest increasing subsequence ending at arr[i].
 */

#include <cstdio>
#include <vector>
#include <cstdlib>
#include <algorithm>

using namespace std;

const int MAX_LEN_LINE = 10;

int findSupremumInd(const vector<int> & valArr, const vector<int> indArr, int key);
void computeLIS(const vector<int> & arr, vector<int> & liSub);

int main(void)
{
    int T;
    char line[MAX_LEN_LINE + 1];
    vector<int> arr, liSub;

    scanf("%d", &T);
    gets(line);
    gets(line);

    while(T)
    {
        arr.clear();
        while(gets(line) != NULL)
        {
            if(line[0] == '\0')
                break;
            arr.push_back(atoi(line));
        }

        computeLIS(arr, liSub);

        printf("Max hits: %d\n", (int) liSub.size());
        for(int i = 0; i < (int) liSub.size(); i++)
            printf("%d\n", liSub[i]);

        if(T > 1)
            printf("\n");
        T--;
    }
    return 0;
}

void computeLIS(const vector<int> & arr, vector<int> & liSub)
{
    int mSize = (int) arr.size();
    vector<int> minEndInd;

    vector<int> predecessor(mSize, 0);
    for(int i = 0; i < mSize; i++)
        predecessor[i] = i;

    for(int i = 0; i < mSize; i++)
    {
        int supremumInd = findSupremumInd(arr, minEndInd, arr[i]);

         if(supremumInd > 0)
                predecessor[i] = minEndInd[supremumInd - 1];

        if(supremumInd == (int) minEndInd.size())
            minEndInd.push_back(i);
        else
            minEndInd[supremumInd] = i;
    }

    // Construct the LIS
    int resultInd = minEndInd[minEndInd.size() - 1];
    liSub.clear();
    while(1)
    {
        liSub.push_back(arr[resultInd]);

        int pInd = predecessor[resultInd];
        if(pInd == resultInd)
            break;
        resultInd = pInd;
    }
    reverse(liSub.begin(), liSub.end());
}

// Return an index k such that
//                  valArr[indArr[k]] >= key > valArr[indArr[k - 1]]
// Let n be the size of indArr.
// Then by convention, valArr[indArr[n]] = INFINITY, valArr[indArr[-1]] = -INFINITY
int findSupremumInd(const vector<int> & valArr, const vector<int> indArr, int key)
{
    int mSize = (int) indArr.size();

    // Corner cases
    if(mSize == 0)
        return mSize;
    if(valArr[indArr[0]] >= key)
        return 0;
    if(valArr[indArr[mSize - 1]] < key)
        return mSize;

    int left = 1, right = mSize - 1;
    while(left <= right)
    {
        int mid = left + ((right - left) >> 1);

        if(valArr[indArr[mid]] >= key && valArr[indArr[mid - 1]] < key)
            return mid;

        if(valArr[indArr[mid]] < key)
            left = mid + 1;
        else
            right = mid - 1;
    }

    return -1;      // Dummy
}
