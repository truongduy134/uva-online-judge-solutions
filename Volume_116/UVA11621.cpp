#include <cstdio>
#include <queue>
#include <vector>
#include <algorithm>

using namespace std;

const long long UPPER_BOUND = ((long long) 1) << 32;
const int NUM_PRIME_FACTOR = 2;
const int LIST_PRIME_FACTOR[NUM_PRIME_FACTOR] = {2, 3};

void generateFactorOfTwoAndThree(vector<long long> & listFactorOfTwoAndThree, long long upperBound);

int main(void)
{
        vector<long long> listFactorOfTwoAndThree;
        vector<long long>::iterator it;
        long long num;

        // listFactorOfTwoAndThree is sorted
        generateFactorOfTwoAndThree(listFactorOfTwoAndThree, UPPER_BOUND);

        while(1)
        {
            scanf("%lld", &num);
            if(num == 0)
                break;

            it = lower_bound(listFactorOfTwoAndThree.begin(), listFactorOfTwoAndThree.end(), num);
            printf("%lld\n", *it);
        }

        return 0;
}

void generateFactorOfTwoAndThree(vector<long long> & listFactorOfTwoAndThree, long long upperBound)
{
    listFactorOfTwoAndThree.clear();

    priority_queue<long long, vector<long long>, greater<long long> > numQueue;

    numQueue.push(1);

    long long num;
    int mSize;
    while(!numQueue.empty())
    {
        num = numQueue.top();
        numQueue.pop();

        if(num > upperBound)
            break;

        mSize = (int) listFactorOfTwoAndThree.size();

        if(mSize == 0 || num != listFactorOfTwoAndThree[mSize - 1])
        {
            listFactorOfTwoAndThree.push_back(num);

            for(int factorId = 0; factorId < NUM_PRIME_FACTOR; factorId++)
                numQueue.push(num * LIST_PRIME_FACTOR[factorId]);
        }
    }
}
