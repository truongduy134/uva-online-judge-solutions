#include <iostream>

using namespace std;

#define MAX_SIZE 15

int findSolution(int k);
bool checkSolution(int k, int m);

int main()
{
    int k;
    int memoTable[MAX_SIZE] = {0};

    while(1)
    {
        cin >> k;

        if(k == 0)
            break;

        if(memoTable[k] == 0)
            memoTable[k] = findSolution(k);
        cout << memoTable[k] << endl;
    }
    return 0;
}

int findSolution(int k)
{
    /* The solution must be at least k + 1 because the first k people are good */
    int m = k + 1;

    while(1)
    {
        if(checkSolution(k, m))
            return m;

        m++;
    }
}

bool checkSolution(int k, int m)
{
    int numLeft = 2 * k;

    int startId = -1;

    while(numLeft > k)
    {
        int killId = (startId + m) % numLeft;

        if(killId < k)
            return false;

        numLeft -= 1;
        startId = killId - 1;
    }

    return true;
}

